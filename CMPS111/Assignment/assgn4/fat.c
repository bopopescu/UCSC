/*
CMPS 111 - 01 
Winter 2017
Darrell Long
Erik Andersen (Team captain)
Michael Cardoza
Yuzhuang Chen
Seongwoo Choi
The Fourth Assignment
*/

#define FUSE_USE_VERSION 26

#include <fuse.h>
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
static struct superblock super_block;
static int * FAT;
static struct file_list open_files;
static int diskImage;
unit32_t num_blocks;
unint32_t num_FAT_blocks;
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

/************************************************************
*   Core-Level Private API Definition                       *
*************************************************************/

/*
 * Writes the FAT back to disk. Returns -1 on error.
 */
int write_FAT (void) {
  if (lseek(dev_fd, BLOCK_SIZE, SEEK_SET) == -1) return -1;
  if (write(dev_fd, FAT, super_block.num_FAT_blocks * BLOCK_SIZE) == -1) return -1;
  return 0;
}

/*
 * Caches the FAT in memory. Returns -1 on error.
 */
int cache_FAT (void) {
  FAT = malloc(super_block.num_FAT_blocks * BLOCK_SIZE);
  if (lseek(dev_fd, BLOCK_SIZE, SEEK_SET) == -1) return -1;
  if (read(dev_fd, FAT, super_block.num_FAT_blocks * BLOCK_SIZE) == -1) return -1;
  return 0;
}

/*
 * Writes the superblock back to disk. Returns -1 on error.
 */
int write_superblock (void) {
  uint32_t * super_block_buf = calloc(1, BLOCK_SIZE);
  super_block_buf[0] = super_block.magic_num;
  super_block_buf[1] = super_block.num_blocks;
  super_block_buf[2] = super_block.num_FAT_blocks;
  super_block_buf[3] = super_block.block_size;
  super_block_buf[4] = super_block.root_start;
  if (lseek(dev_fd, 0, SEEK_SET) == -1) return -1;
  if (write(dev_fd, super_block_buf, BLOCK_SIZE) == -1) return -1;
  return 0;
}

/*
 * Caches the superblock in memory. Returns -1 on error.
 */
int cache_superblock (void) {
  uint32_t * super_block_buf = calloc(1,BLOCK_SIZE);
  if (lseek(dev_fd, 0, SEEK_SET) == -1) return -1;
  if (read(dev_fd, super_block_buf, BLOCK_SIZE) == -1) return -1;
  super_block.magic_num = super_block_buf[0];
  super_block.num_blocks = super_block_buf[1];
  super_block.num_FAT_blocks = super_block_buf[2];
  super_block.block_size = super_block_buf[3];
  super_block.root_start = super_block_buf[4];
  return 0;
}


/************************************************************
*   Core-Level Public API Definition                        *
*************************************************************/

/*
 * Returns a pointer to the superblock.
 */
struct superblock * get_superblock (void) {
  return &super_block;
}

/*
 * Closes the device. Returns -1 on error.
 */
int close_handler (void) {
  if (close(dev_fd) == -1) return -1;
  return 0;
}

/*
 * initializes the device. Returns -1 on error.
 */
int init_handler (char * dev_name) {
  dev_fd = open(dev_name, O_RDWR);
  if (dev_fd < 0) perror(NULL);
  if (cache_superblock() == -1) return -1;
  if (cache_FAT() == -1) return -1;
  init_list(&open_files);
  return 0;
}

struct fat_state {
	char *rootdir;
};

/*
CreateDiskImage
Disk Image that will be created in the underlying file system. 
Split up into superblock, file allocation table, and file data 
(includes directory entries).
*/

CreateDiskImage(imageName, num_blocks) {
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
	write(fd, (void*)(&num_FAT_blocks), 4));
	write(fd, (void*)(&num_blocks), 4);
	write(fd, (void*)(&rootBlock), 4);

	//fill our the rest of superblocks

	emptyBuffer = malloc(block_size-(4*5));
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

int FindOpenBlock() {
	block = rootBlock;
	while(allocationTable[block] != 0)
		block = block + 1;
	if (block < num_blocks) {
		byteArray[4096];
		for ()
	}
}

/*
Writes the allocation table to disk
*/
int WriteAllocationTabletoDisk() {
	offset = lseek(diskImage, block_size, SEEK_SET);
	result = write(diskImage, allocationTable, num_blocks * 4);
	if (result < 0) {
		error("Writing to disk image failed");
	}
}

/*
Directory Entry Functions
These following functions are used to read and write directory 
entries
*/

