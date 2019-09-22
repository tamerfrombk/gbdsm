#include <stack>

#include <vector>

#include "recursive_search_dasm.h"
#include "common.h"

gbdsm::RecursiveSearchDisassembler::RecursiveSearchDisassembler(Rom rom)
    : gbdsm::Disassembler(rom) {}

void gbdsm::RecursiveSearchDisassembler::disassemble(size_t start, size_t end)
{
    const std::set<uint16_t> visited = prune_visited_addresses(start, end);

    std::vector<uint16_t> data_addresses;
    for (size_t addr = 0; addr < rom_.size();) {
        // if we have visited this address, it's code
        if (visited.find(addr) != visited.end()) {
            const auto& inst = gbdsm::INSTRUCTIONS[rom_[addr]];
            if (inst.isPrefix()) {
                const auto& pre = gbdsm::PREFIXED_INSTRUCTIONS[rom_[addr + 1]];
                print_inst(addr, pre);
                addr += pre.length;
            } else {
                print_inst(addr, inst);
                addr += inst.length;
            }
        } else {
            data_addresses.push_back(addr);
            ++addr;
        }
    }

    // Now print data
    for (auto addr : data_addresses) {
        std::printf(".DB $%.2X ; %.4X\n", rom_[addr], addr);
    }
}

std::set<uint16_t> gbdsm::RecursiveSearchDisassembler::prune_visited_addresses(size_t start, size_t end) const
{
    std::stack<uint16_t> calls;

    std::set<uint16_t> visited;

    size_t PC = start;

    calls.push(PC);

    while (!calls.empty()) {
        // if we hit past the end, we return to the previous step
        if (PC >= end) {
            PC = calls.top();
            calls.pop();
        }

        const auto& inst = gbdsm::INSTRUCTIONS[rom_[PC]];
        if (inst.length == 0) {
            // If we hit an unknown instruction, this is probably due
            // to interpreting data as code.
            PC += 1;
        }
        else if (inst.isPrefix()) {
            const auto& pre = gbdsm::PREFIXED_INSTRUCTIONS[rom_[PC + 1]];
            visited.insert(PC);
            PC += pre.length;
        } else if (inst.isJump()) {
            if (inst.op == 0xE9) {
                gbdsm::error("JP (HL) instruction has been detected.\
                 This may cause disassembly errors with the recursive search algorithm.\
                 Consider using linear sweep instead.\n");
                visited.insert(PC);
                PC += inst.length;
            }
            // 16 bit immediate jumps
            else if (inst.op == 0xC3 || inst.op == 0xC2 || inst.op == 0xCA || inst.op == 0xD2 || inst.op == 0xDA) {
                uint16_t target = (uint16_t)rom_[PC + 1] | (uint16_t)rom_[PC + 2] << 8;
                // if we haven't visited the target yet, then add it for visitation
                if (visited.find(target) == visited.end()) {
                    calls.push(target);
                }
                visited.insert(PC);
                PC += inst.length;
            }
            // 8 bit immediate signed relative jumps
            else if (inst.op == 0x18 || inst.op == 0x20 || inst.op == 0x28 || inst.op == 0x30 || inst.op == 0x38) {
                uint16_t target = (int8_t)rom_[PC + 1] + PC + inst.length;
                // if we haven't visited the target yet, then add it for visitation
                if (visited.find(target) == visited.end()) {
                    calls.push(target);
                }
                visited.insert(PC);
                PC += inst.length;
            }
        }
        else if (inst.isCall()) {
            uint8_t next_instruction_address = PC + inst.length;

            calls.push(next_instruction_address);
            visited.insert(PC);

            PC = next_instruction_address;
        }
        else if (inst.isReturn()) {
            uint8_t next_instruction_address = calls.top();

            calls.pop();
            visited.insert(PC);

            PC = next_instruction_address;
        }
        else if (inst.isRestart()) {
            gbdsm::abort("RST support is not implemented yet.");
        }
        else {
            visited.insert(PC);
            PC += inst.length;
        }
    }

    return visited;
}
