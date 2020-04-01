#pragma once
#include <vector>
/* Fast Allocator : A custom fast Allocator efficient allocation and deallocation of memory
*/

namespace fastAllocator {


	// Not yet implemented

	struct FixedAllocator {



		// Constructor to initialize the stuff
		FixedAllocator(size_t block_sz, unsigned char num_blocks) : block_size(block_sz), numBlocks_(num_blocks), allocChunk(nullptr), dllocChunk(nullptr) {}


		void* alloc() {
		
		/* Algorithm
		  IF allocChunk is 0 or allocChunk->block_Available is 0
			Perform a linear search in vector of chunks to find a chunk that has space
			If none found create a new chunk and perform allocation
			if Found then set allocChunk to  current chunk and GET the pointer to the block
			
		*/

			if (allocChunk == nullptr || allocChunk->blocks_available == 0) {
			
				for (auto chunk_el : chunks) {
					if (chunk_el.blocks_available != 0) {
					
						allocChunk = &chunk_el;
						dllocChunk = &chunk_el;
						return chunk_el.allocate(block_size);
					}
				

				}

				// No chunks were free so add a new chunk
				chunk new_chunk;
				new_chunk.init(block_size, numBlocks_);
				chunks.push_back(new_chunk);
				allocChunk = &chunks.back();
				dllocChunk = &chunks.back();
				return allocChunk->allocate(block_size);
			
			}

			return allocChunk->allocate(block_size);
		
		
		}
		void  dealloc(void * p ) {
		
		/* Algorithm: ( There is a very high scope of optimization here )
		   IF p is present in dllocChunk then the block inside dllocChunk gets deallocated
		   ELSE
		   perform a linear search to find the chunk and call dealloc in it
		*/
			if (dllocChunk->isPresent(p, block_size * numBlocks_)) {
			
				dllocChunk->dealloc(p, block_size);
			
			}
			
			for (auto chnk : chunks) {
			
				if (chnk.isPresent(p, block_size * numBlocks_)) {
					chnk.dealloc(p, block_size);
					dllocChunk = &chnk;
				
				}
			
			}
		
		
		}

	private:

		size_t block_size;
		unsigned char numBlocks_;
		struct chunk {
			unsigned char* pData;
			unsigned char  firstAvailableBlock;
			unsigned char  blocks_available;

			void init(size_t block_size, unsigned no_of_blocks) {

				/* Algorithm
				   ALLOCATE pData AS new unsigned char[block_size*no_of_blocks];
				   SET firstAvailableBlock TO 0
				   SET blocks_available TO no_of_blocks
				   ITERATE through each block and set  the first byte with index of next free block( This is freelist. It is a singly linked list where a free element
				   points to next element )
				   SET firstAvailableIndex AS *pData

				*/
				pData = new unsigned char[block_size * no_of_blocks];
				firstAvailableBlock = 0;
				blocks_available = no_of_blocks;
				unsigned char* temp_ptr = pData;

				for (int i = 0; i != no_of_blocks; temp_ptr += block_size) {
					*temp_ptr = ++i;
				}
			}

			void* allocate(size_t block_size) {
				/* Algorithm
				   IF blocks ARE available
				   CREATE and SET pResult= pData+ (firstAvailableBlock*block_size)
				   SET firstAvailableBlock TO *pResult
				   DECREMENT blocks_available by 1
				   return pResult;
				*/

				if (blocks_available) {
					unsigned char* pResult = pData + (firstAvailableBlock * block_size);
					firstAvailableBlock = *pResult;
					--blocks_available;
					return pResult;
				}

				return nullptr; // No blocks to allocate
			}
			void  dealloc(void* p, size_t block_size) {

				/* Algorithm
				  CREATE and SET ptr= static_cast<unsigned char*> ( p);
				  SET *ptr AS firstAvailableBlock
				  SET firstAvailableBlock = static_cast<char>((ptr-pData)/block_size);
				*/
				if (p < pData) return; // Wrong pointer

				unsigned char* release_mem = static_cast<unsigned char*>(p);
				*release_mem = firstAvailableBlock;

				// check Alignment
				if ((release_mem - pData) % block_size != 0) return;

				firstAvailableBlock = static_cast<unsigned char>((release_mem - pData) / block_size);

			}
			bool isPresent(void* p, size_t mem_size) {
				return  p > pData&& p < (pData + mem_size);
			}

		};
		
		typedef std::vector<chunk> Chunks;
		Chunks chunks;
		chunk* allocChunk;
		chunk* dllocChunk;

	};
	class SmallObjAllocator
	{
	public:
		SmallObjAllocator(std::size_t chunkSize,std::size_t maxObjectSize){
			
			while (maxObjectSize) {
				

			}
		
		}
		void* Allocate(std::size_t numBytes);
		void Deallocate(void* p, std::size_t size);
		
	private:
		std::vector<FixedAllocator> pool_;
		std::size_t chunkSize_;

	};

}

