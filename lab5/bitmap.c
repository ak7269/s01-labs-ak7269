#include <errno.h>

#include "disk_map.h"
#include "panic.h"
#include "bitmap.h"

// Check to see if the block bitmap indicates that block 'blockno' is free.
// Return 1 if the block is free, 0 if not.
bool
block_is_free(uint32_t blockno)
{
	if (super == 0 || blockno >= super->s_nblocks)
		return 0;
	if (bitmap[blockno / 32] & (1 << (blockno % 32)))
		return 1;
	return 0;
}

// Mark a block free in the bitmap. 
// Silently does nothing if passed blockno == 0
void
free_block(uint32_t blockno)
{
	// Blockno zero is the null pointer of block numbers.
	// Simplify code paths elsewhere by silently doing nothing
	// on free_block(0).
	if (blockno == 0)
		return; 

	bitmap[blockno/32] |= 1<<(blockno%32);
}

// Search the bitmap for a free block and allocate it.  When you
// allocate a block, immediately flush the changed bitmap block
// to disk.
//
// Return block number allocated on success,
// -ENOSPC if we are out of blocks.
//
// Hint: use free_block as an example for manipulating the bitmap.
int
alloc_block(void)
{
	// The bitmap consists of one or more blocks.  A single bitmap block
	// contains the in-use bits for BLKBITSIZE blocks.  There are
	// super->s_nblocks blocks in the disk altogether.

	// LAB: Your code here.
	
 	int bnum;
	uint32_t length = super->s_nblocks/32;
	int i,j;
	
 	for (i = 0; i < length; i++)
	 {
		 
		 if(block_is_free(i)!=0)
		 {
			for(j=0;j<32;j++)
			{
				if((bitmap[i]>>j)& 0x1)
				{
      					bitmap[i] &=  ~(1u << j);
					flush_block(&bitmap[i]);
		 			bnum=j+i*32;
					return bnum;
				}
			}
			
   		}
		 else
			 continue;

	 }
		 
	//panic("alloc_block not implemented");

 	 return -ENOSPC;
	

}
