# import pandas lib as pd
import pandas as pd
import os 
from enum import Enum
import json
import requests
from collections import defaultdict
import copy
import math

update = True

print ("\n\n\n\n\n---------------")

if (update == True):

    url = 'https://docs.google.com/spreadsheets/d/14LLs5lLqWasFcssBmJdGXjjYxARAJBa_QUOUhXZt4v8/export?format=xlsx'

    response = requests.get(url)
    file_Path = 'text_helper\\text.xlsx'

    if response.status_code == 200:
        with open(file_Path, 'wb') as file:
            file.write(response.content)
        print('File downloaded successfully')
    else:
        print('Failed to download file')

engCharArray = [
0x20, 	0xC0, 	0xC1, 	0xC2, 	0xC7, 	0xC8, 	0xC9, 	0xCA, 	0xCB, 	0xCC, 	0x20, 	0xCE, 	0xCF, 	0xD2, 	0xD3, 	0xD4, 
0x152, 	0xD9, 	0xDA, 	0xDB, 	0xD1, 	0xDF, 	0xE0, 	0xE1, 	0x20, 	0xE7, 	0xE8, 	0xE9, 	0xEA, 	0xEB, 	0xEC, 	0x20, 
0xEE, 	0xEF, 	0xF2, 	0xF3, 	0xF4, 	0x153, 	0xF9, 	0xFA, 	0xFB, 	0xF1, 	0xBA, 	0xAA, 	0x1D49, 	0x26, 	0x2B, 	0x20, 
0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x3D, 	0x3B, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 
0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 
0x25AF, 	0xBF, 	0xA1, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0xCD, 	0x25, 	0x28, 	0x29, 	0x20, 	0x20, 
0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0xE2, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0xED, 
0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x2B07, 	0x2B05, 	0x27A1, 	0x20, 	0x20, 	0x20, 
0x20, 	0x20, 	0x20, 	0x20, 	0x1D49, 	0x3C, 	0x3E, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 
0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20, 
0x2B3, 	0x30, 	0x31, 	0x32, 	0x33, 	0x34, 	0x35, 	0x36, 	0x37, 	0x38, 	0x39, 	0x21, 	0x3F, 	0x2E, 	0x2D, 	0x30FB, 
0x2026, 	0x201C, 	0x201D, 	0x2018, 	0x2019, 	0x2642, 	0x2640, 	0x20, 	0x2C, 	0xD7, 	0x2F, 	0x41, 	0x42, 	0x43, 	0x44, 	0x45, 
0x46, 	0x47, 	0x48, 	0x49, 	0x4A, 	0x4B, 	0x4C, 	0x4D, 	0x4E, 	0x4F, 	0x50, 	0x51, 	0x52, 	0x53, 	0x54, 	0x55, 
0x56, 	0x57, 	0x58, 	0x59, 	0x5A, 	0x61, 	0x62, 	0x63, 	0x64, 	0x65, 	0x66, 	0x67, 	0x68, 	0x69, 	0x6A, 	0x6B, 
0x6C, 	0x6D, 	0x6E, 	0x6F, 	0x70, 	0x71, 	0x72, 	0x73, 	0x74, 	0x75, 	0x76, 	0x77, 	0x78, 	0x79, 	0x7A, 	0x25B6, 
0x3A, 	0xC4, 	0xD6, 	0xDC, 	0xE4, 	0xF6, 	0xFC, 	0x2A, 	0x20, 	0x20, 	0x15E, 	0x23C, 	0x206, 	0x1B2, 	0x147, 	0x19E, 
]

engCharWidthArray = [
    0x4, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x0, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 
0x8, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x0, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x0, 
0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x8, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x9, 	0x6, 	0x6, 	0x0, 
0x0, 	0x0, 	0x0, 	0x0, 	0xA, 	0x8, 	0x3, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 
0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 
0x6, 	0x6, 	0x4, 	0x8, 	0x8, 	0x8, 	0x7, 	0x8, 	0x8, 	0x4, 	0x6, 	0x6, 	0x4, 	0x4, 	0x0, 	0x0, 
0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x6, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x6, 
0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x7, 	0x7, 	0x7, 	0x7, 	0x2, 	0x3, 	0x4, 
0x5, 	0x5, 	0x6, 	0x7, 	0x5, 	0x6, 	0x6, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 
0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 
0x8, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x4, 	0x6, 	0x3, 	0x6, 	0x3, 
0x6, 	0x6, 	0x6, 	0x3, 	0x3, 	0x6, 	0x6, 	0x6, 	0x3, 	0x7, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 
0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 
0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x4, 	0x5, 	0x6, 
0x4, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x5, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x8, 
0x3, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x6, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x38, 	0x0, 	0x0, ]

