import pandas as pd
import os
from enum import Enum
import json
import requests
import sys
from pathlib import Path
import hashlib
import math
import png
import debugpy

class Languages(Enum):
    Japanese = 0
    English = 1
    French = 2
    German = 3
    Italian = 4
    SpanishEU = 5
    SpanishLA = 6
    Korean = 7
    ChineseSI = 8
    ChineseTR = 9
    PortugueseBR = 10

class Font:
    def __init__(self, fileName, numColors, numChars, numCharsX, numCharsY, cellWidth, cellHeight, charWidth, charHeight):
        self.fileName = fileName
        self.numColors = numColors
        self.numChars = numChars
        self.numCharsX = numCharsX
        self.numCharsY = numCharsY
        self.cellWidth = cellWidth
        self.cellHeight = cellHeight
        self.charWidth = charWidth
        self.charHeight = charHeight

        self.bpp = int(math.log(numColors, 2)) + 1
        self.numWords = self.numChars * self.cellWidth * self.cellHeight * self.bpp // (8 * 4)
        self.numBytes = self.numWords * 4

        self.charWordTable = [0] * self.numWords
        self.charWidthTable = [0] * self.numBytes

class LanguageConfig:
    def __init__(self, language, column_aliases, char_array, token_indexes=None):
        self.language = language
        self.column_aliases = column_aliases
        self.char_array = char_array
        self.token_indexes = token_indexes

PURPOSEFUL_SPACE_CHAR = '|'
BACKGROUND_PAL_INDEX = 0

BASE_DIR = Path(__file__).resolve().parent
BUILD_DIR = BASE_DIR / "build"
GEN_DIR = BASE_DIR.parent.parent / "build" / "generated"
BUILD_DIR.mkdir(parents=True, exist_ok=True)
GEN_DIR.mkdir(parents=True, exist_ok=True)
TRANSLATED_H_PATH = GEN_DIR / "translated_text.h"
TRANSLATED_CPP_PATH = GEN_DIR / "translated_text.cpp"
FONTS_H_PATH = GEN_DIR / "fonts.h"
OUTPUT_JSON_PATH = BUILD_DIR / "output.json"
THIS_SCRIPT_PATH = BASE_DIR / "main.py"

XLSX_URL = 'https://docs.google.com/spreadsheets/d/14LLs5lLqWasFcssBmJdGXjjYxARAJBa_QUOUhXZt4v8/export?format=xlsx'
NEW_TEXT_XLSX_PATH = BASE_DIR / 'new_text.xlsx'
TEXT_XLSX_PATH = BASE_DIR / 'text.xlsx'

def parse_build_args(argv):
    if len(argv) >= 4:
        return argv[1], argv[2], argv[3]
    return "", "debug", "local"  # BUILD_LANG not implemented yet

def normalize_column_name(name):
    return str(name).strip().lower()

def find_column_by_aliases(columns, aliases):
    normalized_columns = {normalize_column_name(col): col for col in columns}
    for alias in aliases:
        match = normalized_columns.get(normalize_column_name(alias))
        if match is not None:
            return match
    raise KeyError(f"Could not find column matching aliases: {aliases}")

def find_optional_column_by_aliases(columns, aliases):
    try:
        return find_column_by_aliases(columns, aliases)
    except KeyError:
        return None

def sanitize_macro_token(text):
    out = ""
    for char in str(text).upper():
        out += char if char.isalnum() else "_"
    while "__" in out:
        out = out.replace("__", "_")
    return out.strip("_")

def sanitize_c_identifier(text):
    out = ""
    for char in str(text).lower():
        out += char if char.isalnum() else "_"
    while "__" in out:
        out = out.replace("__", "_")
    out = out.strip("_")
    if not out:
        out = "unnamed"
    if out[0].isdigit():
        out = "n_" + out
    return out

mainDict = {}
textSections = []
boxTypeDefinitions = {}
boxTypeNames = []
boxTypeIdByName = {}
fonts = {
    "International": Font("latin_normal", 1, 256, 16, 16, 16, 16, 16, 16),
    "Japanese": Font("japanese_normal", 1, 256, 16, 16, 16, 16, 16, 16),
}

charArrays = {
    "International": {
        "array": [0] * 0x100,
        "font": fonts["International"],
        "escape": [
            ["{SCL}", [0xFA]],
            ["{CLR}", [0xFB]],
            ["{DEF}", [0xFC, 0x01, 0x02]],
            ["{FEM}", [0xFC, 0x01, 0x04]],
            ["{FPC}", [0xFC, 0x01, 0x06]],
            ["{MLE}", [0xFC, 0x01, 0x08]],
            ["{SPA}", [0xFC]],
            ["{PLR}", [0xFD, 0x01]],
            ["{NEW}", [0xFE]],
            ["{END}", [0xFF]],
        ]
    },
    "Japanese": {
        "array": [0] * 0x100,
        "font": fonts["Japanese"],
        "escape": [
            ["{SCL}", [0xFA]],
            ["{CLR}", [0xFB]],
            ["{DEF}", [0xFC, 0x06, 0x02]],
            ["{FEM}", [0xFC, 0x06, 0x03]], # ???
            ["{MLE}", [0xFC, 0x06, 0x04]],
            ["{SPA}", [0xFC]],
            ["{FPC}", [0xFC, 0x06, 0x05]],
            ["{PLR}", [0xFD, 0x01]],
            ["{NEW}", [0xFE]],
            ["{END}", [0xFF]],
        ]
    },
}

