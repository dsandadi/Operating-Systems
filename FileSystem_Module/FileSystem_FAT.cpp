#include "FileSystem_FAT.h"

/*************
 * Function : printAllocatedBlocks
 * Purpose : Prints the allocated blocks.
 *
 */
void printAllocatedBlocks(int start) {
    int current = start;
    //    cerr << setw(50)<<left<<"";
    if (start == -1) {
        cerr << "NONE" << endl;
        return;
    }//iterating the FAT table.
    while (FATTable[current] != -1) {
        cerr << current << " ";
        current = FATTable[current];
    }
    cerr << current << "\n";
}

/*************
 * Function : getTotalSize
 * Purpose : returns total size of the directory.
 *
 */
int getTotalSize() {
    int totalSize = 0;
    for (list<Entry *>::iterator it = directory.begin(); it != directory.end(); it++) {
        Entry *currentEntry = *it;
        //cerr << "List of allocated blocks :" << endl;
        totalSize += currentEntry->size;
    }
    return totalSize;
}

/*************
 * Function : printDirectory
 * Purpose : Prints details of the directory.
 *
 */
void printDirectory() {
    int totalSize = 0;
    int totalFiles = 0;
    cerr << "\nDirectory contains " << directory.size() << " files. Total Size: " << getTotalSize() << " bytes.\n";
    cerr << "\nFiles in directory :" << endl;
    cerr << "--------------------------------------------\n";
    cerr << setw(20) << left << "FileName" << setw(15) << left << "Size" << setw(50) << left << "Blocks" << endl;
    for (list<Entry *>::iterator it = directory.begin(); it != directory.end(); it++) {
        Entry *currentEntry = *it;
        cerr << setw(20) << left << currentEntry->fileName;
        cerr << setw(15) << left << currentEntry->size;
        //cerr << "List of allocated blocks :" << endl;
        printAllocatedBlocks(currentEntry->start);
        totalSize += currentEntry->size;
        totalFiles++;
    }
    cerr << "File Allocation Table :" << endl;
    printFATTable();
}

/*************
 * Function : findLastBlock
 * Purpose : finds the last block whose entry is end.
 *
 */
int findLastBlock(int end) {
    for (int i = 0; i < LIMIT; i++) {
        if (FATTable[i] == end)
            return i;
    }
    return -1;
}

/*************
 * Function : processLine
 * Purpose : Processes each line and does the corresponding operation..
 *
 */
void processLine(string line) {

    istringstream iss(line);

    //extracting the transaction type.
    string transactionType;
    iss >> transactionType;
    //copy transaction
    if (transactionType == "C") {
        //cerr << "Transaction type : COPY"<< endl;

        string fileName;
        string newFileName;
        iss >> fileName;
        iss >> newFileName;
        //cerr << "COPY: Old file name : "<< fileName<< endl;
        //cerr << "COPY: New file name : "<< newFileName<< endl;
        copyFile(fileName, newFileName);
    }
    //Delete transaction.
    if (transactionType == "D") {
        // cerr << "Transaction type : DELETE"<< endl;
        string fileName;
        iss >> fileName;
        //  cerr << "DELETE : File name :"<< fileName << endl;
        deleteFile(fileName);

    }
    //New transaction.
    if (transactionType == "N") {
        // cerr << "Transaction type : NEWFILE"<< endl;

        string fileName;
        iss >> fileName;
        int fileSize;
        iss >> fileSize;
        if (directory.size() % 12 == 0) {
            Entry *ent = findFile(".");
            int newBlock = findFirstAvailableBlock();
            FATTable[ent->end] = newBlock;
            ent->end = newBlock;
            ent->size += BLOCK_SIZE;
            FATTable[newBlock] = -1;
        }
        createNewFile(fileName, fileSize);
    }
    // Modify transaction.
    if (transactionType == "M") {
        string fileName;
        int fileSize;
        iss >> fileName;
        iss >> fileSize;
        modifyFile(fileName, fileSize);
    }
    //Rename transaction.
    if (transactionType == "R") {
        string oldFileName;
        string newFileName;
        iss >> oldFileName;
        iss >> newFileName;
        renameFile(oldFileName, newFileName);
    }
}

/*************
 * Function : modifyFile
 * Purpose : Modifies the old file to new file.
 *
 */
void modifyFile(string oldfileName, int fileSize) {
    if (!searchFile(oldfileName)) {
        cerr << "ERROR: " << oldfileName << "not found. Cannot Modify.\n";
        return;
    }
    createNewFile("temporaryFile", fileSize);
    deleteFile(oldfileName);
    renameFile("temporaryFile", oldfileName);
}

/*************
 * Function : renameFile
 * Purpose : renames old file to new file.
 *
 */
void renameFile(string oldFileName, string newFileName) {
    if (!searchFile(oldFileName)) {
        cerr << "ERROR: " << oldFileName << " not found. Cannot Rename.\n";
        return;
    }
    if (searchFile(newFileName)) {
        cerr << newFileName << "already exists. Pick another name.\n";
        return;
    }
    Entry *entry = findFile(oldFileName);
    entry->fileName = newFileName;
}

/*************
 * Function : copyFile
 * Purpose : Copies the file.
 *
 */
void copyFile(string fileName, string newFileName) {
    Entry *entry = findFile(fileName);
    if (entry == nullptr) {
        cerr << "ERROR: " << fileName << "not found. Cannot Copy.\n";
        return;
    }
    if (searchFile(newFileName)) {
        cerr << "ERROR: " << fileName << " already exists. Cannot Copy.\n";
        return;
    }
    createNewFile(newFileName, entry->size);
}

