#include "ops.h"
#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>

using Rom = std::vector<std::uint8_t>;

static void print_help()
{
    std::puts("Help.");
}

static Rom read_rom(const char* path)
{
     // open the file:
    std::ifstream file(path, std::ios::binary);

    // Stop eating new lines in binary mode!!!
    file.unsetf(std::ios::skipws);

    // get its size:
    std::streampos fileSize;

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // reserve capacity
    Rom vec;
    vec.reserve(fileSize);

    // read the data:
    vec.insert(vec.begin(),
               std::istream_iterator<std::uint8_t>(file),
               std::istream_iterator<std::uint8_t>());

    return vec;
}

static void disassemble(const Rom& rom)
{
    for (auto b : rom) {
        std::printf("%.2X\n", b);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::puts("Need input ROM.");
        print_help();
        return 1;
    }

    auto rom = read_rom(argv[1]);
    if (rom.empty()) {
        std::printf("Can't read %s.\n", argv[1]);
        return 1;
    }

    disassemble(rom);
}
