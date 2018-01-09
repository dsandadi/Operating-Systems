/****************************************
           Assignment - 6
Name                    : Dinesh Sandadi
Zid                     : Z1797942
Section                 : 2
DateDue                 : 11/15/2017
TA                      : David Wiilams
Purpose                 : Simulation program for memory management using various
algorithms like first-fit and best-fit.
Execution               : make
./Assign6
 ****************************************/

#include "Block.h"
/************************
Function : MemoryBlock.
Purpose  : constructor.
***********************/
MemoryBlock::MemoryBlock(int startAddress, int blockSize, string process_id, string blockID) {
    this->start_address = startAddress;
    this->block_size = blockSize;
    this->mem_block_ID = blockID;
    this->process_ID = process_id;
}
/*******************************
Function : MemoryBlock.
Purpose  : Constructor.
******************************/

MemoryBlock::MemoryBlock(int startAddress, int size) {
    this->start_address = startAddress;
    this->block_size = size;
}
/*******************************
Function : printBlock.
Purpose  : Printst the details of the block.
Return   : Returns Nothing.
******************************/

void MemoryBlock::printBlock() {
    cout << "Start Address :" << this->start_address << "\n";
    cout << "Process ID :" << this->process_ID << "\n";
    cout << "Memory block ID :" << this->mem_block_ID << "\n";
    int size = this->block_size;
    cout << "Block Size :" << (size) << "\n";
    cout << " ===================================== \n";
}


