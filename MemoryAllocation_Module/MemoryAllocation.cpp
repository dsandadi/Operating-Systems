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

#include "MemoryAllocation.h"
// included header files.
using namespace std;

// linkedlist for storing list of memory blocks in use.
list<MemoryBlock *> inUse;
// linkedlisr of memory blocks for storing the list of available blocks in use.
list<MemoryBlock *> avail;

/**************
 * Function : initialize()
 * Purpose  : Initializes avail and inuse list.
 * Returns  : Nothing.
 */
void initialize() {
	MemoryBlock *firstBlock = new MemoryBlock(3 * MB, MB);
	MemoryBlock *secondBlock = new MemoryBlock(4 * MB, 2 * MB);
	MemoryBlock *thirdBlock = new MemoryBlock(6 * MB, 2 * MB);
	MemoryBlock *forthBlock = new MemoryBlock(8 * MB, 4 * MB);
	MemoryBlock *fifthBlock = new MemoryBlock(12 * MB, 4 * MB);
	// pushes blocks in to avail list.
	avail.push_back(firstBlock);
	avail.push_back(secondBlock);
	avail.push_back(thirdBlock);
	avail.push_back(forthBlock);
	avail.push_back(fifthBlock);
}

/******************
 * Function  : printList.
 * Arguments : currrentList ( list of memory blocks)
 * Purpose   : prints the contents of the list.
 *
 */

void printList(list<MemoryBlock *> currentList) {
	list<MemoryBlock *>::iterator it;// creating an iterator.
	int total = 0;
	// if currentlist is not empty.
	if (!currentList.empty()) {
		cerr << "\n" << setw(25) << "Start Address" << "Size" << "\n";
		// iterating over currentlist.
		for (it = currentList.begin(); it != currentList.end(); it++) {
			MemoryBlock *currentBlock = *it;
			// printing details of the currentblock.
			cerr << setw(25) << currentBlock->start_address << currentBlock->block_size << "\n";
			//currentBlock->printBlock();
			total += currentBlock->block_size;
		}
	} else
		cerr << "\n(NONE)\n";
	cerr << "Total size of the list = " << (total)<<"\n";
}

/******************
 * Function  : processLine.
 * Arguments : line, fittype
 * Purpose   : Processes each line of the file using the type of fit.
 *
 */
void processLine(string line, string fitType) {
	istringstream iss(line);// initializing input string stream.
	string transactionType;
	iss >> transactionType;// extracting the transactiontype.
	//This is for loading the process in to the memory.
	cerr << "\n=============================================\n";
	// if transaction is load or allocate.
	if (transactionType == "L" || transactionType == "A") {

		int blockSize;
		string processName, processID;
		iss >> processID;// extracting processID.
		iss >> blockSize;// extracting blockSize.
		iss >> processName;
		if (transactionType == "L")
			cerr << "\nTransaction: Request to load process " << processID << ", Block ID " << processName << " using\n"
				<< blockSize << " bytes of memory." << "\n";
		if (transactionType == "A")
			cerr << "\n\nTransaction: Request to Allocate additional" << blockSize << " bytes for process " << processID
				<< ",\n"
				"Block ID: " << processName << "\n";
		// calling loadprocess.
		loadProcess(processID, blockSize, processName, fitType);
		return;
	}
	//This is for deallocating the process memory.
	if (transactionType == "D") {

		string processID;
		string processName;

		iss >> processID;
		iss >> processName;
		cerr << "\n\nTransaction: Request to DeAllocate Block ID: " << processName << " for process " << processID
			<< "\n";
		//calling deallocate process.
		deallocateProcess(processID, processName, transactionType);
		return;
	}
	//This is for terminating the process.
	if (transactionType == "T") {

		string processID;

		iss >> processID;
		cerr << "\n\nTransaction: Request to Terminate process " << processID << "\n";
		terminateProcess(processID);
		return;
	}

}

/******************
 * Function  : allocateProcess
 * Arguments : iterator, processID, requiredBlockSize, processName.
 * Purpose   : allocates the required memory block from list of available memory blocks.
 *
 */

void allocateProcess(list<MemoryBlock *>::iterator it, string processID, int requiredBlockSize, string processName) {
	MemoryBlock *current = *it;
	//dynamically creating new memory block.
	MemoryBlock *block1 = new MemoryBlock(current->start_address, requiredBlockSize, processID, processName);
	int start = current->start_address + requiredBlockSize;
	// Adding the allocated block to inUse and removing that block from avail list.
	inUse.push_front(block1);
	avail.erase(it++);

	//Creating a new block to hold the remaining memory.
	int newBlockSize = current->block_size - requiredBlockSize;
	if (newBlockSize > 0) {
		MemoryBlock *block2 = new MemoryBlock(start, newBlockSize, "", "");
		//inserting the block2 at the position iterator is currently pointing to.
		avail.insert(it, block2);
	}

}

