import pandas as pd
import os 
from enum import Enum
import json
import requests
from collections import defaultdict
import sys
from pathlib import Path
import hashlib
import math
import numpy as np
import png
import shutil
import debugpy

class Languages(Enum):
    Japanese = 0
    English = 1
    French = 2
    German = 3
    Italian = 4
    SpanishEU = 5
    SpanishLA = 6

FIRST_TRANSLATION_COL_INDEX = 10
PURPOSEFUL_SPACE_CHAR = '|'

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

url = 'https://docs.google.com/spreadsheets/d/14LLs5lLqWasFcssBmJdGXjjYxARAJBa_QUOUhXZt4v8/export?format=xlsx'
new_file_path = BUILD_DIR / 'new_text.xlsx'
old_file_path = BUILD_DIR / 'text.xlsx'
release_file_path = BASE_DIR / 'release.xlsx'
json_file_path = BUILD_DIR / "output.json"

if len(sys.argv) >= 3:
    BUILD_LANG = sys.argv[1]
    BUILD_TYPE = sys.argv[2]
else:
    BUILD_LANG = "" # Not implemented yet
    BUILD_TYPE = "debug"

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


    while(currWordIndex < len(words)):
        word = words[currWordIndex]
        wordLength = 0
        # print(word)
        
        # Figure out the length of the word in pixels
        for char in word:
            if (char == PURPOSEFUL_SPACE_CHAR):
                char = " "
            if (pixelsPerChar == "Variable"):
                wordLength += charArrayOfLanguage[lang]["font"].charWidthTable[convert_char_to_byte(ord(char), charArrayOfLanguage[lang]["array"], lang)]
                spaceLength = charArrayOfLanguage[lang]["font"].charWidthTable[0]
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

def convert_item(ogDict, lang):
    line = ogDict["bytes"]
    numLines = ogDict["numLines"]
    pixelsPerChar = ogDict["pixelsPerChar"]
    pixelsInLine = ogDict["pixelsInLine"]
    include_box_breaks = ogDict["includeBoxBreaks"]
    include_scrolling = ogDict["includeScrolling"]

    arr = charArrayOfLanguage[lang]["array"]
    escape_list = charArrayOfLanguage[lang]["escape"]

    for pair in escape_list:
        if pair[0] in line:
            escapeString = ""
            for char in pair[1]:
                escapeString += arr[char]
            #print(f"Replacing {pair[0]} with {escapeString}!")
            line = line.replace(pair[0], escapeString)
            #print(line)
    
    # Special case for the centering escape character
    line = line.replace("{CTR}", 'ɑ')
    line = line.replace("{nCTR}", 'Ω')

    # Special case for the values that change by language. Probably should be built into the lang struct eventually
    if (lang == Languages.English):
            line = line.replace("{LVL}", arr[0x30])
            line = line.replace("{PP}", arr[0x60])
            line = line.replace("{NO}", arr[0x70])
    elif (lang == Languages.French):
            line = line.replace("{LVL}", arr[0x31])
            line = line.replace("{PP}", arr[0x60])
            line = line.replace("{NO}", arr[0x71])            
    elif (lang == Languages.German):
            line = line.replace("{LVL}", arr[0x32])
            line = line.replace("{PP}", arr[0x61])
            line = line.replace("{NO}", arr[0x72])  
    elif (lang == Languages.Italian):
            line = line.replace("{LVL}", arr[0x33])
            line = line.replace("{PP}", arr[0x60])
            line = line.replace("{NO}", arr[0x71])  
    elif (lang == Languages.SpanishEU or lang == Languages.SpanishLA):
            line = line.replace("{LVL}", arr[0x34])
            line = line.replace("{PP}", arr[0x60])
            line = line.replace("{NO}", arr[0x72])  

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
    arr = charArrayOfLanguage[lang]["array"]
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

def download_xlsx_file():
    if os.path.isfile(release_file_path):
        print('Release file found. Using that instead!')
        shutil.copy(release_file_path, new_file_path)
        offline = False
    else:
        print("Downloading xlsx file")
        offline = False
        # ---- Attempt download ----
        try:
            response = requests.get(url, timeout=5)
            response.raise_for_status()
            with open(new_file_path, 'wb') as f:
                f.write(response.content)
            print("File downloaded successfully")

        except (requests.exceptions.ReadTimeout, requests.exceptions.ConnectionError):
            if old_file_path.exists():
                print("No internet. Using cached xlsx.")
                offline = True
            else:
                print("ERROR: No internet and no cached xlsx. Cannot continue.")
                sys.exit(1)

    # ---- Decision logic ----
    if offline:
        # XML exists (guaranteed here)
        if json_file_path.exists():
            print("Offline mode: trusting cached XML + JSON. Skipping parse.")
            if debugpy.is_client_connected():
                print("\t...but we're running with a debugger, so we're doing it anyway!")
                return
            elif os.path.getmtime(THIS_SCRIPT_PATH) > os.path.getmtime(OUTPUT_JSON_PATH):
                print("\t...but the python file is new, so we're doing it anyway!")
                return
            sys.exit(0)
        else:
            print("Offline mode: XML present but JSON missing. Rebuilding.")

    else:
        # Online mode
        if old_file_path.exists():

            if hash_excel(new_file_path) == hash_excel(old_file_path):
                print("Downloaded file is identical")
                new_file_path.unlink()
                if json_file_path.exists():
                    print("Skipping parse")
                    if debugpy.is_client_connected():
                        print("\t...but we're running with a debugger, so we're doing it anyway!")
                        return
                    elif os.path.getmtime(THIS_SCRIPT_PATH) > os.path.getmtime(OUTPUT_JSON_PATH):
                        print("\t...but the python file is new, so we're doing it anyway!")
                        return
                    sys.exit(0)
                else:
                    print("JSON missing - forcing rebuild")
            else:
                old_file_path.unlink()
                new_file_path.rename(old_file_path)

        else:
            print("No cached xlsx - forcing rebuild")
            new_file_path.rename(old_file_path)