int GetDirectoryEntry (array) {
	dirent = new DirectoryEntry;
	//read filename string into structure
	for (i=0; i < 24; i++) {
		dirent.file_name[i] = array[i];
	}
		dirent.creationTime = *(size_t*)array[24];
		dirent.modificationTime = *(size_t)array[32];
		dirent.accessTime = *(size_t*)array[40];
		dirent.filLength =*(unit32_t*)array[48];
		dirent.startBlock = *(int *)array[52];
		dirent.flags = *(int *)array[56];
		dirent.unused =*(int *)array[60];
		return dirent;
}

/*
WriteDirectoryEntryToBuffer
Writes the directory entry struct to the buffer
*/

int WriteDirectoryEntryToBuffer(dirent, byteBuffer) {
	intBuffer = (int*)byteBuffer;
	longBuffer = (size_t*)byteBuffer;
	uintBuffer = (uint32_t*)byteBuffer;
	for (i=0; i <24; i++) {
		byteBuffer[i] = dirent.file_name[i];
	}
	longBuffer[3] = dirent.creationTime;
	longBuffer[4] = dirent.modificationTime;
	longBuffer[5] = dirent.accessTime;
	uintBuffer[12] = dirent.filLength;
	intBuffer[13] = dirent.start_block;
	intBuffer[14] = dirent.flags;
	intBuffer[15] = dirent.unused;
}

/*
removeDirectoryEntry
Removes the directory entry specified by path
*/

int removeDirectoryEntry (*path):
	check = traverseDirectoryTree(path);
	Previous = offset in block of check’s directory entry
	Next = offset in block of entry after check
	currentEntry = check
	currentBlock = block containing currentEntry’s directory entry done = false
	Buffer = array of size blockSize
	read currentBlock into memory
	while (not done) {
	tempBuf = array of size 64 if (next < blockSize)
	nextDirectoryEntry = getDirectoryEntry(address of buffer[next]) if (nextDirectoryEntry exists)
	Write directory entry to tempBuf
} else {
		Fill tempBuf with zeros
		done = true
		write tempBuf to block at offset previous previous = next
		next = next + 64
else if (allocationTable[currentBlock] > 0) next = 0
nextBlock = allocationTable[currentBlock]
nextbuffer = array of size blockSize
read nextBlock’s disk block into nextbuffer
nextDirectoryEntry = getDirectoryEntry(address of nextbuffer[next]); if(nextDirectoryEntry exists)
Write directory entry to tempBuf else
Fill tempBuf with zeros
done = 1
write tempBuf to current block at offset previous previous = 0
next = next + 64
currentBlock = nextBlock


/*
mkdir()
Creates a new directory by creating a new directory entry and writing
to the disk used for mkdir operation. 
*/

int mkdir(*path) {
	origLoc = 0;
	directoryEntry = traverseDirectoryTree (*path) 
	//get directory that willl contain our new directory
	block = newdirectoryEntry.start_block;
	while (allocationTable[block] > 0) {
		offset = lseek(diskImage, block_size*block, SEEK_SET);
		buffer = malloc(block_size[]);
		result = read(diskImage, buffer, block_size);
		if(result < 0) {
			error("can't read diskImage");
		} 
		read(diskImage, buffer, block_size);
		count = 0;
		while(buffer[count] != 0 && count < block_size) {
			count = count + 64;
		} if (count >= block_size) //there is no free space in block
			allocationTable[block] = findOpenBlock();
			block = allocationTable[block];
			allocationTable[block] =-2;
			buffer = malloc(block_size);
			count = 0;
		}
		dirent = new directoryEntry;
		dirent.file_name = node;
		dirent.creationTime = time (&rawtime);
		dirent.modificationTime = dirent.creationTime;
		dirent.accessTime = dirent.creationTime;
		dirent.fileLength = 0;
		dirent.start_block = findOpenBlock();
		dirent.flags = DIRECTORY;
		allocationTable[dirent.start_block] = -2;
		WriteAllocationTabletoDisk();
		WriteDirectoryEntryToBuffer(dirent, malloc(buffer[count]));
		offset = lseek(diskImage, block_size * block, SEEK_SET);
		result = write(diskImage, buffer, block_size);
		if (result < 0) {
			perror("can't read diskImage");
			return -1;
		}
		newDir.fileLength = new.fileLength + 64;
		newDir.modificationTime = time (&rawtime);
		newDir.accessTime = new Dir.modificationTime;

		if(origLoc > 0) {
			tempBuf = DirectoryEntry;
			WriteDirectoryEntryToBuffer(newDir, tempBuf);
			offset = lseek(diskImage, origLoc, SEEK_SET);
			result = write(diskImage, temoBuf, DirectoryEntry);
		}
		return 0;
	}
}