/******************
 * Function  : findFirstFitBlock.
 * Arguments : requiredBlockSize.
 * Purpose   : finds the block needed by process using first fit algorithm.
 * Return value : Returns the iterator which points the required block.
 */

list<MemoryBlock *>::iterator findFirstFitBlock(int requiredBlockSize) {
	//initializing the iterator.
	list<MemoryBlock *>::iterator it = avail.begin();
	// looping through the iterator.
	while (it != avail.end()) {
		MemoryBlock *current = *it;
		// if the required block is found return the block.
		if (current->block_size >= requiredBlockSize) {
			cerr << "Sufficient memory block found! Size: " << current->block_size << "\n";
			cerr << "Allocating Memory to Block Successful!\n";
			return it;
		}
		it++;
	}
	return it;
}

/******************
 * Function  : findBestFitBlock.
 * Arguments : requiredBlockSize.
 * Purpose   : finds the block needed by process using best fit algorithm.
 * Return value : Returns the iterator which points the required block.
 */

list<MemoryBlock *>::iterator findBestFitBlock(int requiredBlockSize) {
	// initializing the iterator.
	list<MemoryBlock *>::iterator it = avail.begin();
	list<MemoryBlock *>::iterator minIterator = avail.end();
	int minValue = std::numeric_limits<int>::max();
	// iterating the avail to find the minimum fitting block.
	while (it != avail.end()) {
		MemoryBlock *currentBlock = *it;
		//MemoryBlock *minimum = *minIterator;
		int currentBlockSize = currentBlock->block_size;

		// if currentBlock size is greater than required block size
		if (currentBlockSize >= requiredBlockSize) {
			// if currentBlockSize is less than the already found minimum size.
			if (currentBlockSize < minValue) {
				minIterator = it;
				minValue = (*minIterator)->block_size;// set the minvalue.
			}
		}
		it++;
	}
	return minIterator;
}

/******************
 * Function  : loadProcess.
 * Arguments : processID,blockSize, processName, typeFit.
 * Purpose   : loads the process in to the memory.
 * Return value : Nothing.
 */
void loadProcess(string processID, int blockSize, string processName, string typeFit) {
	list<MemoryBlock *>::iterator it;
	// if fit type is firstFit.
	if (typeFit == "F") {
		it = findFirstFitBlock(blockSize);// find the required block.
		if (it == avail.end()) {
			cerr << "ERROR: ATTEMPT TO ALLOCATE MEMORY FAILED.\n"
				"NO BLOCK OF SUFFICIENT MEMORY AVAILABLE!";
			return;
		}
	}
	// if typeFit is bestfit.
	else if (typeFit == "B") {
		it = findBestFitBlock(blockSize);// find the required block.
		if (it == avail.end()) {
			cerr << "ERROR: ATTEMPT TO ALLOCATE MEMORY FAILED.\n"
				"NO BLOCK OF SUFFICIENT MEMORY AVAILABLE!";
			return;
		} else {
			cerr << "Sufficient memory block found! Size: " << (*it)->block_size << "\n";
			cerr << "Allocating Memory to Block Successful!\n";
		}
	}
	// allocate the process in to memory.
	allocateProcess(it, processID, blockSize, processName);

}

/******************
 * Function  : findTheProcess.
 * Arguments : processID,blockSize, processName.
 * Purpose   : Finds the memory block of the required processID and processName.
 * Return value : address of the required memoryblock.
 */
MemoryBlock *findTheProcess(string processID, string processName) {
	// iterating through the inUse list for finding the required memoryblock.
	for (list<MemoryBlock *>::iterator it = inUse.begin(); it != inUse.end(); it++) {
		MemoryBlock *currentBlock = *it;
		if ((currentBlock->process_ID == processID) && (currentBlock->mem_block_ID == processName)) {
			inUse.erase(it);
			return currentBlock;
		}
	}
	// return null if not found.
	return nullptr;
}

/******************
 * Function  : attachProcessToAvail
 * Arguments : MemoryBlock*.
 * Purpose   : Attach process to avail list in sequence of the starting address.
 * Return value : Nothing.
 */
void attachProcessToAvail(MemoryBlock *block) {
	// iterating through the avail list to find the right spot.
	for (list<MemoryBlock *>::iterator it = avail.begin(); it != avail.end(); it++) {
		MemoryBlock *currentBlock = *it;
		// if right spot is found.Insert in to avail list.
		if (currentBlock->start_address > block->start_address) {
			avail.insert(it, block);
			return;
		}
	}
}

/******************
 * Function  : normalizeTheAvailList.
 * Arguments : Nothing
 * Purpose   : Removes the redundant blocks from the avail list.
 * Return value : Nothing
 */