def transfer_xlsx_to_dict():
    print("\tGetting character arrays")
    currSheet = pd.read_excel(old_file_path, sheet_name="Character Arrays", header=None)
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
    currSheet = pd.read_excel(old_file_path, sheet_name="Translations")

    for row in currSheet.iterrows():
        currRow = row[1]["Text Section"]
        if (currRow not in textSections):
            textSections.append(currRow)

    for lang in Languages:
        mainDict[lang.name] = {}
        for section in textSections:
            mainDict[lang.name][section] = {}
            mainDict[lang.name]["Warnings"] = {}
            mainDict[lang.name]["Errors"] = {}

    for row in currSheet.iterrows():
        #print(row)
        for lang in Languages:
            currRow = row[1]
            #print(currRow)
            offset = lang.value
            if (pd.isna(currRow.iloc[FIRST_TRANSLATION_COL_INDEX + lang.value])):
                offset = Languages.English.value
            mainDict[lang.name][currRow.iloc[1]][currRow.iloc[2]] = {"bytes": currRow.iloc[FIRST_TRANSLATION_COL_INDEX + offset],
                                                                        "numLines": currRow.iloc[3],
                                                                        "pixelsPerChar": currRow.iloc[4],
                                                                        "pixelsInLine" : currRow.iloc[5],
                                                                        "includeBoxBreaks": currRow.iloc[6],
                                                                        "includeScrolling": currRow.iloc[7],
                                                                        }
def test_if_release():
    if (BUILD_TYPE == 'release'):
        print("\tis release. Saving text file as release.xlsx")
        shutil.copy(old_file_path, release_file_path)

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

        hFile.write("const u8* get_compressed_text_table(int table_index);\n")


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
        cppFile.write("// THIS FILE HAS BEEN GENERATED BY text_helper/main.py !\n#include \"translated_text.h\"\n#include \"debug_mode.h\"\n")
        # generate includes for each language
        for lang in Languages:
            for section in textSections:
                cppFile.write("#include \"" + section.upper() + "_" + lang.name.lower() + "_lz10_bin.h\"\n")


        cppFile.write("\nconst u8* get_compressed_text_table(int table_index)\n")

        for i, lang in enumerate(Languages):
            cppFile.write(f"\n#{'el' if i > 0 else ''}if PTGB_BUILD_LANGUAGE == {lang.value + 1}\n")
            cppFile.write("{\n")
            cppFile.write("\tswitch (table_index)\n\t{\n")
            for section in textSections:
                cppFile.write("\tcase(" + section + "_INDEX):\n")
                if(section == "PTGB"):
                    cppFile.write("\tdefault:\n")
                cppFile.write("\t\treturn " + section + "_" + lang.name.lower() + "_lz10_bin;\n")
                cppFile.write("\t\tbreak;\n")
            cppFile.write("\t}\n")
            cppFile.write("}\n")
        cppFile.write(f"#else\n#error \"Unsupported PTGB_BUILD_LANGUAGE\"\n#endif")

def output_json_file():
    print("\tOutputting json file")
    for lang in Languages:
        for section in textSections:
            for item in mainDict[lang.name][section]:
                string = mainDict[lang.name][section][item]["bytes"].split(" ")
                outText = ""
                arr = charArrayOfLanguage[lang]["array"]
                for byte in string:
                    byte = arr[int(byte, 16)]
                    outText += str(byte)
                mainDict[lang.name][section][item]["text"] = outText

    with open(OUTPUT_JSON_PATH, 'w') as jsonFile:
        jsonFile.write(json.dumps(mainDict))
     

# This is for the font generation
fontDir = os.curdir
BACKGROUND_PAL_INDEX = 0
CELL_PAL_INDEX = 1

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

def build_h():
    print("Building font.h")
    with open(FONTS_H_PATH, 'w') as f:
        f.write(f'''#ifndef PTGB_BUILD_LANGUAGE
#error "PTGB_BUILD_LANGUAGE not defined"
#endif

#include "debug_mode.h"
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
    print("Generating font tables")
    for myFont in fonts.values():
        print(f'\t{myFont.fileName}')
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

mainDict = {}
textSections = []
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
charArrayOfLanguage = {
    Languages.Japanese: charArrays["Japanese"],
    Languages.English: charArrays["International"],
    Languages.French: charArrays["International"],
    Languages.German: charArrays["International"],
    Languages.Italian: charArrays["International"],
    Languages.SpanishEU: charArrays["International"],
    Languages.SpanishLA: charArrays["International"],
}

charConversionList = [
    # replaces the first char in the list with the latter
    ["'", "’"],
]

# Main
print("Running text_helper:")
generate_tables()
build_h()
download_xlsx_file()
test_if_release()
transfer_xlsx_to_dict()
generate_header_file()
generate_text_tables()
generate_cpp_file()
output_json_file()
print("text_helper finished!\n")
