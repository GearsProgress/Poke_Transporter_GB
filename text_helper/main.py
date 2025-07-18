# import pandas lib as pd
import pandas as pd
import os 
from enum import Enum
import json
import requests
from collections import defaultdict
import copy
import math
import sys

update = True

print ("\nRunning text_helper:\n\n\n\n---------------")

if (update == True):

    url = 'https://docs.google.com/spreadsheets/d/14LLs5lLqWasFcssBmJdGXjjYxARAJBa_QUOUhXZt4v8/export?format=xlsx'

    response = requests.get(url)
    file_Path = 'text_helper/text.xlsx'

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

jpnCharWidthArray = [
    0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 
0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 
0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 
0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 
0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 
0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 
0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 
0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 
0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 
0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 
0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 
0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 
0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 
0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 
0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 
0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x8, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x0, 	0x28, 	0x0, 	0x0, ]

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
            if (pixelsPerChar == "Variable"):
                if(lang == Languages.Japanese):
                    wordLength += jpnCharWidthArray[convertByte(ord(char), engCharArray)]
                    spaceLength = jpnCharWidthArray[convertByte(ord(' '), engCharArray)]
                else:
                    wordLength += engCharWidthArray[convertByte(ord(char), engCharArray)]
                    spaceLength = engCharWidthArray[convertByte(ord(' '), engCharArray)]
                    
            elif (pixelsPerChar == "Default"):
                if (lang == Languages.Japanese):
                    wordLength += 8
                    spaceLength = 8
                
                else:
                    wordLength += 6
                    spaceLength = 6
        
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
dir = os.curdir + "/text_helper"

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
        byteStr += f"{convertByte(ord(char), arr):02x} "
    if (len(outStr) > 0 and outStr[-1] != ' '): # Check if the last char is a space
        byteStr += f"{convertByte(ord(outStr[-1]), arr):02x} "
        
    byteStr += "ff"
    
    ogDict["bytes"] = byteStr
    return ogDict

def write_text_bin_file(filename, dictionary):
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
            dictionary[key] = convert_item(line)
            # store the offset of the line in the index as a 16 bit little endian value
            index[num * 2] = (current_offset & 0xFF)
            index[num * 2 + 1] = (current_offset >> 8) & 0xFF
            linedata = bytes.fromhex(dictionary[key]['bytes'])
            bindata.extend(linedata)
            current_offset += len(linedata)

            if len(linedata) > 1024:
                print(f"Error: entry '{key}' numBytes exceeds 1024 (got {len(linedata)})", file=sys.stderr)
                sys.exit(1)

            num += 1

        # Write the index and bindata to the file
        binFile.write(index)
        binFile.write(bindata)
        binFile.close()

def write_enum_to_header_file(hFile, prefix, dictionary):
    num = 0
    for key, line in dictionary.items():
        hFile.write(f"#define {prefix}{key} {num}\n")
        num += 1
    hFile.write("\n")
    return num


print("\n\nStarting parse: \n")

currSheet = pd.read_excel(dir + "/text.xlsx", sheet_name="Translations")
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

# generate the header file
with open (os.curdir + '/include/translated_text.h', 'w') as hFile:
    hFile.write("#ifndef DIALOGUE_H\n#define DIALOGUE_H\n\n#include <tonc.h>\n\n")

    # PTGB
    num = write_enum_to_header_file(hFile, "", mainDict[lang.name]["PTGB"])
    hFile.write(f"\n#define DIA_SIZE {num}\n#define DIA_END DIA_SIZE\n\n")

    # RSEFRLG
    write_enum_to_header_file(hFile, "RSEFRLG_", mainDict[lang.name]["RSEFRLG"])

    # GENERAL
    write_enum_to_header_file(hFile, "GENERAL_", mainDict[lang.name]["GENERAL"])

    # CREDITS
    write_enum_to_header_file(hFile, "CREDITS_", mainDict[lang.name]["CREDITS"])

    # PKMN_NAMES
    write_enum_to_header_file(hFile, "PKMN_NAMES_", mainDict[lang.name]["PKMN_NAMES"])

    hFile.write("/** Returns the LZ10 compressed PTGB text table.*/\n")
    hFile.write("const u8* get_compressed_PTGB_table();\n\n")
    hFile.write("/** Returns the LZ10 compressed RSEFRLG text table.*/\n")
    hFile.write("const u8* get_compressed_rsefrlg_table();\n\n")
    hFile.write("/** Returns the LZ10 compressed GENERAL text table.*/\n")
    hFile.write("const u8* get_compressed_general_table();\n\n")
    hFile.write("/** Returns the LZ10 compressed CREDITS text table.*/\n")
    hFile.write("const u8* get_compressed_credits_table();\n\n")
    hFile.write("/** Returns the LZ10 compressed PKMN_NAMES text table.*/\n")
    hFile.write("const u8* get_compressed_pkmn_names_table();\n\n")

    hFile.write("\n#endif")
    hFile.close()

