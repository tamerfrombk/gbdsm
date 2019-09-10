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

    def __init__(self, op, mnemonic, length, cycles, args):
        self.op = op 
        self.mnemonic = mnemonic 
        self.length = length
        self.cycles = cycles
        self.args = args

    def __repr__(self):
        return '{{ {} , Instruction{{ {}, "{} {}", {}, {} }} }},'\
                .format(self.op, self.op, self.mnemonic, self.args, self.length, self.cycles)

def create_instruction(obj):
    op = obj['addr'].upper()
    mnemonic = obj['mnemonic'].upper()
    length = obj['length']
    cycles = obj['cycles'][0]

    args = "" 

    # add arguments
    if 'operand1' in obj:
        args += obj['operand1'].upper()

    if 'operand2' in obj:
        args += ','
        args += obj['operand2'].upper()

    # data arguments should be templated
    if "D8" in args:
       args = args.replace("D8", "%D8")
        
    if "D16" in args:
       args = args.replace("D16", "%D16")

    return Instruction(op, mnemonic, length, cycles, args)

def generate_instructions(path):
    with open(path, 'r') as f:
        root = json.load(f)

        levels = ['unprefixed', 'cbprefixed']
        for level in levels:
            prefix_type = root[level]
            for obj in prefix_type:
                inst = create_instruction(prefix_type[obj])
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
