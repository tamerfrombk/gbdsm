#include "recursive_search_dasm.h"
#include "common.h"

gbdsm::RecursiveSearchDisassembler::RecursiveSearchDisassembler(Rom rom)
    : gbdsm::Disassembler(rom) {}

void gbdsm::RecursiveSearchDisassembler::disassemble(size_t start, size_t end)
{
    GBDSM_UNUSED(start);
    GBDSM_UNUSED(end);

    gbdsm::abort("Recursive search unimplemented.\n");
}

void gbdsm::RecursiveSearchDisassembler::print_inst(size_t pos, const Instruction& inst)
{
    GBDSM_UNUSED(pos);
    GBDSM_UNUSED(inst);

    gbdsm::abort("Recursive search unimplemented.\n");
}