LANGUAGE_CONFIGS = {
    Languages.Japanese: LanguageConfig(Languages.Japanese, ("Japanese",), charArrays["Japanese"]),
    Languages.English: LanguageConfig(Languages.English, ("English",), charArrays["International"], (0x30, 0x60, 0x70)),
    Languages.French: LanguageConfig(Languages.French, ("French",), charArrays["International"], (0x31, 0x60, 0x71)),
    Languages.German: LanguageConfig(Languages.German, ("German",), charArrays["International"], (0x32, 0x61, 0x72)),
    Languages.Italian: LanguageConfig(Languages.Italian, ("Italian",), charArrays["International"], (0x33, 0x60, 0x71)),
    Languages.SpanishEU: LanguageConfig(Languages.SpanishEU, ("Spanish (EU)",), charArrays["International"], (0x34, 0x60, 0x72)),
    Languages.SpanishLA: LanguageConfig(Languages.SpanishLA, ("Spanish (LA)",), charArrays["International"], (0x34, 0x60, 0x72)),
    Languages.Korean: LanguageConfig(Languages.Korean, ("Korean",), charArrays["International"]),
    Languages.ChineseSI: LanguageConfig(Languages.ChineseSI, ("Chinese (Simplified)",), charArrays["International"]),
    Languages.ChineseTR: LanguageConfig(Languages.ChineseTR, ("Chinese (Traditional)",), charArrays["International"]),
    Languages.PortugueseBR: LanguageConfig(Languages.PortugueseBR, ("Brazilian Portuguese",), charArrays["International"]),
}

def get_language_config(lang):
    return LANGUAGE_CONFIGS[lang]

charConversionList = [
    # replaces the first char in the list with the latter
    ["'", "’"],
]

def split_into_sentences(text: str) -> list[str]:
    # -*- coding: utf-8 -*-
    import re
    alphabets= r"([A-Za-z])"
    prefixes = r"(Mr|St|Mrs|Ms|Dr)[.]"
    suffixes = r"(Inc|Ltd|Jr|Sr|Co)"
    starters = r"(Mr|Mrs|Ms|Dr|Prof|Capt|Cpt|Lt|He\s|She\s|It\s|They\s|Their\s|Our\s|We\s|But\s|However\s|That\s|This\s|Wherever)"
    acronyms = r"([A-Z][.][A-Z][.](?:[A-Z][.])?)"
    websites = r"[.](com|net|org|io|gov|edu|me)"
    digits = r"([0-9])"
    multiple_dots = r'\.{2,}'

    """
    Split the text into sentences.

    If the text contains substrings "<prd>" or "<stop>", they would lead 
    to incorrect splitting because they are used as markers for splitting.

    :param text: text to be split into sentences
    :type text: str

    :return: list of sentences
    :rtype: list[str]
    """
    text = " " + text + "  "
    text = text.replace("\n"," ")
    text = re.sub(prefixes,"\\1<prd>",text)
    text = re.sub(websites,"<prd>\\1",text)
    text = re.sub(digits + "[.]" + digits,"\\1<prd>\\2",text)
    text = re.sub(multiple_dots, lambda match: "<prd>" * len(match.group(0)) + "<stop>", text)
    if "Ph.D" in text: text = text.replace("Ph.D.","Ph<prd>D<prd>")
    text = re.sub(r"\s" + alphabets + "[.] "," \\1<prd> ",text)
    text = re.sub(acronyms+" "+starters,"\\1<stop> \\2",text)
    text = re.sub(alphabets + "[.]" + alphabets + "[.]" + alphabets + "[.]","\\1<prd>\\2<prd>\\3<prd>",text)
    text = re.sub(alphabets + "[.]" + alphabets + "[.]","\\1<prd>\\2<prd>",text)
    text = re.sub(" "+suffixes+"[.] "+starters," \\1<stop> \\2",text)
    text = re.sub(" "+suffixes+"[.]"," \\1<prd>",text)
    text = re.sub(" " + alphabets + "[.]"," \\1<prd>",text)
    if "”" in text: text = text.replace(".”","”.")
    if "\"" in text: text = text.replace(".\"","\".")
    if "!" in text: text = text.replace("!\"","\"!")
    if "?" in text: text = text.replace("?\"","\"?")
    if "。" in text: text = text.replace("。\"","\"。") # Added for Japanese support
    if "？" in text: text = text.replace("？\"","\"？") # Added for Japanese support
    if "！" in text: text = text.replace("！\"","\"！") # Added for Japanese support
    text = text.replace(".",".<stop>")
    text = text.replace("?","?<stop>")
    text = text.replace("!","!<stop>")
    text = text.replace("。","。<stop>") # Added for Japanese support
    text = text.replace("？","？<stop>") # Added for Japanese support
    text = text.replace("！","！<stop>") # Added for Japanese support
    text = text.replace("<prd>",".")
    text = text.replace("Ň", "<stop>Ň<stop>") # Split newlines into their own sentences
    text = text.replace("ȼ", "<stop>ȼ<stop>") # Split new boxes into their own sentences
    text = text.replace("Ş", "<stop>Ş<stop>") # Split new boxes into their own sentences
    text = text.replace("Ω", "<stop>Ω<stop>") # Split centering into their own sentences
    text = text.replace("ɑ", "<stop>ɑ<stop>") # Split centering into their own sentences

    sentences = text.split("<stop>")
    sentences = [s.strip() for s in sentences]
    if sentences and not sentences[-1]: sentences = sentences[:-1]
    return sentences
 