/*
opendir()
Opens directory and should not have to check for permissions. 
Used for the cd operation
*/

int opendir(*path, fi) {
	printf("opendir");
	if (*path == "..") {
		*path = prevpath;
	}
	int origLoc;
	DirectoryEntry check = traverseDirectoryTree (path, &origLoc);
	if (check == NULL && check.flags != IS_DIRECTORY) {
		return -ENOENT;
	}
	check.accessTime = time (&rawtime);
	if (origLoc > 0) {
		char tempBuf;
		
	}
}

int main (argc, argv) {
	if (argc < 2) {
		error("Insufficient argument");
	diskImage = open(argv[1], READ_WRITE);
	if (open(diskImage)= -1) {
		error ("Unable to open: " +argv[1]);
	buffer = malloc()
	}
	}
}

#define fat_DATA ((struct fat_state *) fuse_get_context()->private_date)

//Struct for directories
struct fat_dirp {
	DIR *dp;
	struct dirent *entry;
	off_t offset;
};

//Helper function for Directory pointer
static inline struct fat_dirp *get_dirp(struct fuse_file_info *fi)
{
	return (struct fat_dirp *) (uintptr_t) fi->fh;
};


static int fat_rename(const char *from, const char *to)
{
	printf("Rename is unsupported. Sorry.\n");

	return ENOENT;
}

// Create directory
static int fat_mkdir(const char *path, mode_t mode) 
{
	int stat;

	stat = mkdir(path, mode);
	if (stat == -1)
		return ENOENT;

	return 0;
}

// Remove directory
static int fat_rmdir(const char *path)
{
	int stat = read_entry_at(path, &e);
	struct entry e;

	if (status == -1) return -1;

	if (e.start_block == super_block.root_start) return -1;

	if (strcmp(e.file_name, "..") == 0) return -1;

	struct entry * es;
	int num_entries = read_entries_of(&e, &es);
	free(es);

	if (num_entries != 1) return -1;

	status = free_block 

	stat = rmdir(path);
	if (stat == -1)
		return ENOENT;
	
	return 0;
}

// Open file
static int fat_open(const char *path, struct fuse_file_info *fi)
{
	int fd;

	/* Need a path conversion function still
	char fpath[PATHMAX];
	fat_fullpath(fpath, path);
	*/
	fd = open(path, fi->flags);
	if(fd < 0){
	   printf("Error in open\n");
	   fd = ENOENT;
	}

	fi->fh = fd;

	return fd;
}

// Read data from an open file
static int fat_read(const char *path, char *buf, size_t size, off_t offset,
		      struct fuse_file_info *fi)
{
	int fd = 0;

	fd = pread(fi->fh, buf, size, offset); //atomic operation read
	if (fd < 0){
	   printf("Error in read\n");
	   fd = ENOENT;
        }

	return 0;
}

// Write data to an open file
static int fat_write(const char *path, const char *buf, size_t size, off_t offset
						       , struct fuse_file_info *fi )
{
	int stat;

	(void) path;
	stat = pwrite(fi->fh, buf, size, offset);
	if(stat == -1)
		return ENOENT;
	return stat;
}

static struct fuse_operations fat_oper = {
	.getattr	= fat_getattr,
	.fgetattr	= fat_fgetattr,
	.access		= fat_access,
	.readlink	= fat_readlink,
	.opendir	= fat_opendir,
	.readdir	= fat_readdir,
	.releasedir	= fat_releasedir,
	.mknod		= fat_mknod,
	.mkdir		= fat_mkdir,
	.symlink	= fat_symlink,
	.unlink		= fat_unlink,
	.rmdir		= fat_rmdir,
	.rename		= fat_rename,
	.link		= fat_link,
	.chmod		= fat_chmod,
	.truncate	= fat_truncate,
	.create		= fat_create,
	.open		= fat_open,
	.read		= fat_read,
	.write		= fat_write,
	.statfs		= fat_statfs,
	.flush		= fat_flush,
	.release	= fat_release,
	.fsync		= fat_fsync,
};

int main(int argc, char *argv[])
{
   struct fat_state *fat_data;

   fat_data = malloc(sizeof(struct fat_state));
   if(fat_data == NULL){
      printf("Error malloc in main\n");
   }

   //save the mount point
   fat_data->rootdir = argv[1];

   return fuse_main(argc, argv, &fat_oper, fat_data);
}