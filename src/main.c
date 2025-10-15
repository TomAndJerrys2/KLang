#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm/machine.h"

int main(int argc, const char *argv[])
{

    init_machine();

    Chunk chunk;

    init_chunk(&chunk);

    // ts not that good atm
    int constant = add_constant(&chunk, 1.2);
    write_chunk(&chunk, OP_CONSTANT, 123);
    write_chunk(&chunk, constant, 123);

    write_chunk(&chunk, OP_NEGATE, 123);

    write_chunk(&chunk, OP_RETURN, 123);

    disassembleChunk(&chunk, "t:chunk");

    // bytecode -> virtual machine
    interpret(&chunk);

    // # add a cleanup function
    free_machine();
    free_chunk(&chunk);

    return 0;
}
