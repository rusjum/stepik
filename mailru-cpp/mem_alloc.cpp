#include <cstddef>
#include <iostream>
class SmallAllocator {
private:
        int total_memory = 1048576;
        char Memory[1048576];

public:
        static int get_block_size(char *block_start) {
            return *((int *) (block_start + 1));
        }
    
        static int get_info_size() {
            return sizeof(int) + sizeof(char);
        }
    
        static void occupy_block(char *block) {
            *block = 1;
        }
        
        static void free_block(char *block) {
            *block = 0;
        }
    
        static void init_block(char *start, int effective_size) {
            *start = 0;
            int *p = (int *) (start + 1);
            *p = effective_size;
        }
    
        SmallAllocator() {
            init_block(Memory, total_memory - get_info_size());
        }
        
        void *Alloc(unsigned int Size) {
            char *block_start = Memory;
            while (*block_start == 1 || (block_start < Memory + total_memory && get_block_size(block_start) < Size)) {
                block_start += get_block_size(block_start) + get_info_size();
            }
            if (block_start >= Memory + total_memory) {
                return NULL;
            }
            int block_size = get_block_size(block_start);
            if (block_size + 2 * get_info_size() > Size * 1.2) {
                char *new_block_start = block_start + block_size - Size;
                int old_block_new_size = block_size - Size - get_info_size();
                init_block(block_start, old_block_new_size);
                init_block(new_block_start, Size);
                block_start = new_block_start;
            }
            occupy_block(block_start);
            return (void *) (block_start + get_info_size());
        };
    
        void *ReAlloc(void *ptr, unsigned int s) {
            void *new_place = Alloc(s);
            if (new_place != NULL) {
                char *new_ptr = (char *) new_place;
                char *data_start = (char *) ptr;
                for (int i = 0; i < get_block_size(data_start - get_info_size()); ++i) {
                    new_ptr[i] = data_start[i];
                }
                Free(data_start);
            }
            return new_place;
        };
    
        void Free(void *ptr) {
            free_block((char *) (ptr) - get_info_size());
        };
};