jpnCharArray = [
0x20, 	0x3042, 	0x3044, 	0x3046, 	0x3048, 	0x304A, 	0x304B, 	0x304D, 	0x304F, 	0x3051, 	0x3053, 	0x3055, 	0x3057, 	0x3059, 	0x305B, 	0x305D, 
0x305F, 	0x3061, 	0x3064, 	0x3066, 	0x3068, 	0x306A, 	0x306B, 	0x306C, 	0x306D, 	0x306E, 	0x306F, 	0x3072, 	0x3075, 	0x3078, 	0x307B, 	0x307E, 
0x307F, 	0x3080, 	0x3081, 	0x3082, 	0x3084, 	0x3086, 	0x3088, 	0x3089, 	0x308A, 	0x308B, 	0x308C, 	0x308D, 	0x308F, 	0x3092, 	0x3093, 	0x3041, 
0x3043, 	0x3045, 	0x3047, 	0x3049, 	0x3083, 	0x3085, 	0x3087, 	0x304C, 	0x304E, 	0x3050, 	0x3052, 	0x3054, 	0x3056, 	0x3058, 	0x305A, 	0x305C, 
0x305E, 	0x3060, 	0x3062, 	0x3065, 	0x3067, 	0x3069, 	0x3070, 	0x3073, 	0x3076, 	0x3079, 	0x307C, 	0x3071, 	0x3074, 	0x3077, 	0x307A, 	0x307D, 
0x3063, 	0x30A2, 	0x30A4, 	0x30A6, 	0x30A8, 	0x30AA, 	0x30AB, 	0x30AD, 	0x30AF, 	0x30B1, 	0x30B3, 	0x30B5, 	0x30B7, 	0x30B9, 	0x30BB, 	0x30BD, 
0x30BF, 	0x30C1, 	0x30C4, 	0x30C6, 	0x30C8, 	0x30CA, 	0x30CB, 	0x30CC, 	0x30CD, 	0x30CE, 	0x30CF, 	0x30D2, 	0x30D5, 	0x30D8, 	0x30DB, 	0x30DE, 
0x30DF, 	0x30E0, 	0x30E1, 	0x30E2, 	0x30E4, 	0x30E6, 	0x30E8, 	0x30E9, 	0x30EA, 	0x20, 	0x30EC, 	0x30ED, 	0x30EF, 	0x30F2, 	0x30F3, 	0x30A1, 
0x30A3, 	0x30A5, 	0x30A7, 	0x30A9, 	0x30E3, 	0x30E5, 	0x30E7, 	0x30AC, 	0x30AE, 	0x30B0, 	0x30B2, 	0x30B4, 	0x30B6, 	0x30B8, 	0x30BA, 	0x30BC, 
0x30BE, 	0x30C0, 	0x30C2, 	0x30C5, 	0x30C7, 	0x30C9, 	0x30D0, 	0x30D3, 	0x30D6, 	0x30D9, 	0x30DC, 	0x30D1, 	0x30D4, 	0x30D7, 	0x30DA, 	0x30DD, 
0x30C3, 	0x30, 	0x31, 	0x32, 	0x33, 	0x34, 	0x35, 	0x36, 	0x37, 	0x38, 	0x39, 	0xFF01, 	0xFF1F, 	0x3002, 	0x30FC, 	0x30FB, 
0x30FB, 	0x300E, 	0x300F, 	0x300C, 	0x300D, 	0x2642, 	0x2640, 	0x5186, 	0x2E, 	0xD7, 	0x2F, 	0x41, 	0x42, 	0x43, 	0x44, 	0x45, 
0x46, 	0x47, 	0x48, 	0x49, 	0x4A, 	0x4B, 	0x4C, 	0x4D, 	0x4E, 	0x4F, 	0x50, 	0x51, 	0x52, 	0x53, 	0x54, 	0x55, 
0x56, 	0x57, 	0x58, 	0x59, 	0x5A, 	0x61, 	0x62, 	0x63, 	0x64, 	0x65, 	0x66, 	0x67, 	0x68, 	0x69, 	0x6A, 	0x6B, 
0x6C, 	0x6D, 	0x6E, 	0x6F, 	0x70, 	0x71, 	0x72, 	0x73, 	0x74, 	0x75, 	0x76, 	0x77, 	0x78, 	0x79, 	0x7A, 	0x25B6, 
0x3A, 	0xC4, 	0xD6, 	0xDC, 	0xE4, 	0xF6, 	0xFC, 	0x2A, 	0x20, 	0x20, 	0x15E, 	0x23C, 	0x206, 	0x1B2, 	0x147, 	0x19E, 
]