# now generate the text tables
for lang in Languages:
    # PTGB
    table_file = os.curdir + '/to_compress/PTGB_' + lang.name.lower() + '.bin'
    write_text_bin_file(table_file, mainDict[lang.name]["PTGB"])

    # RSEFRLG
    table_file = os.curdir + '/to_compress/RSEFRLG_' + lang.name.lower() + '.bin'
    write_text_bin_file(table_file, mainDict[lang.name]["RSEFRLG"])

    # GENERAL
    table_file = os.curdir + '/to_compress/GENERAL_' + lang.name.lower() + '.bin'
    write_text_bin_file(table_file, mainDict[lang.name]["GENERAL"])

    # CREDITS
    table_file = os.curdir + '/to_compress/CREDITS_' + lang.name.lower() + '.bin'
    write_text_bin_file(table_file, mainDict[lang.name]["CREDITS"])

    # PKMN_NAMES
    table_file = os.curdir + '/to_compress/PKMN_NAMES_' + lang.name.lower() + '.bin'
    write_text_bin_file(table_file, mainDict[lang.name]["PKMN_NAMES"])

# now generate the cpp file.
with open(os.curdir + '/source/translated_text.cpp', 'w') as cppFile:
    cppFile.write("#include \"translated_text.h\"\n#include \"debug_mode.h\"\n#include \"pokemon_data.h\"\n")
    # generate includes for each language
    for lang in Languages:
        for cat in mainDict[lang.name]:
            if cat in {"PTGB", "RSEFRLG", "GENERAL", "CREDITS", "PKMN_NAMES"}:
                cppFile.write("#include \"" + cat.upper() + "_" + lang.name.lower() + "_lz10_bin.h\"\n")

    for lang in Languages:
        cppFile.write(f"\n#if PTGB_BUILD_LANGUAGE == {lang.value + 1}\n")
        # PTGB
        cppFile.write("const u8* get_compressed_PTGB_table()\n")
        cppFile.write("{\n")
        cppFile.write("\treturn PTGB_" + lang.name.lower() + "_lz10_bin;\n")
        cppFile.write("}\n\n")
        # RSEFRLG
        cppFile.write("const u8* get_compressed_rsefrlg_table()\n")
        cppFile.write("{\n")
        cppFile.write("\treturn RSEFRLG_" + lang.name.lower() + "_lz10_bin;\n")
        cppFile.write("}\n\n")
        # GENERAL
        cppFile.write("const u8* get_compressed_general_table()\n")
        cppFile.write("{\n")
        cppFile.write("\treturn GENERAL_" + lang.name.lower() + "_lz10_bin;\n")
        cppFile.write("}\n\n")
        # CREDITS
        cppFile.write("const u8* get_compressed_credits_table()\n")
        cppFile.write("{\n")
        cppFile.write("\treturn CREDITS_" + lang.name.lower() + "_lz10_bin;\n")
        cppFile.write("}\n\n")
        # PKMN_NAMES
        cppFile.write("const u8* get_compressed_pkmn_names_table()\n")
        cppFile.write("{\n")
        cppFile.write("\treturn PKMN_NAMES_" + lang.name.lower() + "_lz10_bin;\n")
        cppFile.write("}\n\n")

        cppFile.write(f"#endif\n\n\n")


for lang in Languages:
    for cat in mainDict[lang.name]:
        if cat in {"PTGB", "RSEFRLG", "GENERAL", "CREDITS", "PKMN_NAMES"}:
            for item in mainDict[lang.name][cat]:
                string = mainDict[lang.name][cat][item]["bytes"].split(" ")
                outText = ""
                if lang == Languages.Japanese:
                    arr = jpnCharArray
                else:
                    arr = engCharArray
                for byte in string:
                    byte = engCharArray[int(byte, 16)]
                    outText += chr(byte)
                mainDict[lang.name][cat][item]["text"] = outText
    
with open(dir + '/output.json', 'w') as jsonFile:
    jsonFile.write(json.dumps(mainDict))
    
