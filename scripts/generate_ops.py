#!/usr/bin/env python3

#
# generate_ops.py 
# Author: Tamer Aly (2019)
#
# This script generates the opcodes table used by the disassembler from a CSV file.
#
#

from sys import argv

class Row():

    def __init__(self, op, mnemonic, length, cycles):
        self.op = op 
        self.mnemonic = mnemonic 
        self.length = length
        self.cycles = cycles

    def __repr__(self):
        return "{} {} {} {}".format(self.op, self.mnemonic, self.length, self.cycles)

def create_row(input):
    tokens = input.split(',')
    if len(tokens) != 11:
        print("Invalid input ", input)
        exit()

    return Row(tokens[0], tokens[1], tokens[2], tokens[3])

def process(list, f):
    for e in list:
        f(e)

def _print(list):
    process(list, print)


def to_cpp(row):
    print('{{ {} , Instruction{{ {}, "{}", {}, {} }} }},'\
.format(row.op, row.op, row.mnemonic, row.length, row.cycles))

def dump(list):
    process(list, to_cpp)

def read_csv(path):
    with open(path, 'r') as f:
        lines = f.readlines()
        rows = []
        for line in lines:
            rows.append(create_row(line))
        
        dump(rows)

def main():
    argc = len(argv)

    if argc != 2:
        print("Missing file!")
        exit()

    script, file = argv

    read_csv(file)


if __name__ == '__main__':
    main()