charConversionList = [
    # replaces the first char in the list with the latter
    ["'", "’"],
]

def convertByte(incoming, array):
    for pair in charConversionList:
        if incoming == ord(pair[0]):
            incoming = ord(pair[1])
            #print(f"Warning! {pair[0]} found, replacing with {pair[1]} !")
            next_key = max(mainDict[lang.name]["Warnings"].keys(), default =- 1) + 1
            mainDict[lang.name]["Warnings"][next_key] = f"Warning! {pair[0]} found, replacing with {pair[1]} !"
    
    
    index = 0
    for val in array:
        if val == incoming:
            return index
        index += 1
    #print(f"Error! No match found for char [ {chr(incoming)} ]!")
    
    next_key = max(mainDict[lang.name]["Errors"].keys(), default =- 1) + 1
    mainDict[lang.name]["Errors"][next_key] = f"Error! No match found for char [ {chr(incoming)} ]!"
    return 0
 
def SplitSentenceIntoLines(sentence, offset, pixelsPerChar, pixelsInLine):
    # If we can optimize this to remove the spaces, it could save a few bytes.

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
            if (pixelsPerChar == "Variable Latin Font"):
                wordLength += engCharWidthArray[convertByte(ord(char), engCharArray)]
                spaceLength = engCharWidthArray[convertByte(ord(' '), engCharArray)]
            else:
                wordLength += pixelsPerChar
                spaceLength = pixelsPerChar
        
        # See if the whole sentence is a newline
        if (sentence == "Ň"):
            outStr += "Ň"
            currLine = ""
            lineCount += 1
            offset = 0
            lineLength = 0
            currWordIndex += 1
            
        # See if the sentence is a new box
        elif(sentence == "Ş" or sentence == "ȼ"):
            outStr += sentence
            currLine = ""
            offset = 0
            lineLength = 0
            currWordIndex += 1
            
        # Test if the word is too long in general
        elif (wordLength > pixelsInLine):
            #print(f"ERROR: Word {word} exceeds alloted length")
            next_key = max(mainDict[lang.name]["Errors"].keys(), default =- 1) + 1
            mainDict[lang.name]["Errors"][next_key] = f"ERROR: Word {word} exceeds alloted length"
            currWordIndex += 1
            
        # Test if adding the word will go over our alloted space
        elif ((wordLength + lineLength + offset) <= pixelsInLine):
            # If not, add the word and increase the index
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
                
    outStr += currLine
    return lineLength + offset, lineCount, outStr

# -*- coding: utf-8 -*-
import re
alphabets= "([A-Za-z])"
prefixes = "(Mr|St|Mrs|Ms|Dr)[.]"
suffixes = "(Inc|Ltd|Jr|Sr|Co)"
starters = "(Mr|Mrs|Ms|Dr|Prof|Capt|Cpt|Lt|He\s|She\s|It\s|They\s|Their\s|Our\s|We\s|But\s|However\s|That\s|This\s|Wherever)"
acronyms = "([A-Z][.][A-Z][.](?:[A-Z][.])?)"
websites = "[.](com|net|org|io|gov|edu|me)"
digits = "([0-9])"
multiple_dots = r'\.{2,}'

def split_into_sentences(text: str) -> list[str]:
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
    text = re.sub("\s" + alphabets + "[.] "," \\1<prd> ",text)
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
    sentences = text.split("<stop>")
    sentences = [s.strip() for s in sentences]
    if sentences and not sentences[-1]: sentences = sentences[:-1]
    return sentences

