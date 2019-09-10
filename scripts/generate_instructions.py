#!/usr/bin/env python3

#
# generate_ops.py 
#
# Author: Tamer Aly (2019)
#
# This script generates the opcodes table used by the disassembler from a CSV file.
#
#

from sys import argv
import json

class Instruction():

    def __init__(self, op, mnemonic, length, cycles):
        self.op = op 
        self.mnemonic = mnemonic 
        self.length = length
        self.cycles = cycles

    def __repr__(self):
        return '{{ {} , Instruction{{ {}, "{}", {}, {} }} }},'\
                .format(self.op, self.op, self.mnemonic, self.length, self.cycles)

def create_instruction(obj, is_prefixed):
    op = obj['addr']
    mnemonic = obj['mnemonic']
    length = int(obj['length'])
    cycles = int(obj['cycles'][0])

    return Instruction(op, mnemonic, length, cycles)

def generate_instructions(path):
    with open(path, 'r') as f:
        root = json.load(f)

        prefixed = root['cbprefixed']
        for obj in prefixed:
            inst = create_instruction(prefixed[obj], True)
            print(inst)
            
        unprefixed = root['unprefixed']
        for obj in unprefixed:
            inst = create_instruction(unprefixed[obj], False)
            print(inst)

def main():
    argc = len(argv)
    if argc != 2:
        print("Missing required JSON file!")
        exit()

    _, path = argv

    generate_instructions(path)

if __name__ == '__main__':
    main()
