#pragma once

#include "dasm.h"
#include "ops.h"

namespace gbdsm {

class RecursiveSearchDisassembler
    : public Disassembler {
public:
    RecursiveSearchDisassembler(Rom rom);

    virtual void disassemble(size_t start, size_t end) override;

private:
    void print_inst(size_t pos, const Instruction& inst);
};

}