class Languages(Enum):
    Japanese = 0
    English = 1
    French = 2
    German = 3
    Italian = 4
    SpanishEU = 5
    SpanishLA = 6

# read by default 1st sheet of an excel file
dir = os.curdir + "\\text_helper"

mainDict = {}

for lang in Languages:
    mainDict[lang.name] = {
    "PTGB": {},
    "RSEFRLG": {},
    "GB": {},
    "GENERAL": {},
    "CREDITS": {},
    "PKMN_NAMES": {},
    "Warnings" : {},
    "Errors": {},
}

def convert_item(ogDict):
    line = ogDict["bytes"]
    numLines = ogDict["numLines"]
    pixelsPerChar = ogDict["pixelsPerChar"]
    pixelsInLine = ogDict["pixelsInLine"]
    include_box_breaks = ogDict["includeBoxBreaks"]
    split_sents = split_into_sentences(line)
    index = 0
    outStr = ""
    currLine = 0
    offset = 0
    escapeCount = 0
    while index < len(split_sents) and escapeCount < 100:
        offset, recievedLine, out = SplitSentenceIntoLines(split_sents[index], offset, pixelsPerChar, pixelsInLine)
        currLine += recievedLine
        
        if (out == "ȼ"):
            offset = 0
            currLine = 0
            outStr = outStr[:-1]
            outStr += "ȼ"
            index += 1
        elif (currLine < numLines):
            #print(split_sents[index])
            index += 1
            outStr += out
        else:
            outStr = outStr[:-1]
            outStr += "ȼ" # new textbox character
            offset = 0
            currLine = 0
            escapeCount += 1
            #print(index)
            if not include_box_breaks:
                #print(f"ERROR! Made a line break when disabled, sentence \"{outStr}\" is too long!")
                next_key = max(mainDict[lang.name]["Errors"].keys(), default =- 1) + 1
                mainDict[lang.name]["Errors"][next_key] = f"ERROR! Made a line break when disabled, sentence \"{outStr}\" is too long!"
            
    if escapeCount == 100:
        #print(f"ERROR! Sentence \"{out}\" is too long!")
        next_key = max(mainDict[lang.name]["Errors"].keys(), default =- 1) + 1
        mainDict[lang.name]["Errors"][next_key] = f"ERROR! Sentence \"{out}\" is too long!"
            
    # Some cases that should be fixed
    exitLoop = False
    while(not exitLoop):
        newStr = outStr
        # A space right before a newline just takes up space
        newStr = newStr.replace(" Ň", "Ň")
        # Newlines shouldn't happen right after a new textbox
        newStr = newStr.replace("ȼŇ", "ȼ")
        # Nor should newlines be right before a new textbox
        newStr = newStr.replace("Ňȼ", "ȼ")
        # Nor should a new textbox be after a new textbox
        newStr = newStr.replace("ȼȼ", "ȼ")
        # Nor should a new scroll be after a new textbox
        newStr = newStr.replace("Şȼ", "Ş")
        # Nor should a new scroll be after a new textbox
        newStr = newStr.replace("ȼŞ", "ȼ")
        
        exitLoop = (newStr == outStr)
        outStr = newStr
    
    byteStr = ""
    if lang == Languages.Japanese:
        arr = jpnCharArray
    else:
        arr = engCharArray
    for char in outStr[:-1]:
        byteStr += hex(convertByte(ord(char), arr)) + ", "
    if outStr[-1] != ' ': # Check if the last char is a space
        byteStr += hex(convertByte(ord(outStr[-1]), arr)) + ", "
        
    byteStr += "0xff" 
    
    ogDict["bytes"] = byteStr
    return ogDict

print("\n\nStarting parse: \n")

currSheet = pd.read_excel(dir + "\\text.xlsx", sheet_name="Translations")
for row in currSheet.iterrows():
    #print(row)
    for lang in Languages:
        currRow = row[1]
        #print(currRow)
        offset = lang.value
        if (pd.isna(currRow.iloc[7 + lang.value])):
            offset = Languages.English.value
        mainDict[lang.name][currRow.iloc[0]][currRow.iloc[1]] = {"bytes": currRow.iloc[7 + offset],
                                                                    "numLines": currRow.iloc[2],
                                                                    "pixelsPerChar": currRow.iloc[3],
                                                                    "pixelsInLine" : currRow.iloc[4],
                                                                    "includeBoxBreaks": currRow.iloc[5],
                                                                    }
                
