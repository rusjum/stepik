#include <cstddef>
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

char *head;
char *init_ptr;
size_t init_size;

void occupy(char *cur);

size_t helper_info_size() {
    return sizeof(int) + sizeof(char) + sizeof(char*);
}


size_t total_helper_info_size() {
    return 2 * helper_info_size();
}


size_t get_size(char *block) {
    return *((int*) (block + 1));
}

// info layout char|int|char*
void init_info(char *ptr, size_t size) {
    *ptr = 0;
    ptr++;
    int *p = (int *) ptr;
    *p = size;
    p++;
    char **next = (char**) p;
    *next = NULL;
}

void init_block(void *start, size_t size) {
    char *start_ptr = (char *) start;
    char *end_ptr = start_ptr + size - helper_info_size();
    size_t effective_size = size - total_helper_info_size();
    init_info(start_ptr, effective_size);
    init_info(end_ptr, effective_size);
}


void mysetup(void *buf, size_t size) {
    init_block(buf, size);
    init_ptr = (char *) buf;
    init_size = size;
    head = (char *) buf;
}

void set_next(char *cur, char *next) {
    cur += sizeof(int) + sizeof(char);
    char **cur_next = (char **) cur;
    char *old_next = *cur_next;
    *cur_next = next;
    if (old_next != NULL) {
        set_next(next, old_next);
    }
}


void myfree(void *p) {
    char *cur = (char *) p;
    cur -= helper_info_size();
    if (*cur == 0)
        return;
    char * block_to_free = cur;
    size_t free_size = get_size(cur) + total_helper_info_size();

    if (cur - helper_info_size() > init_ptr) {
        char * prev = cur - helper_info_size();
        if (*prev == 0) {
            char *new_start = prev - get_size(prev) - helper_info_size();
            block_to_free = new_start;
            free_size += get_size(prev) + total_helper_info_size();
        }
    }
    char * next = cur + get_size(cur) + total_helper_info_size();
    if (next < init_ptr + init_size) {
        if (*next == 0) {
            size_t next_size = get_size(next) + total_helper_info_size();
            free_size += next_size;
        }
    }
    init_block(block_to_free, free_size);
}

void *myalloc(size_t size) {

    char * cur = head;
    while (cur != NULL) {
        if (*cur == 0) { // block is free
            size_t block_size = get_size(cur);
            if (block_size > size * 1.5) {
                size_t real_block_size = block_size + total_helper_info_size();
                size_t real_new_block_size = size + total_helper_info_size();
                char* new_block_ptr =  cur + real_block_size - real_new_block_size;
                init_block(cur, real_block_size - real_new_block_size);
                init_block(new_block_ptr, real_new_block_size);
                set_next(cur, new_block_ptr);
                cur = new_block_ptr;
                block_size = real_new_block_size - total_helper_info_size();
            }
            if (block_size >= size) {
                occupy(cur);
                return (void*) (cur + helper_info_size());
            }
        }

        cur += sizeof(char) + sizeof(int);
        cur = *((char**) cur);
    }
    return NULL;
}

void occupy(char *cur) {
    *cur = 1;
    cur += get_size(cur) + helper_info_size();
    *cur = 1;
}


//int main() {
//
//    size_t sz = 100000;
//    void * mem = (void*) new char[sz];
//    mysetup(mem, sz);
//    int max = 99900;
//    void *p = myalloc(max);
//    if (p == NULL)
//        cout << "fail\n";
//    myfree(p);
//
//
//    vector<void*> ret = {};
//    size_t  block_size  = 16;
//    int i = 0;
//    while(1) {
//        ret.push_back(myalloc(block_size));
//        if(ret[i] == NULL) break;
//        i++;
//    }
//    for(int j = 0; j < i; j++) {
//        int rnd = (rand()/(double)RAND_MAX*(i-1));
//        void *swp = ret[rnd];
//        ret[rnd] = ret[j];
//        ret[j] = swp;
//    }
//    for(int j = 0; j < i; j++) {
//        myfree(ret[j]);
//    }
//
//    p = myalloc(max);
//    if (p == NULL)
//        cout << "fail\n";
//    myfree(p);
//}