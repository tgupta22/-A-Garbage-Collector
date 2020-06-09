
#include "memlib.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "mm.h"
#include "hw4.h"

struct node * root_table[ROOT_NR] = {};

int in_use(unsigned int * hdrp) {
	  return (*hdrp) & 0x1u;
}

// the three lowest bits are not part of the size
// // 0x1 is already used for free blocks; we use 0x2
 #define MARK_BIT (((unsigned int)0x2))
//
// // marking related operations
 int is_marked(unsigned int * hdrp) {
   return ((*hdrp) & MARK_BIT) >> 1; // return 1 or 0
   }
//
   void mark(unsigned int * hdrp) {
     (*hdrp) |= MARK_BIT;
     }
//
     void unmark(unsigned int * hdrp) {
       (*hdrp) &= ~MARK_BIT;
       }
//
//       // same to GET_SIZE in mm.c
       unsigned int block_size(unsigned int * hdrp) {
         return (*hdrp) & (~7u);
         }
//
         void* next_hdrp(unsigned int * hdrp) {
           const unsigned int size = block_size(hdrp);
             if (size == 0) {
                 fprintf(stderr,"%s Panic, chunk is of zero size.\n", __func__);
                     exit(-1);
                       }
                         hdrp = (unsigned int *)(((char *)hdrp) + size);
                           return block_size(hdrp) ? hdrp : NULL;
                           }
//
                           void heap_stat(const char * msg)
                           {
                             void *hdrp = mm_first_hdr();
                               size_t nr_inuse = 0;
                                 size_t sz_inuse = 0;
                                   size_t nr_free = 0;
                                     size_t sz_free = 0;

                                       while (hdrp && block_size(hdrp)) {
                                           if (in_use(hdrp)) {
                                                 nr_inuse++;
                                                       sz_inuse += block_size(hdrp);
						       //                                                          
                                                           }
					   else {
                                                                 nr_free++;
                                                                       sz_free += block_size(hdrp);
                                                                           }
                                                                               if (is_marked(hdrp))
                                                                                     printf("%s WARNING: found a mark\n", __func__);
                                                                                         hdrp = next_hdrp(hdrp);
                                                                                           }
//
                                                                                             printf("%s: %s: heapsize %zu  inuse %zu %zu  free %zu %zu\n", __func__, msg,
                                                                                                   mem_heapsize(), nr_inuse, sz_inuse, nr_free, sz_free);
                                                                                                   }
//
//                                                                                                   // ========
//                                                                                                   // add helper functions here if any

                                                                                                   // garbage collection: Mark and Sweep
												   // /*    void gc() {


// Took help from Professor to get started and some implementation. 	      
	 void mark_block(void * hdrp  ){
	  int t = 0;
												   
	struct  node *block_pointer = root_table[t];
       // void *hdrp = mm_first_hdr();                                                                                                                 
	  // Checking if the current block is not equal to null
	 //         // then we can work our way forward, to mark/unmark accordingly.
														   //
														   //


	while(block_pointer == 0 ||  block_pointer !=  NULL)
	{

	if(hdrp != 0 &&  block_pointer == 0) {

			t++; // Incrementing here

		// From here, I have used the ideas from book page #904, piazza post @953 and 
		// Professors and TA's help
		

	   
	//   hdrp = next_hdrp(hdrp);

			
	   if(hdrp != NULL)

	   {
		   block_pointer = root_table[t];
	   }

	   hdrp = next_hdrp(hdrp);

	   if(hdrp == NULL)
	   {
		   return;
	   }

	}
	    

	

	else {
	


		if(is_marked(hdrp) == 0)
		{
			mark(hdrp);
		}

		else  if(is_marked(hdrp) == 1)

		{
			return;
		}

		hdrp = next_hdrp(hdrp);

		t++;

		// If the the next block is not equals to null then we point to it, otherwise we check in the root table.
		if(block_pointer->next != NULL)
		{
			block_pointer = block_pointer ->next;
		}

	       else {
		 if(t == ROOT_NR)
		 {

		//	 block_pointer = root_table[t];
		
		return;
		 }

		 else {

//			 return;

			 block_pointer =  root_table[t];


		 }

	}

	 } 
  
	 }
}

									

	// Accessing the root table with the pointer on the current block.
	//	node *currBlock = root_table[s];
                                                                      
	// Refering from the book page #904 and the The took help from piazza post @353 through Professor and TA.
 
void gc()
{

	struct node *Block = root_table[0];
	void *hdrp = mm_first_hdr();
	mark_block(hdrp);
  // Checking if hdrp is not equals to null


	// Implementing the algoithm to sweep and unmark the block. 
	while(hdrp != NULL) {

	if(is_marked(hdrp) == 0)
	{

	if(in_use(hdrp)){
          mm_free(hdrp+4); // The size is 4.

	}
	}		

//	hdrp = next_hdrp(hdrp);

	 if(is_marked(hdrp) == 1)
	{
        
 	 unmark(hdrp);
	}

	 hdrp = next_hdrp(hdrp);
	}
}


