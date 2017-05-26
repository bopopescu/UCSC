#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/time.h>
#include <sys/file.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <limits.h>

#define PATHMAX 4096

static int dev_fd;
static int i;
static struct superblock super_block;
static int * FAT;
static struct file_list open_files;
static int diskImage;
unsigned int unit32_t num_blocks;
unsigned int unint32_t num_FAT_blocks;
time_t rawtime;
struct tm * timeinfo;

/************************************************************
*   Core-Level Private API Declaration                      *
*************************************************************/

int write_FAT (void);
int cache_FAT (void);
int write_superblock (void);
int cache_superblock (void);

/************************************************************
*   Low-Level Private API Declaration                       *
*************************************************************/

int in_block_range(uint32_t); // TODO: Rename | Rethink
int get_free_block_num (void); // TODO: Rename | Rethink
int allocate_block (void);
int clear_block (uint32_t);
int next_block (uint32_t);
int free_block (uint32_t);
int read_block (uint32_t, void *);
int write_block (uint32_t, void *);
int count_blocks_from (uint32_t);
int free_blocks_from (uint32_t);
int read_blocks_from (uint32_t, void **);
int write_blocks_from (uint32_t, void **); // V.2 TODO: Write + incorporate during refactor

/************************************************************
*   Mid-Level Private API Declaration                       *
*************************************************************/

int read_entries_of (struct entry *, struct entry **);
int write_entries_of (struct entry *, struct entry **); // V.2 TODO: Write + incorporate during refactor
int forge_root_entry (struct entry *);
void read_entry (int, struct entry *); // Rethink
void write_entry (int, struct entry *); // Rethink

// TODO:
// Refactor or demote to low-level
int get_N_block(struct entry *, int);
int get_entry_block(const char *);

/************************************************************
*   END DECLARATIONS                                        *
*************************************************************/

void CreateDiskImage(imageName, num_blocks) {
	int magic_num = 0xfadedbee;
	int block_size = 1024;
	int num_FAT_blocks = (num_blocks/(block_size/4))+1;
	int rootBlock = num_FAT_blocks + 1;
	int fd = open(imageName(O_WRONLY));
		if (fd =! 1) { 
			return create(fd);
	}
	write(fd, (void*)(&magic_num), 4);
	write(fd, (void*)(&block_size), 4);
	write(fd, (void*)(&num_FAT_blocks), 4);
	write(fd, (void*)(&num_blocks), 4);
	write(fd, (void*)(&rootBlock), 4);

	//fill our the rest of superblocks

	int emptyBuffer = malloc(block_size-(4*5));
	write(fd, emptyBuffer, block_size-20);

	//fill in the file allocation table
	int allocationTable[num_blocks];
	for (i=0; i < rootBlock; i++) {
		allocationTable[i] = -1;
		allocationTable[rootBlock] = -2;
	}
	for (i=0; 0 < rootBlock; i++) {
		allocationTable[i] = -1;
	}
	allocationTable[rootBlock] = -2;
	for (i=0; i < (rootBlock + 1); num_blocks++) {
		allocationTable[i] = 0;
	}
	write(fd, allocationTable, num_blocks);
	// Fill in rest of last block in file allocation table
	buffer = size_t ((nBlocksInFileAllocationTable * block_size)-num_blocks);
	for(i=0; sizeof(buffer); i++){
		buffer[i] = -1
	}
	write(fd, buffer, sizeof(buffer));
	for (int i = 0; i < rootBlock; num_blocks++)
	{
		write(fd, emptyBuffer, block_size);
	}
}