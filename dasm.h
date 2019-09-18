#pragma once

#include <vector>
#include <cstdint>

#include "ops.h"

namespace gbdsm {

using Rom = std::vector<uint8_t>;

class Disassembler {
public:
    Disassembler(Rom rom);

    void disassemble(size_t start, size_t end);

private:
    void print_inst(size_t pos, const Instruction& instruction);

    Rom rom_;
};

}
