#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "bitmap.h"
#include "hash.h"
#include "main.h"
#include "structure_helper.h"
#include "limits.h"


void createHandler(char* dsType, char* dsName, char* bitNum) {
	
	int i, emptyIdx;

	if (strcmp(dsType, "list") == 0) {
		
		if (listNum >= MAX_NUM) {
			fprintf(stdout, "List Storage is Full \n");
			return;
		}
		
		for (i = 0; i < MAX_NUM; i++) {
			
			if (listStorage[i] && strcmp(listStorage[i]->name, dsName) == 0) {
				fprintf(stdout, "list %s already exists. \n", dsName);
				return;
			}
		}
		
		for (emptyIdx = 0; emptyIdx < MAX_NUM; emptyIdx++)
			if (listStorage[emptyIdx] == NULL) break;
		
		listStorage[emptyIdx] = (listStore*)malloc(sizeof(listStore));
		
		listStorage[emptyIdx]->list = (struct list*)malloc(sizeof(struct list));
		list_init(listStorage[emptyIdx]->list);
		
		strcpy(listStorage[emptyIdx]->name, dsName);
		
		listNum++;
		
		return;
	}
	else if (strcmp(dsType, "bitmap") == 0) {

		if (bitmapNum >= MAX_NUM) {
			fprintf(stdout, "Bitmap Storage is Full \n");
			return;
		}
		
		for (i = 0; i < MAX_NUM; i++) {
			
			if (bitmapStorage[i] && strcmp(bitmapStorage[i]->name, dsName) == 0) {
				fprintf(stdout, "bitmap %s already exists. \n", dsName);
				return;
			}
		}
		
		for (emptyIdx = 0; emptyIdx < MAX_NUM; emptyIdx++)
			if (bitmapStorage[emptyIdx] == NULL) break;
		
		int bNum = atoi(bitNum);
		
		bitmapStorage[emptyIdx] = (bitmapStore*)malloc(sizeof(bitmapStore));
		
		bitmapStorage[emptyIdx]->bm = bitmap_create(bNum);
		
		strcpy(bitmapStorage[emptyIdx]->name, dsName);
		
		bitmapNum++;
		
		return;
	}
	else if (strcmp(dsType, "hashtable") == 0) {
		
		if (hashNum >= MAX_NUM) {
			fprintf(stdout, "Hashtable Storage is Full \n");
			return;
		}
		
		for (i = 0; i < MAX_NUM; i++) {
			
			if (hashStorage[i] && strcmp(hashStorage[i]->name, dsName) == 0) {
				fprintf(stdout, "hashtable %s already exists. \n", dsName);
				return;
			}
		}
		
		for (emptyIdx = 0; emptyIdx < MAX_NUM; emptyIdx++)
			if (hashStorage[emptyIdx] == NULL) break;
		
		hashStorage[emptyIdx] = (hashStore*)malloc(sizeof(hashStore));
		hashStorage[emptyIdx]->hash = (struct hash*)malloc(sizeof(struct hash));
		strcpy(hashStorage[emptyIdx]->name, dsName);
		
		hash_hash_func* HH_Func;
		HH_Func = hash_func;
		
		hash_less_func* HL_Func;
		HL_Func = hash_less;
		
		hash_init(hashStorage[emptyIdx]->hash, HH_Func, HL_Func, NULL);
		
		hashNum++;
		
		//fprintf(stdout, "hash %s created \n", hashStorage[emptyIdx]->name);
		return;
	}
}


