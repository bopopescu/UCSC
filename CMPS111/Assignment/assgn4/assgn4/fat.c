#define FUSE_USE_VERSION 30

#include <fuse.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/time.h>
#include <sys/file.h>
#include <fcntl.h>
#include <sys/types.h>
#include <limits.h>

#define PATHMAX 4096


struct file_list{


};
struct superblock{
 uint32_t magnum;
 uint32_t blocksFS;
 uint32_t blocksFAT;
 uint32_t startblock;
 uint32_t root;
};

struct direent{
 char filename[24];
 uint64_t chtime;
 uint64_t mtime;
 uint64_t atime;
 uint32_t filelength;
 uint32_t startblock;
 uint32_t flags;
 uint32_t unused;
};

static int dev_fd;
static int i;
static struct superblock super_block;
static int * FAT;
static struct file_list open_files;
static int diskImage;
uint32_t num_blocks;
uint32_t num_FAT_blocks;
time_t rawtime;
struct tm * timeinfo;


int write_FAT (void);
int cache_FAT (void);
int write_superblock (void);
int cache_superblock (void);


int in_block_range(uint32_t);
int get_free_block_num (void);
int allocate_block (void);
int clear_block (uint32_t);
int next_block (uint32_t);
int free_block (uint32_t);
int read_block (uint32_t, void *);
int write_block (uint32_t, void *);
int count_blocks_from (uint32_t);
int free_blocks_from (uint32_t);
int read_blocks_from (uint32_t, void **);
int write_blocks_from (uint32_t, void **);


int read_entries_of (struct direent *, struct direent **);
int write_entries_of (struct direent*, struct direent **);
int forge_root_entry (struct direent *);
void read_entry (int, struct direent *);
void write_entry (int, struct direent *);

int get_N_block(struct direent *, int);
int get_entry_block(const char *);


void disk(const char* img, uint32_t num_blocks) {
  uint32_t magic_num = 0xfadedbee;
  uint32_t block_size = 1024;
  uint32_t num_FAT_blocks = (num_blocks/(block_size/4))+1;
  uint32_t rootBlock = num_FAT_blocks + 1;
  int fd = open(img, O_WRONLY);
    if (fd != 1) { 
     creat(img, O_WRONLY);
  }
  write(fd, (void*)(&magic_num), 4);
  write(fd, (void*)(&block_size), 4);
  write(fd, (void*)(&num_FAT_blocks), 4);
  write(fd, (void*)(&num_blocks), 4);
  write(fd, (void*)(&rootBlock), 4);

  //fill the rest of our superblocks

  void* emptyBuffer = malloc(block_size-(4*5));
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
  uint32_t *buffer = malloc(sizeof((num_FAT_blocks * block_size)-num_blocks));
  for(i=0; i < sizeof(buffer); i++){
    buffer[i] = -1;
  }
  write(fd, buffer, sizeof(buffer));
  for (int i = 0; i < rootBlock; num_blocks++)
  {
    write(fd, emptyBuffer, block_size);
  }
}

static int fat_getattr(const char *path, struct stat *stbuf){
  int retval = 0;

  retval = lstat(path, stbuf);
  if(retval == -1)
    retval = -ENOENT;

  return retval;
}

static int fat_access(const char *path, int mask){
  int retval;

  retval = access(path, mask);
  if(retval == -1) return -errno;

  return 0;
}

static int fat_readdir(const char* path, void* buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info* fi){
   DIR *dr;
   struct dirent *d;
   
   (void) offset;
   (void) fi;
   dr = opendir(path);
   // struct stat st;
   // memset(&st, 0, sizeof(st));

   if (dr == NULL)
	                       return -ENOENT;
   // filler(buf, ".", NULL, 0);
   // filler(buf, "..", NULL, 0);
   int i = 0;
   
   while((d = readdir(dr)) != NULL){
     struct stat st;
     memset(&st, 0, sizeof(st));
     filler(buf, d->d_name, &st, 0);
   }  
   
   closedir(dr);
   return 0;
}

static int fat_symlink(const char *from, const char *to){
  int retval;

  retval = symlink(from, to);
  if(retval == -1) return -errno;

  return 0;
}

static int fat_link(const char *from, const char *to){
  int retval;

  retval = link(from, to);
  if(retval == -1) return -errno;

  return 0;
}

static int fat_rename(const char *from, const char *to){
  int retval;

  retval = rename(from, to);
  if(retval == -1) return -errno;

  return 0;
}  

static int fat_open(const char *path, struct fuse_file_info *fi)
{
   int retval;
  
   retval = open(path, O_CREAT);
   if( retval == -1) return -errno;

   close(retval);
   return 0;


}


static int fat_read(const char *path, char *buf, size_t size, off_t offset,
		                                      struct fuse_file_info *fi)
{
		(void) fi;
	       // int fd = open(path, O_CREAT | O_TRUNC | O_RDONLY);
		//		if (fd == -1)
		//					return -errno;

					int retval = pread(fi->fh, buf, size, offset);
						if (retval == -1)
									retval = -errno;

//							close(fd);
								return retval;



}

static int fat_write(const char* path, const char* buf, size_t size, off_t offset, struct fuse_file_info *fi){
  // int f = open(path, O_WRONLY);
  // if(f == -1) return -errno;

   int retval = pwrite(fi->fh, buf, size, offset);
   if(retval == -1) retval = -errno;

 //  close(f);
   return 0;
}	   

static int fat_truncate(const char *path, off_t offset){
   int retval;

   retval = truncate(path, offset);
   if(retval == -1) return -errno;

   return 0;
}   

static int fat_mkdir(const char* path, mode_t mode){
   int retval;
   
   retval = mkdir(path, mode);
   if(retval == -1) return -errno;
   int i = 0;
   return 0;   
}  	

static int fat_unlink(const char *path){
   int retval;

   retval = unlink(path);
   if(retval == -1) return -errno;

   return 0;
}

static int fat_rmdir(const char *path){
	   int retval;

	      retval = rmdir(path);
	         if(retval == -1) return -errno;

		    return 0;
}

static struct fuse_operations fat_ops = {
   .getattr = fat_getattr,
   .access = fat_access,
   .readdir = fat_readdir,
   .symlink = fat_symlink,
   .link = fat_link,
   .rename = fat_rename,
   .open = fat_open,
   .read = fat_read,
   .write = fat_write,
   .truncate = fat_truncate,
   .mkdir = fat_mkdir,
   .unlink = fat_unlink,
   .rmdir = fat_rmdir,
};

int main(int argc, char **argv)
{
	    umask(0);
	    return fuse_main(argc, argv, &fat_ops, NULL);
}
