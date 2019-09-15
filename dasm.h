#pragma once

#include <vector>
#include <cstdint>

#include "ops.h"

namespace gbdsm {

using Rom = std::vector<uint8_t>;

class Disassembler {
public:
    Disassembler(Rom rom);

    void disassemble();

private:
    void print_inst(unsigned pos, Instruction instruction);

    Rom rom_;
};

}