void dumpdataHandler(char* target) {
	
	int i = 0;
	int flag = 0;
	
	// search list
	for (i = 0; i < MAX_NUM; i++) {
		if (listStorage[i] && strcmp(listStorage[i]->name, target) == 0) {
			flag = 1;
			break;
		}
	}
	
	if (flag) {
		
		if (list_size(listStorage[i]->list) == 0) return;
		
		struct list_elem* elem = list_begin(listStorage[i]->list);
		
		while (list_end(listStorage[i]->list) != elem) {
			
			fprintf(stdout, "%d ", list_entry(elem, struct list_item, elem)->data);
			
			elem = list_next(elem);
		}
		fprintf(stdout, "\n");
		return;
	}


	//search bitmap
	for (i = 0; i < MAX_NUM; i++) {
		if (bitmapStorage[i] && strcmp(bitmapStorage[i]->name, target) == 0) {
			flag = 1;
			break;
		}
	}
	
	if (flag) {

		int idx = i;
		int num = bitmap_size(bitmapStorage[i]->bm);
		
		for (i = 0; i < num; i++) 
			fprintf(stdout, "%s", (bitmap_test(bitmapStorage[idx]->bm, i) ? "1" : "0"));
		
		fprintf(stdout, "\n");
		return;
	}
	
	
	//search hashtable
	for (i = 0; i < MAX_NUM; i++) {
		if (hashStorage[i] && strcmp(hashStorage[i]->name, target) == 0) {
			flag = 1;
			break;
		}
	}
	
	if (flag) {
		
		int idx = i;
		
		if (hash_size(hashStorage[idx]->hash) == 0) return;
		
		struct hash_iterator it;

		hash_first (&it, hashStorage[idx]->hash);
		
		while (hash_next (&it)) {
			
			struct hash_item* node = hash_entry (hash_cur (&it), struct hash_item, h_elem);
			
			fprintf(stdout, "%d ", node->data);
        }
		
		fprintf(stdout, "\n");
		
		return;
	}
}



void deleteHandler(char* target) {
	
	int i = 0;
	int flag = 0;
	
	
	// search list
	for (i = 0; i < MAX_NUM; i++) {
		if (listStorage[i] && strcmp(listStorage[i]->name, target) == 0) {
			flag = 1;
			break;
		}
	}
	
	if (flag) {
		
		struct list_elem* delElem = list_begin(listStorage[i]->list);
		
		while (list_end(listStorage[i]->list) != delElem) {
			
			struct list_item* delNode = list_entry(delElem, struct list_item, elem);
			
			delElem = list_remove(delElem);
			free(delNode);
		}
		
		free(listStorage[i]->list);
		free(listStorage[i]);
		listStorage[i] = NULL;
		
		listNum--;
		
		return;
	}
	
	
	//search bitmap
	for (i = 0; i < MAX_NUM; i++) {
		if (bitmapStorage[i] && strcmp(bitmapStorage[i]->name, target) == 0) {
			flag = 1;
			break;
		}
	}
	
	if (flag) {

		bitmap_destroy(bitmapStorage[i]->bm);
		free(bitmapStorage[i]);
		bitmapStorage[i] = NULL;
		
		bitmapNum--;
		
		return;
	}
	
	
	//search hashtable
	for (i = 0; i < MAX_NUM; i++) {
		if (hashStorage[i] && strcmp(hashStorage[i]->name, target) == 0) {
			flag = 1;
			break;
		}
	}
	
	if (flag) {
		
		hash_action_func* actionFunc;
		actionFunc = hash_destruct;
		
		hash_destroy(hashStorage[i]->hash, actionFunc);
		
		free(hashStorage[i]);
		hashStorage[i] = NULL;
		
		hashNum--;
		
		return;
	}
}

bool quitHandler() {
	
	int i;
	
	// delete list
	for (i = 0; i < MAX_NUM; i++) {
		
		if (listStorage[i]) {

			struct list_elem* delElem = list_begin(listStorage[i]->list);
		
			while (list_end(listStorage[i]->list) != delElem) {
				
				struct list_item* delNode = list_entry(delElem, struct list_item, elem);
				
				delElem = list_remove(delElem);
				free(delNode);
			}
			
			free(listStorage[i]->list);
			free(listStorage[i]);
			listStorage[i] = NULL;
			
			listNum--;	
		}
	}
	
	
	// delete bitmap
	for (i = 0; i < MAX_NUM; i++) {
		
		if (bitmapStorage[i]) {
			
			bitmap_destroy(bitmapStorage[i]->bm);
			free(bitmapStorage[i]);
			bitmapStorage[i] = NULL;
			
			bitmapNum--;
		}
	}
	
	
	// delete hashtable
	for (i = 0; i < MAX_NUM; i++) {
		
		if (hashStorage[i]) {

			hash_action_func* actionFunc;
			actionFunc = hash_destruct;
			
			hash_destroy(hashStorage[i]->hash, actionFunc);
			
			free(hashStorage[i]);
			hashStorage[i] = NULL;
			
			hashNum--;
		}
	}
	
	
	if (listNum == 0 && bitmapNum == 0 && hashNum == 0)
		return true;
	else 
		return false;
}
