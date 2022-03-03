#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "bitmap.h"
#include "hash.h"

#define MAX_NUM 10
#define NAME_LEN 20
#define CMD_LEN 100

int listNum;
int bitmapNum;
int hashNum;

typedef struct list_storage {
	
	char name[NAME_LEN];
	struct list* list;
} listStore;

/*
	struct list_elem {
	
		struct list_elem* prev;
		struct list_elem* next;
	}

	struct list {
		struct list_elem head;
		struct list_elem tail;
	}
	
	struct list_item {
	
		struct list_elem elem;
		int data;
	};
*/

listStore* listStorage[MAX_NUM];


/*
	typedef unsigned long elem_type;

	struct bitmap {
		
		size_t bit_cnt;    
		elem_type *bits;    
	};
*/


typedef struct bitmap_storage {
	
	char name[NAME_LEN];
	struct bitmap* bm;
} bitmapStore;

bitmapStore* bitmapStorage[MAX_NUM];



/*

	struct hash_elem {
		
		struct list_elem list_elem;
	};
	 
	struct hash {
		
		size_t elem_cnt;            
		size_t bucket_cnt;         
		struct list *buckets;    // head and tail of elems
		hash_hash_func *hash;     
		hash_less_func *less;     
		void *aux;             
	};
	
	struct hash_item {
	
		struct hash_elem h_elem;
		int data;
	};


*/

typedef struct hash_storage {
	
	char name[NAME_LEN];
	struct hash* hash;
} hashStore;

hashStore* hashStorage[MAX_NUM]; 





