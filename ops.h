#pragma once

#include <unordered_map>
#include <string>
#include <cstdint>

namespace gbdsm {

struct Instruction {
    uint8_t op;
    std::string mnemonic;
    uint8_t length;
    uint8_t cycles;
};

extern std::unordered_map<uint8_t, Instruction> INSTRUCTIONS;
extern std::unordered_map<uint8_t, Instruction> PREFIXED_INSTRUCTIONS;

}
