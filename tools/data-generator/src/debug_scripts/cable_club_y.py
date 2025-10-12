#!/usr/bin/env python3

import bgb_link
import numpy as np
from io import BufferedReader
from typing import List

hs: int
ack: int
menu: int
trade: int
colosseum: int
cancel: int
preamble: int
trade_data: int
done: int

hs, ack, menu, trade, colosseum, cancel, preamble, trade_data, done = list(
    range(9))
state: int = hs
counter = 0

file_path = "to_compress/gb_gen1_payloads_Y.bin"
try:
    data = np.fromfile(file_path, dtype=np.uint8)
except FileNotFoundError:
    print(f"Error: The file '{file_path}' was not found.")
except Exception as e:
    print(f"An error occurred: {e}")
    
    
def cable_club(byte):
    global state, hs, ack, menu, trade, colosseum, cancel, trade_data

    if state == hs:
        if byte == 0x01:
            state = ack
            print("Connection established")
            return 0x02

    elif state == ack:
        if byte == 0x00:
            state = menu
            print("Menu")
            return 0x00

    elif state == menu:
        # 0xd1 battle
        # 0xd5 battle selected
        if byte == 0xd0:
            print("Battle")
            state = trade
            return 0xd5
        else:
            return byte

    elif state == trade:
        if byte == 0xfd:
            state = preamble
        return byte

    elif state == preamble:
        if byte != 0xfd:
            print("Sending data...")
            state = trade_data
            return exchange_parties(byte)
        return byte

    elif state == trade_data:
        # 0xfd = Preamble byte for array
        # 0xfe = No data
        return exchange_parties(byte)
    
    elif state == done:
        # Refill the code section
        return exchange_parties(byte)
    return byte


def exchange_parties(byte):
    global counter, data, state, done
    if counter < len(data):
        ret = data[counter]
        counter += 1
        print(hex(ret))
        return ret
    else:
        while(True):
            1==1
        state = done
        print("Restarting!")
        counter = 436
        ret = data[counter]
        counter += 1
        print(hex(ret))
        return ret


bgb_link.connect(8765, cable_club)