with open(os.curdir + '\\source\\translated_text.cpp', 'w') as cppFile:   
    cppFile.write("#include \"translated_text.h\"\n#include \"debug_mode.h\"\n#include \"pokemon_data.h\"\n")
    for lang in Languages: # putting this here is a really silly way to loop through all the CPP values but only write to H once
        with open (os.curdir + '\\include\\translated_text.h', 'w') as hFile:
            hFile.write("#ifndef DIALOGUE_H\n#define DIALOGUE_H\n\n#include <string>\n#include <tonc.h>\n\n")
            cppFile.write(f"#if PTGB_BUILD_LANGUAGE == {lang.value + 1}\n")


            # PTGB
            PTGB = mainDict[lang.name]["PTGB"]
            
            num = 0
            for key, line in PTGB.items():
                #print("--------")
                PTGB[key] = convert_item(line)
                cppFile.write("\nconst byte dialogueLine" + str(num) + "[] = {" + PTGB[key]["bytes"] + "};")
                hFile.write(f"#define {key} {num}\n")
                num += 1
                
            cppFile.write("\n")
            hFile.write(f"\n#define DIA_SIZE {num}\n#define DIA_END DIA_SIZE\n\n")

            cppFile.write("\n\nconst byte *dialogue[DIA_SIZE] = {")
            for i in range(num):
                cppFile.write("\ndialogueLine" + str(i) + ", ")
            cppFile.write("\n};\n")
            hFile.write("extern const byte *dialogue[DIA_SIZE];\n")

            # RSEFRLG
            RSEFRLG = mainDict[lang.name]["RSEFRLG"]
            for key, line in RSEFRLG.items():
                RSEFRLG[key] = convert_item(line)
                cppFile.write(f"\nconst byte {key}[] = {{{RSEFRLG[key]["bytes"]}}};")
                hFile.write(f"\nextern const byte {key}[];")

            # General
            GENERAL = mainDict[lang.name]["GENERAL"]
            for key, line in GENERAL.items():
                GENERAL[key] = convert_item(line)
                cppFile.write(f"const byte {key}[] = {{{GENERAL[key]["bytes"]}}};\n")
                hFile.write(f"extern const byte {key}[];\n")
            
            # Credits
            CREDITS = mainDict[lang.name]["CREDITS"]
            for key, line in CREDITS.items():
                CREDITS[key] = convert_item(line)
                cppFile.write(f"const byte {key}[] = {{{CREDITS[key]["bytes"]}}};\n")
                hFile.write(f"extern const byte {key}[];\n")
            cppFile.write("\n")
                
            # Pokemon Names
            PKMN_NAMES = mainDict[lang.name]["PKMN_NAMES"]
            
            num = 0
            for key, line in PKMN_NAMES.items():
                #print("--------")
                PKMN_NAMES[key] = convert_item(line)
                cppFile.write("const byte PKMN_NAMES" + str(num) + "[] = {" + PKMN_NAMES[key]["bytes"] + "};\n")
                num += 1
                
            cppFile.write("\n")

            cppFile.write(f"\n\nconst byte *PKMN_NAMES[{num}] = " + "{")
            for i in range(num):
                cppFile.write("\nPKMN_NAMES" + str(i) + ", ")
            cppFile.write("\n};\n")
            hFile.write(f"extern const byte *PKMN_NAMES[{num}];\n")

                
            
            
            
            cppFile.write("\n")
            cppFile.write(f"#endif\n\n\n")
            
            hFile.write("\n#endif")

for lang in Languages:
    for cat in mainDict[lang.name]:
        if cat in {"PTGB", "RSEFRLG", "GENERAL", "CREDITS", "PKMN_NAMES"}:
            for item in mainDict[lang.name][cat]:
                string = mainDict[lang.name][cat][item]["bytes"].split(", ")
                outText = ""
                if lang == Languages.Japanese:
                    arr = jpnCharArray
                else:
                    arr = engCharArray
                for byte in string:
                    byte = engCharArray[int(byte, 0)]
                    outText += chr(byte)
                mainDict[lang.name][cat][item]["text"] = outText
    
with open(dir + '\\output.json', 'w') as jsonFile:
    jsonFile.write(json.dumps(mainDict))
    