void normalizeTheAvailList() {
	MemoryBlock *currentBlock = *(avail.begin());
	int endingAddress = currentBlock->start_address + currentBlock->block_size;
	int startingAddress;
	list<MemoryBlock *>::iterator it = avail.begin();
	it++;
	// iterating the avail list.
	while (it != avail.end()) {
		currentBlock = *it;
		startingAddress = currentBlock->start_address;
		// if starting address is equal to ending address.
		if (endingAddress == startingAddress) {
			int blockSize = currentBlock->block_size;
			it--;// decrement the iterator.
			// get the previous block.
			MemoryBlock *prevBlock = *it;
			int newSize = prevBlock->block_size + blockSize;
			if (newSize < 4 * MB) {
				cerr << "Merging free memory block at address " << prevBlock->start_address
					<< " with free memory block at address " << currentBlock->start_address << " \n";
				// creating a new memory block with updataed values.
				MemoryBlock *newBlock = new MemoryBlock(prevBlock->start_address, newSize);
				// unplug it from the avail list.
				avail.erase(it++);
				// delete the prevBlock.
				delete (prevBlock);
				prevBlock = *it;
				// unplug from avail list.
				avail.erase(it++);
				//delete prevBlock
				delete (prevBlock);
				//set prevBlock to nullptr.
				prevBlock = nullptr;
				avail.insert(it, newBlock);// insert in to avail list.
				endingAddress = newBlock->start_address + newBlock->block_size;
				continue;
			} else {
				// keep calculating ending address.
				it++;
				endingAddress = startingAddress + blockSize;
				continue;
			}
		}
		endingAddress = currentBlock->block_size + startingAddress;
		it++;
	}

}

/******************
 * Function  : deallocateProcess.
 * Arguments : processID,processName, typeOfTrans.
 * Purpose   : deallocates the process.
 * Return value : Nothing.
 */

void deallocateProcess(string processID, string processName, string typeOfTrans) {
	//Finds the process and detaches it from the inUse list.
	MemoryBlock *block;
	// finds the process.
	block = findTheProcess(processID, processName);
	// if block is nullpointer.
	if (block == nullptr) {
		cerr << "\nERROR: ATTEMPT TO DEALLOCATE MEMORY FAILED. BLOCK NOT FOUND!\n";
		return;
	}
	// attach the process to the avail list in sequence.
	attachProcessToAvail(block);
	// normalizes the avail list.
	normalizeTheAvailList();
	// if type is deallocate.
	if (typeOfTrans == "D") {
		cerr << "\nMemory block is found!!\n";
		cerr << "Deallocation of block successful.\n";
	}
}

/******************
 * Function  : terminateProcess.
 * Arguments : processID.
 * Purpose   : terminates the process.
 * Return value : Nothing.
 */

void terminateProcess(string processID) {
	list<MemoryBlock *>::iterator it = inUse.begin();
	bool found = false;
	while (it != inUse.end()) {
		//currentBlock
		MemoryBlock *currentBlock = *it;
		//if currenBlock process_ID is equal to processID.
		if (currentBlock->process_ID == processID) {
			it++;
			found = true;
			deallocateProcess(processID, currentBlock->mem_block_ID, "T");// deallocate the Process.
		} else {
			it++;
		}
	}
	if (!found)
		cerr << "\nERROR: ATTEMPT TO TERMINATE PROCESS FAILED. PROCESS NOT FOUND!\n";
	else
		cerr<<"Process "<<processID<<" successfully terminated.\n";
}

/******************
 * Function  : readFile.
 * Arguments : path, fitType.
 * Purpose   : read file.
 * Return value : Nothing.
 */
void readFile(string path, string fitType) {
	if (!fitType.compare("B"))
		cerr << "\nYou chose to run the Best-Fit algorithm for Memory Management!\n";
	else if (!fitType.compare("F"))
		cerr << " \nYou chose to run the First-Fit algorithm for Memory Management!\n";
	else {
		cerr << "Invalid arguments, it should be B or F. \n";
		exit(-1);
	}
	cerr << "\nBeginning the Simulation Run now.\n";
	ifstream readFile;// creating input file stream.
	readFile.open(path);// open the file.
	if (!readFile) {
		cerr << "Can't read the file.\n";
		exit(EXIT_FAILURE);
	}

	string line;
	// reading lines from readFile.
	while (getline(readFile, line)) {
		// if the line is ? break the loop.
		if (line == "?") break;
		// call the processLine.
		processLine(line, fitType);
		cerr << "\nList of available blocks.";
		printList(avail);// prints the avail list
		cerr << "\n\nList of blocks currently in use.";
		printList(inUse);// prints the inUse list.

	}
}

/******************
 * Function  : main()
 * Arguments : int, char**
 * Purpose   : Entry point of the program.
 * Return value : integer value.
 */

int main(int argc, char **argv) {
	if (argc != 2) {
		cerr << "ERROR: USAGE: ./Assign6: INCORRECT NUMBER OF ARGUMENTS!\n";
		exit(-1);
	}
	cerr << left;
	initialize();

	readFile("data6.txt", argv[1]);
	cerr << "\n \n End of the Simulation!\n";
	cerr << "\nList of available blocks\n";
	printList(avail);
	cerr << "\nList of blocks currently in use";
	printList(inUse);

	return 0;

}