/*************
 * Function : findFile
 * Purpose : Finds the file.
 *
 */
Entry *findFile(string fileName) {
    for (list<Entry *>::iterator it = directory.begin(); it != directory.end(); it++) {
        Entry *currentEntry = *it;
        if (currentEntry->fileName == fileName) {
            return currentEntry;
        }
    }
    return nullptr;
}

/*************
 * Function : readFile
 * Purpose : reads the given file.
 *
 */
void readFile(string path) {
    Entry *entry1 = new Entry("0-0-0", 0, 0, ".", 512);
    Entry *entry2 = new Entry("0-0-0", -1, -1, "..", 0);
    FATTable[0] = -1;
    directory.push_back(entry1);
    directory.push_back(entry2);

    ifstream readFile;// creating input file stream.
    readFile.open(path);// open the file.
    if (!readFile) {
        cerr << "Can't read the file.\n";
        exit(EXIT_FAILURE);
    }

    string line;
    int lineCount = 0;
    // reading lines from readFile.
    while (getline(readFile, line)) {
        // if the line is ? break the loop.
        if (line == "?") break;
        if (lineCount % 6 == 0)
            printDirectory();
        // call the processLine.
        processLine(line);
        lineCount++;
    }

}

/*************
 * Function : findFirstAvailable
 * Purpose : Finds the first available block.
 *
 */
int findFirstAvailableBlock() {
    for (int i = 0; i < TOTAL_BLOCKS; i++) {
        if (FATTable[i] == 0) {
            return i;
        }
    }
    return -1;
}

/*************
 * Function : populateFATTable
 * Purpose : populates the fat table using the required number of blocks.
 *
 */
int populateFatTable(int start, int requiredBlocks) {
    int prevAvailable = start;
    requiredBlocks -= 1;
    //cerr << requiredBlocks << endl;
    for (int i = start + 1; i < TOTAL_BLOCKS; i++) {
        if (requiredBlocks <= 0) {
            FATTable[prevAvailable] = -1;
            return prevAvailable;
        }
        if (FATTable[i] == 0) {
            FATTable[prevAvailable] = i;
            prevAvailable = i;
            requiredBlocks--;
        }
    }
    cerr << "\nThere is not enough memory available to fit the file, still " << requiredBlocks
         << "need to be fitted.\n";
    // set the last available position of fat table to -1.
    return -1;
}

/*************
 * Function : searchFile.
 * Purpose : searches for the fileName inside directory returns true if it is present else false.
 *
 */
bool searchFile(string fileName) {
    for (list<Entry *>::iterator it = directory.begin(); it != directory.end(); it++) {
        Entry *currentEntry = *it;
        if (currentEntry->fileName == fileName) {
            return true;
        }
    }
    return false;
}

/*************
 * Function : createNewFile.
 * Purpose : creates new file with given filename and filesize.
 *
 */

void createNewFile(string fileName, int fileSize) {
    if (searchFile(fileName)) {
        cerr << fileName << "already exists. Cannot create a new file.\n";
        return;
    }
    time_t rawTime;
    struct tm *timeInfo;
    time(&rawTime);
    timeInfo = localtime(&rawTime);
    string currentTime = asctime(timeInfo);
    int requiredBlocks = ceil(((float) (fileSize)) / BLOCK_SIZE);
    int start = -1, end = -1;
    if (requiredBlocks > 0) {
        start = findFirstAvailableBlock();
        // cerr << requiredBlocks << endl;
        end = populateFatTable(start, (int) requiredBlocks);
    }
    Entry *newEntry = new Entry(currentTime, start, end, fileName, fileSize);
    directory.push_back(newEntry);
}

/*************
 * Function : removeFromFatTable.
 * Purpose : removes an entry from the fat table.
 *
 */
void removeFromFatTable(int start) {
    int index = start;
    if (start == -1) {
        return;
    }
    while (FATTable[index] != -1) {
        int temp = FATTable[index];
        FATTable[index] = 0;
        index = temp;
    }
    FATTable[index] = 0;
}

/*************
 * Function : deleteFile
 * Purpose : Deletes the file with the given file name.
 *
 */
void deleteFile(string fileName) {
    // If the given file doesn't exist.
    if (!searchFile(fileName)) {
        cerr << "ERROR: " << fileName << "not found. Cannot Delete.\n";
        return;
    }
    // if exists.
    for (list<Entry *>::iterator it = directory.begin(); it != directory.end(); it++) {
        Entry *currentEntry = *it;
        if (currentEntry->fileName == fileName) {
            removeFromFatTable(currentEntry->start);
            it = directory.erase(it);
            // deleting the unused object from heap.
            delete (currentEntry);
            currentEntry = nullptr;
            return;
        }
    }
    if (directory.size() % 12 == 0) {
        Entry *ent = findFile(".");
        int lastBlock = findLastBlock(ent->end);
        FATTable[ent->end] = 0;
        FATTable[lastBlock] = -1;
        ent->end = lastBlock;
    }
}

/*************
 * Function : printFATTable
 * Purpose : prints the file accesss table.
 *
 */
void printFATTable() {
    cerr << "--------------------------------------------\n";
    for (int i = 0; i < LIMIT; i++) {
        if (i % 12 == 0) cerr << endl;
        cerr << setw(3) << left << FATTable[i] << "   ";
    }
    cerr << "\n--------------------------------------------\n";
}

/*************
 * Function : main
 * Purpose : driver of the program.
 *
 */
int main() {
    readFile("data.txt");
    printDirectory();
    cerr << "\n*******************************\n";
    return 0;
}