def split_sentence_into_lines(sentence, offset, pixelsPerChar, pixelsInLine, centered, lang):
    outStr = ""
    currLine = ""
    lineCount = 0
    currWordIndex = 0
    lineLength = 0
    spaceLength = 0

    words = sentence.split()
    language_config = get_language_config(lang)
    language_char_array = language_config.char_array


    while(currWordIndex < len(words)):
        word = words[currWordIndex]
        wordLength = 0
        # print(word)
        
        # Figure out the length of the word in pixels
        for char in word:
            if (char == PURPOSEFUL_SPACE_CHAR):
                char = " "
            if (pixelsPerChar == "Variable"):
                wordLength += language_char_array["font"].charWidthTable[convert_char_to_byte(ord(char), language_char_array["array"], lang)]
                spaceLength = language_char_array["font"].charWidthTable[0]
            elif (pixelsPerChar == "Default"):
                if (lang == Languages.Japanese):
                    wordLength += 8
                    spaceLength = 8
                
                else:
                    wordLength += 6
                    spaceLength = 6
        
        # See if the whole sentence is a newline or scroll
        if (sentence == "Ň" or sentence == "Ş"):
            if (sentence == "Ň"):
                outStr += "Ň"
            elif (sentence == "Ş"):
                outStr += "Ş"
            currLine = ""
            lineCount += 1
            offset = 0
            lineLength = 0
            currWordIndex += 1

         # See if the whole sentence is a center character
        elif (sentence == "ɑ" or sentence == "Ω"):
            if (sentence == "ɑ"):
                centered = True
                outStr += "Ň"
            else:
                centered = False
                outStr += "Ň"
            currLine = ""
            lineCount += 1
            offset = 0
            lineLength = 0
            currWordIndex += 1
            
        # See if the sentence is a new box
        elif(sentence == "ȼ"):
            outStr += sentence
            currLine = ""
            offset = 0
            lineLength = 0
            currWordIndex += 1
            
        # Test if the word is too long in general
        elif (wordLength > pixelsInLine):
            log_warning_error(lang, "Error", f"Word {word} exceeds alloted length ({pixelsInLine} pixels)")
            currWordIndex += 1
            
        # Test if adding the word will go over our alloted space
        elif ((wordLength + lineLength + offset) <= pixelsInLine):
            # If not, add the word and increase the index
            if (currWordIndex == (len(words) - 1)):
                # Don't add a space to the end of the sentence.
                currLine += word
                lineLength += wordLength
            else:
                currLine += (word + " ")
                lineLength += (wordLength + spaceLength)
            currWordIndex += 1
            
        # We need to move to the next line
        else:
            # Every line should already have a space at the end of it. Remove it here
            outStr += (currLine[:-1] + "Ň")
            currLine = ""
            lineCount += 1
            lineLength = 0
            offset = 0
    if (centered and (len(words) > 0) and words[0] not in ['ɑ', 'ȼ', 'Ň', 'Ş']):
        count = ((pixelsInLine - lineLength) // 2)
        currLine = f'_[{count}]{currLine}'
        lineLength += count
    outStr += currLine
    return lineLength + offset, lineCount, outStr, centered

def convert_char_to_byte(incoming, array, lang):
    for pair in charConversionList:
        if incoming == ord(pair[0]):
            incoming = ord(pair[1])
            log_warning_error(lang, "Warning", f"Character {pair[0]} was used but is not in character table. Replaced with {pair[1]} .")
    
    index = 0
    #print(array)
    for val in array:
        if str(val) == chr(incoming):
            return index
        index += 1    
    if chr(incoming) != '_':
        log_warning_error(lang, "Error", f"No match found for char [ {chr(incoming)} ]!")
    return 0
    
def log_warning_error(lang, type, text):
    nType = type + "s"
    nText = type + ": " + text
    if nText not in mainDict[lang.name][nType].values():
        mainDict[lang.name][nType][max(mainDict[lang.name][nType].keys(), default =- 1) + 1] = nText
        #print(nText)

def hash_excel(path):
    sheets = pd.read_excel(path, sheet_name=None)
    h = hashlib.sha256()
    for name in sorted(sheets):
        h.update(name.encode())
        h.update(pd.util.hash_pandas_object(
            sheets[name], index=True
        ).values)
    return h.digest()

def apply_escape_sequences(line, arr, escape_list):
    for token, char_indexes in escape_list:
        if token in line:
            escape_string = "".join(arr[idx] for idx in char_indexes)
            line = line.replace(token, escape_string)

    # Special case for centering escape characters
    line = line.replace("{CTR}", 'ɑ')
    line = line.replace("{nCTR}", 'Ω')
    return line

def apply_language_tokens(line, arr, lang):
    indexes = get_language_config(lang).token_indexes
    if indexes is None:
        return line

    lvl_index, pp_index, no_index = indexes
    return (
        line
        .replace("{LVL}", arr[lvl_index])
        .replace("{PP}", arr[pp_index])
        .replace("{NO}", arr[no_index])
    )

def convert_item(ogDict, lang):
    line = ogDict["bytes"]
    numLines = ogDict["numLines"]
    pixelsPerChar = ogDict["pixelsPerChar"]
    pixelsInLine = ogDict["pixelsInLine"]
    include_box_breaks = ogDict["includeBoxBreaks"]
    include_scrolling = ogDict["includeScrolling"]

    language_char_array = get_language_config(lang).char_array
    arr = language_char_array["array"]
    escape_list = language_char_array["escape"]

    line = apply_escape_sequences(line, arr, escape_list)
    line = apply_language_tokens(line, arr, lang)

    # Change all the punctuation marks followed by spaces into being followed by | temporarily
    spaces = [' ', '　']
    puncts = ['.', '?', '!', '。', '！', '？']
    for space in spaces:
        for punct in puncts:
            line = line.replace(punct + space, punct + PURPOSEFUL_SPACE_CHAR)

    split_sents = split_into_sentences(line)
    index = 0
    outStr = ""
    currLine = 0
    offset = 0
    escapeCount = 0
    centered = False
    while index < len(split_sents) and escapeCount < 100:
        offset, recievedLine, out, centered = split_sentence_into_lines(split_sents[index], offset, pixelsPerChar, pixelsInLine, centered, lang)
        currLine += recievedLine
        
        if (out == "ȼ"):
            offset = 0
            currLine = 0
            # This tests if the character before the new box is a space, newline, or scroll
            if outStr and (outStr[-1] in (" ", "Ň", "Ş")):
                outStr = outStr[:-1]
            outStr += "ȼ"
            index += 1
        elif (currLine < (numLines + int(include_scrolling))):
            #print(split_sents[index])
            index += 1
            # This tests if the character after the new box is a space, newline, or scroll
            if outStr and out and outStr[-1] == 'ȼ' and out[0] in (" ", "Ň", "Ş"):
                out = out[1:]
            outStr += out
        else:
            if not include_box_breaks:
                log_warning_error(lang, "Error", f"Attempted to make a new text box when disabled, sentence \"{outStr}\" is too long!")
            # This tests if the character before the new box is a space, newline, or scroll(?)
            elif outStr and (outStr[-1] in (" ", "Ň", "Ş")):
                outStr = outStr[:-1]
            outStr += "ȼ" # new textbox character
            offset = 0
            currLine = 0
            escapeCount += 1
                #print(index)

            
    if escapeCount == 100:
        log_warning_error(lang, "Error", f"Sentence \"{out}\" is too long!")

    # It's safe to swap the purposeful spaces back
    outStr = outStr.replace(PURPOSEFUL_SPACE_CHAR, " ")

    # Some cases that should be fixed
    exitLoop = False
    while(not exitLoop):
        newStr = ""

        splitBoxes = outStr.split('ȼ')
        outIndex = 0
        for box in splitBoxes:
            if box and ((box[0] == " ")):
                box = box[1:]
                outIndex += 1
            # Make sure both kinds of newlines are being accounted for
            box = box.replace('Ş', 'Ň')
            splitLines = box.split('Ň')
            outBox = ""
            i = 1
            for split in splitLines:
                outIndex += len(split)
                if split == splitLines[-1]:
                    breakChar = ""
                elif ((i >= numLines) and include_scrolling):
                    breakChar = 'Ş'
                else:
                    breakChar = outStr[outIndex]
                outBox += split + breakChar
                outIndex += 1
                i += 1
            if (outBox and (outBox[:-1] == 'ȼ') or (outBox[:-1] == 'Ň')):
                newStr += f'{outBox[:-1]}ȼ'
            elif (outBox):
                newStr += f'{outBox}ȼ'
        newStr = newStr[:-1] # remove the last ȼ

        if len(newStr) > 1023:
            newStr = newStr[:1023]
            log_warning_error(lang, "Warning", f"String {newStr} exceeds character limit of 1023 and has been truncated.")

        exitLoop = (newStr == outStr)
        outStr = newStr
    
    byteStr = ""
    arr = language_char_array["array"]
    i = 0
    while i < len(outStr[:-1]):
        char = outStr[i]
        if (char == '['):
            val = ''
            i += 1
            while outStr[i] != ']':
                val = val + outStr[i]
                i += 1
            num = int(val)
            byteStr += f"{num:02x} "
        else:
            byteStr += f"{convert_char_to_byte(ord(char), arr, lang):02x} "
        i += 1
    if (len(outStr) > 0 and outStr[-1] != ' '): # Check if the last char is a space
        byteStr += f"{convert_char_to_byte(ord(outStr[-1]), arr, lang):02x} "
        
    byteStr += "ff"
    
    ogDict["bytes"] = byteStr
    return ogDict

def write_text_bin_file(filename, dictionary, lang, section):
    MAX_BIN_SIZES = {
        "PTGB": 6144,
        "RSEFRLG": 3444,
        "GB": 9999,
        "GENERAL": 2048,
        "CREDITS": 2048,
        "PKMN_NAMES": 3072,
    }

    Path(filename).parent.mkdir(parents=True, exist_ok=True)
    with open(filename, 'wb') as binFile:
        # Let the first byte indicate the number of entries
        dict_size = len(dictionary)
        # We need to store 2 bytes instead of one, because not aligning the data to 16 bits will cause corruption on the gba.
        binFile.write(bytes([dict_size & 0xFF, (dict_size >> 8) & 0xFF]))
        # After this initial byte, we will read the offset (16 bit) of each line (relative to the last index byte)
        index = bytearray(len(dictionary) * 2)
        # bindata will contain the binary data of each entry
        bindata = bytearray()
        current_offset = 0

        num = 0
        # Append every line's binary data to bindata
        # keep an index of the binary offset within bindata at which each line starts
        for key, line in dictionary.items():
            dictionary[key] = convert_item(line, lang)
            # store the offset of the line in the index as a 16 bit little endian value
            index[num * 2] = (current_offset & 0xFF)
            index[num * 2 + 1] = (current_offset >> 8) & 0xFF
            linedata = bytes.fromhex(dictionary[key]['bytes'])

            bindata.extend(linedata)
            current_offset += len(linedata)

            num += 1

        # Write the index and bindata to the file
        binFile.write(index)
        binFile.write(bindata)
        binFile.seek(0, os.SEEK_END)
        if binFile.tell() > MAX_BIN_SIZES[section]:
            log_warning_error(lang, "Error", f'Section {section} exceeds the max binary file size by {binFile.tell() - MAX_BIN_SIZES[section]} bytes!')
        binFile.close()

def write_enum_to_header_file(hFile, prefix, dictionary):
    num = 0
    for key, line in dictionary.items():
        hFile.write(f"#define {prefix}{key} {num}\n")
        num += 1
    hFile.write(f"\n#define {prefix}LENGTH {num}\n")
    hFile.write("\n")
    return num

def update_xlsx_file(build_xlsx_mode):

    if build_xlsx_mode == "local":
        print("\tUsing local XLSX file.")

        if not TEXT_XLSX_PATH.exists():
            print("ERROR: Local XLSX file not found.")
            sys.exit(1)
        return False

    elif build_xlsx_mode == "remote":
        print("\tDownloading XLSX.")

        try:
            response = requests.get(XLSX_URL, timeout=5)
            response.raise_for_status()

            with open(NEW_TEXT_XLSX_PATH, 'wb') as f:
                f.write(response.content)

            print("\tDownload successful.")

        except requests.exceptions.RequestException as e:
            print("ERROR: Failed to download XLSX.")
            print(f"Reason: {e}")
            sys.exit(1)

        # If cached file exists, compare hashes
        if TEXT_XLSX_PATH.exists():
            if hash_excel(NEW_TEXT_XLSX_PATH) == hash_excel(TEXT_XLSX_PATH):
                print("\tDownloaded file is identical. Skipping parse.")
                NEW_TEXT_XLSX_PATH.unlink()
                return False
            else:
                TEXT_XLSX_PATH.unlink()
                NEW_TEXT_XLSX_PATH.rename(TEXT_XLSX_PATH)
                return True
        else:
            print("\tNo cached XLSX - forcing rebuild.")
            NEW_TEXT_XLSX_PATH.rename(TEXT_XLSX_PATH)
            return True

    else:
        print(f"ERROR: Invalid BUILD_XLSX value '{build_xlsx_mode}'")
        sys.exit(1)

def are_text_build_artifacts_newer():
    if debugpy.is_client_connected():
        print("\tDebugger connected, forcing text rebuild.")
        return False

    artifacts = [TRANSLATED_H_PATH, TRANSLATED_CPP_PATH, OUTPUT_JSON_PATH]
    if any(not path.exists() for path in artifacts):
        print("\tText artifacts missing - forcing rebuild.")
        return False

    artifacts_are_stale = are_generated_files_stale(get_text_source_files(), artifacts)
    if artifacts_are_stale:
        print("\tText artifacts are older than sources - forcing rebuild.")
        return False

    print("\tText artifacts are newer than sources. Skipping text rebuild.")
    return True

def initialize_translation_storage():
    mainDict.clear()
    for lang in Languages:
        mainDict[lang.name] = {section: {} for section in textSections}
        mainDict[lang.name]["Warnings"] = {}
        mainDict[lang.name]["Errors"] = {}

def transfer_xlsx_to_dict():
    global boxTypeDefinitions
    global boxTypeNames
    global boxTypeIdByName

    print("\tGetting character arrays")
    currSheet = pd.read_excel(TEXT_XLSX_PATH, sheet_name="Character Arrays", header=None)
    offset = 0
    for key, value in charArrays.items():
        for r in range(16):
            for c in range(16):
                val = currSheet.iloc[r + 1, c + offset]
                if pd.isna(val):
                    val = " "
                value["array"][r * 0x10 + c] = val
        # print(charArrays[key])
        offset += 16



    print("\tGetting string data")
    currSheet = pd.read_excel(TEXT_XLSX_PATH, sheet_name="Translations")
    sheet_columns = list(currSheet.columns)

    print("\tGetting box types")
    boxTypeSheet = pd.read_excel(TEXT_XLSX_PATH, sheet_name="Box Types")
    box_type_columns = list(boxTypeSheet.columns)
    box_type_name_col = find_column_by_aliases(box_type_columns, ("Box Type",))
    box_type_num_lines_col = find_column_by_aliases(box_type_columns, ("# of Lines",))
    box_type_pixels_in_line_col = find_column_by_aliases(box_type_columns, ("Pixels per line",))
    box_type_include_box_breaks_col = find_column_by_aliases(box_type_columns, ("Include box breaks",))
    box_type_include_scrolling_col = find_column_by_aliases(box_type_columns, ("Include one line of scrolling",))
    box_type_pixels_per_char_col = find_optional_column_by_aliases(box_type_columns, ("Pixels per Char",))
    box_type_box_style = find_column_by_aliases(box_type_columns, ("Box Style",))

    boxTypeDefinitions = {}
    boxTypeNames = []
    boxTypeIdByName = {}
    for _, box_type_row in boxTypeSheet.iterrows():
        box_type_name = box_type_row[box_type_name_col]
        if pd.isna(box_type_name):
            continue
        box_type_name = str(box_type_name).strip()
        if box_type_name in boxTypeDefinitions:
            raise KeyError(f"Duplicate Box Type '{box_type_name}' found in Box Types sheet.")
        pixels_per_char = "Default"
        if box_type_pixels_per_char_col is not None:
            value = box_type_row[box_type_pixels_per_char_col]
            if not pd.isna(value):
                pixels_per_char = value
        boxTypeDefinitions[box_type_name] = {
            "numLines": box_type_row[box_type_num_lines_col],
            "pixelsPerChar": pixels_per_char,
            "pixelsInLine": box_type_row[box_type_pixels_in_line_col],
            "includeBoxBreaks": box_type_row[box_type_include_box_breaks_col],
            "includeScrolling": box_type_row[box_type_include_scrolling_col],
            "boxStyle": box_type_row[box_type_box_style],
        }
        boxTypeIdByName[box_type_name] = len(boxTypeNames)
        boxTypeNames.append(box_type_name)

    text_section_col = find_column_by_aliases(sheet_columns, ("Text Section",))
    text_key_col = find_column_by_aliases(sheet_columns, ("Text Key", "Text ID", "Key"))
    box_type_col = find_column_by_aliases(sheet_columns, ("Box Type",))

    language_columns = {
        lang: find_column_by_aliases(sheet_columns, get_language_config(lang).column_aliases)
        for lang in Languages
    }
    english_col = language_columns[Languages.English]

    textSections.clear()
    for row in currSheet.iterrows():
        currRow = row[1][text_section_col]
        if (currRow not in textSections):
            textSections.append(currRow)

    initialize_translation_storage()

    for row in currSheet.iterrows():
        #print(row)
        for lang in Languages:
            currRow = row[1]
            lang_col = language_columns[lang]
            text_value = currRow[lang_col]
            if pd.isna(text_value):
                text_value = currRow[english_col]
            box_type_name = currRow[box_type_col]
            if pd.isna(box_type_name):
                raise KeyError(f"Missing Box Type for row key '{currRow[text_key_col]}' in section '{currRow[text_section_col]}'.")
            box_type_name = str(box_type_name).strip()
            box_type_data = boxTypeDefinitions.get(box_type_name)
            if box_type_data is None:
                raise KeyError(
                    f"Unknown Box Type '{box_type_name}' for row key '{currRow[text_key_col]}' "
                    f"in section '{currRow[text_section_col]}'."
                )
            mainDict[lang.name][currRow[text_section_col]][currRow[text_key_col]] = {"bytes": text_value,
                                                                                       "boxType": box_type_name,
                                                                                       "numLines": box_type_data["numLines"],
                                                                                       "pixelsPerChar": box_type_data["pixelsPerChar"],
                                                                                       "pixelsInLine" : box_type_data["pixelsInLine"],
                                                                                       "includeBoxBreaks": box_type_data["includeBoxBreaks"],
                                                                                       "includeScrolling": box_type_data["includeScrolling"],
                                                                                       "boxStyle": box_type_data["boxStyle"],
                                                                                       }

def generate_header_file():
    print("\tGenerating header file")
    with open(TRANSLATED_H_PATH, 'w') as hFile:
        hFile.write("// THIS FILE HAS BEEN GENERATED BY text_helper/main.py !\n\n#ifndef TRANSLATED_TEXT_H\n#define TRANSLATED_TEXT_H\n\n#include <tonc.h>\n\n")

        sectionEnds = []
        index = 0
        lang = Languages.English # This doesn't matter, it just needs to be there. They're all the same
        for section in textSections:
            num = write_enum_to_header_file(hFile, section + "_", mainDict[lang.name][section])
            hFile.write("#define " + section + "_INDEX " + str(index))
            if(section == "PTGB"):
                hFile.write(f"\n#define DIA_END {num}\n")

            hFile.write("/** Returns the LZ10 compressed " + section + " text table.*/\n")
            sectionEnds.append(num)
            index += 1

        hFile.write("#define NUM_TEXT_SECTIONS " + str(index) + "\n")
        hFile.write("const int text_section_lengths[] = {\n")
        for end in sectionEnds:
            hFile.write("\t" + str(end) + ",\n")
        hFile.write("};\n\n")

        hFile.write("#define BOX_TYPE_INVALID 0xFF\n")
        for box_type_name in boxTypeNames:
            box_type_id = boxTypeIdByName[box_type_name]
            hFile.write(f"#define BOX_TYPE_{sanitize_macro_token(box_type_name)} {box_type_id}\n")
        hFile.write(f"#define NUM_BOX_TYPES {len(boxTypeNames)}\n\n")
        for index, definitions in enumerate(boxTypeDefinitions[boxTypeNames[0]]):
            hFile.write(f"#define BOX_TYPE_VAL_{sanitize_macro_token(definitions)} {index}\n")
        hFile.write(f"#define NUM_BOX_TYPE_VALS {len(boxTypeDefinitions[boxTypeNames[0]])}\n\n")
        hFile.write("const int box_type_info[NUM_BOX_TYPES][NUM_BOX_TYPE_VALS] = {\n")
        for box_type_name in boxTypeNames:
            boxType = boxTypeDefinitions[box_type_name]
            hFile.write(f"\t{{{boxType["numLines"]}, {boxType["pixelsInLine"]}, {boxType["pixelsPerChar"]}, {int(boxType["includeBoxBreaks"])}, {int(boxType["includeScrolling"])}, {int(boxType["boxStyle"])}}},\n")
        hFile.write("};\n\n")

        hFile.write("const u8* get_compressed_text_table(int table_index);\n")
        hFile.write("u8 get_text_box_type(int table_index, int text_index);\n")


        hFile.write("\n#endif")
        hFile.close()

def generate_text_tables():
    print("\tGenerating text tables")
    for lang in Languages:
        for section in textSections:
            table_file = os.curdir + '/to_compress/' + section + '_' + lang.name.lower() + '.bin'
            write_text_bin_file(table_file, mainDict[lang.name][section], lang, section)

def generate_cpp_file():
    print("\tGenerating cpp file")
    with open(TRANSLATED_CPP_PATH, 'w') as cppFile:
        cppFile.write("// THIS FILE HAS BEEN GENERATED BY text_helper/main.py !\n#include \"translated_text.h\"\n#include \"dbg/debug_mode.h\"\n")
        # generate includes for each language
        for lang in Languages:
            for section in textSections:
                cppFile.write("#include \"" + section.upper() + "_" + lang.name.lower() + "_lz10_bin.h\"\n")

        cppFile.write("\n")
        for section in textSections:
            section_var = sanitize_c_identifier(section)
            box_type_macros = []
            for _, entry in mainDict[Languages.English.name][section].items():
                box_type_name = entry["boxType"]
                box_type_macros.append(f"\n\tBOX_TYPE_{sanitize_macro_token(box_type_name)}")
            cppFile.write(f"\nstatic const u8 {section_var}_box_types[] = {{")
            cppFile.write(",".join(box_type_macros))
            cppFile.write("\n};\n")

        cppFile.write("\nconst u8* get_compressed_text_table(int table_index)\n")

        for i, lang in enumerate(Languages):
            cppFile.write(f"\n#{'el' if i > 0 else ''}if PTGB_BUILD_LANGUAGE == {lang.value + 1}\n")
            cppFile.write("{\n")
            cppFile.write("\tswitch (table_index)\n\t{\n")
            for section in textSections:
                cppFile.write("\tcase (" + section + "_INDEX):\n")
                if(section == "PTGB"):
                    cppFile.write("\tdefault:\n")
                cppFile.write("\t\treturn " + section + "_" + lang.name.lower() + "_lz10_bin;\n")
                cppFile.write("\t\tbreak;\n")
            cppFile.write("\t}\n")
            cppFile.write("}\n")
        cppFile.write(f"#else\n#error \"Unsupported PTGB_BUILD_LANGUAGE\"\n#endif")

        cppFile.write("\n\nu8 get_text_box_type(int table_index, int text_index)\n")
        cppFile.write("{\n")
        cppFile.write("\tif (text_index < 0)\n")
        cppFile.write("\t\treturn BOX_TYPE_INVALID;\n")
        cppFile.write("\tswitch (table_index)\n")
        cppFile.write("\t{\n")
        for section in textSections:
            section_var = sanitize_c_identifier(section)
            cppFile.write(f"\tcase({section}_INDEX):\n")
            cppFile.write(f"\t\tif (text_index >= {section}_LENGTH)\n")
            cppFile.write("\t\t\treturn BOX_TYPE_INVALID;\n")
            cppFile.write(f"\t\treturn {section_var}_box_types[text_index];\n")
        cppFile.write("\tdefault:\n")
        cppFile.write("\t\treturn BOX_TYPE_INVALID;\n")
        cppFile.write("\t}\n")
        cppFile.write("}\n")

def output_json_file():
    print("\tOutputting json file")
    for lang in Languages:
        for section in textSections:
            for item in mainDict[lang.name][section]:
                string = mainDict[lang.name][section][item]["bytes"].split(" ")
                outText = ""
                arr = get_language_config(lang).char_array["array"]
                for byte in string:
                    byte = arr[int(byte, 16)]
                    outText += str(byte)
                mainDict[lang.name][section][item]["text"] = outText

    with open(OUTPUT_JSON_PATH, 'w') as jsonFile:
        jsonFile.write(json.dumps(mainDict))

def are_generated_files_stale(source_files, generated_files):
    source_paths = [Path(path) for path in source_files]
    generated_paths = [Path(path) for path in generated_files]

    missing_sources = [path for path in source_paths if not path.exists()]
    if missing_sources:
        raise FileNotFoundError(f"Missing source files: {', '.join(str(path) for path in missing_sources)}")

    if any(not path.exists() for path in generated_paths):
        return True

    newest_source_mtime = max(path.stat().st_mtime for path in source_paths)
    oldest_generated_mtime = min(path.stat().st_mtime for path in generated_paths)
    return newest_source_mtime > oldest_generated_mtime

def update_generated_files(target_name, source_files, generated_files, generate_function):
    if debugpy.is_client_connected():
        print(f"\tDebugger connected, rebuilding {target_name}!")
        generate_function()
        return

    if are_generated_files_stale(source_files, generated_files):
        print(f"\t{target_name} outputs are outdated or missing. Rebuilding...")
        generate_function()
        return

    print(f"\t{target_name} outputs are up to date. Skipping rebuild.")

def build_h():
    print("\tBuilding font.h")
    with open(FONTS_H_PATH, 'w') as f:
        f.write(f'''#ifndef PTGB_BUILD_LANGUAGE
#error "PTGB_BUILD_LANGUAGE not defined"
#endif

#include "dbg/debug_mode.h"
#include "pokemon_data.h"

#ifndef __FONTS_H__
#define __FONTS_H__''')


        for myFont in fonts.values():
            f.write(f'''\n
#define {myFont.fileName}GlyphsLen {myFont.numBytes}
#define {myFont.fileName}WidthsLen {myFont.numChars}''')
            
            f.write(f'\n\nconst unsigned int {myFont.fileName}Glyphs[{myFont.numWords}] __attribute__((aligned(4)))=\n{{\n\t')

            for i in range(myFont.numWords):
                f.write(f'{myFont.charWordTable[i]:#010x},')
                if (i == myFont.numWords - 1):
                    f.write("\n};\n\n")
                elif (i % 64 == 63):
                    f.write("\n\n\t")
                elif (i % 8 == 7):
                    f.write("\n\t")

            f.write(f'const unsigned char {myFont.fileName}Widths[{myFont.numChars}] __attribute__((aligned(4)))=\n{{\n\t')

            for i in range(myFont.numChars):
                f.write(f'{myFont.charWidthTable[i]:#04x}, ')
                if (i == myFont.numChars - 1):
                    f.write("\n};\n\n")
                elif (i % 128 == 127):
                    f.write("\n\n\t")
                elif (i % 16 == 15):
                    f.write("\n\t")

            f.write(f'''const TFont {myFont.fileName}Font= 
{{
    {myFont.fileName}Glyphs, 
    {myFont.fileName}Widths, 
    0, // All heights are the same 
    0, // Character offset, is set to zero
    {myFont.numChars},
    {myFont.charWidth}, {myFont.charHeight},
    {myFont.cellWidth}, {myFont.cellHeight}, 
    {myFont.numBytes // myFont.numChars}, 
    {myFont.bpp}, 
    0, // Padding, left blank
}};''')

        f.write('\n\n#endif')
    f.close()

def generate_tables():
    for myFont in fonts.values():
        print(f'\t\t{myFont.fileName}')
        reader = png.Reader(f'{BASE_DIR}/fonts/{myFont.fileName}.png')
        png_info = reader.read()[3]
        palette = png_info.get('palette')
        if (palette is None):
            print("Error: Image file does not contain a palette")
            exit()

        width, height, rows, info = reader.read()
        pixels = list(rows)

        bitsPerWord = 32
        pixelsPerTileX = 8
        pixelsPerTileY = 8
        tilesPerCharX = myFont.cellWidth // pixelsPerTileX
        tilesPerCharY = myFont.cellHeight // pixelsPerTileY
        charsPerChartX = myFont.numCharsX
        charsPerChartY = myFont.numCharsY

        globalX = 0
        globalY = 0
        bitTotal = 0

        for charY in range(charsPerChartY):
            for charX in range(charsPerChartX):
                for tileX in range(tilesPerCharX): # Tiles go from top to bottom, then left to right
                    for tileY in range(tilesPerCharY):
                        for pixelY in range(pixelsPerTileY):
                            for pixelX in range(pixelsPerTileX):
                                
                                arrayIndex = bitTotal // bitsPerWord
                                bitIndex = bitTotal % bitsPerWord

                                globalX = pixelX + (tileX * pixelsPerTileX) + (charX * tilesPerCharX * pixelsPerTileX)
                                globalY = pixelY + (tileY * pixelsPerTileY) + (charY * tilesPerCharY * pixelsPerTileY)

                                val = (pixels[globalY][globalX] - 1)
                                if val < 0:
                                    val = 0
                                val &= myFont.bpp
                                myFont.charWordTable[arrayIndex] |= val << bitIndex

                                #print(f'globalX: {globalX}, globalY: {globalY}, arrayIndex:{arrayIndex}, bitIndex:{bitIndex}, val:{val}')
                                bitTotal += myFont.bpp
                
                #print(f'{charX, charY}')

                myFont.charWidthTable[(charY * charsPerChartX) + charX] = (tilesPerCharX * pixelsPerTileX)
                for x in range(tilesPerCharX * pixelsPerTileX):
                    globalX = x + (charX * tilesPerCharX * pixelsPerTileX)
                    globalY = 0 + (charY * tilesPerCharY * pixelsPerTileY)
                    #print(f'x: {globalX}, y: {globalY}')
                    if (pixels[globalY][globalX] == BACKGROUND_PAL_INDEX):
                        myFont.charWidthTable[(charY * charsPerChartX) + charX] = x
                        break

def get_font_source_files():
    return [THIS_SCRIPT_PATH] + [BASE_DIR / "fonts" / f"{font.fileName}.png" for font in fonts.values()]

def get_font_generated_files():
    return [FONTS_H_PATH]

def generate_font_files():
    print("\tGenerating font tables:")
    generate_tables()
    build_h()

def update_font_files():
    update_generated_files(
        target_name="Fonts.h",
        source_files=get_font_source_files(),
        generated_files=get_font_generated_files(),
        generate_function=generate_font_files,
    )

def get_text_source_files():
    return [THIS_SCRIPT_PATH, TEXT_XLSX_PATH]

def get_text_generated_files():
    generated_files = [TRANSLATED_H_PATH, TRANSLATED_CPP_PATH, OUTPUT_JSON_PATH]
    for lang in Languages:
        for section in textSections:
            generated_files.append(Path(os.curdir) / "to_compress" / f"{section}_{lang.name.lower()}.bin")
    return generated_files

def generate_text_files():
    generate_header_file()
    generate_text_tables()
    generate_cpp_file()
    output_json_file()

def update_text_files():
    update_generated_files(
        target_name="Text",
        source_files=get_text_source_files(),
        generated_files=get_text_generated_files(),
        generate_function=generate_text_files,
    )

def main():
    _, _, build_xlsx_mode = parse_build_args(sys.argv)
    print("Running text_helper:")
    update_font_files()
    update_xlsx_file(build_xlsx_mode)
    if are_text_build_artifacts_newer():
        print("text_helper finished!\n")
        return
    transfer_xlsx_to_dict()
    update_text_files()
    print("text_helper finished!\n")

if __name__ == "__main__":
    main()
