#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "hash_helper.h"
#include "hash.h"

void hashHandlerTwoArgs(char* option, char* hashName) {
	
	int i;
	hashStore* curHash;
	int isFound = 0;
	
	if (strlen(hashName) == 0) {
		
		fprintf(stdout, "No Name for list \n");
		return;
	}
	
	for (i = 0 ; i < MAX_NUM; i++) {
		
		if (hashStorage[i] && strcmp(hashStorage[i]->name, hashName) == 0) {
			
			isFound = 1;
			curHash = hashStorage[i];
			break;
		}
	}
	if (!isFound) {
		fprintf(stdout, "Hash Not Found \n");
		return;
	}	
	
	
	if (strcmp(option, "hash_size") == 0) {
		
		fprintf(stdout, "%zu \n", hash_size(curHash->hash));
		return;
	}
	else if (strcmp(option, "hash_empty") == 0) {
		
		fprintf(stdout, "%s \n", (hash_empty(curHash->hash) ? "true" : "false"));
	}
	else if (strcmp(option, "hash_clear") == 0) {
		
		hash_clear(curHash->hash, NULL);
		return;
	}
	
}

void hashHandlerThreeArgs(char* option, char* hashName, char* param) {
	
	int i;
	int num = atoi(param);
	hashStore* curHash;
	int isFound = 0;
	
	if (strlen(hashName) == 0) {
		
		fprintf(stdout, "No Name for list \n");
		return;
	}
	
	for (i = 0 ; i < MAX_NUM; i++) {
		
		if (hashStorage[i] && strcmp(hashStorage[i]->name, hashName) == 0) {
			
			isFound = 1;
			curHash = hashStorage[i];
			break;
		}
	}
	if (!isFound) {
		fprintf(stdout, "Hash Not Found \n");
		return;
	}	
	
	
	if (strcmp(option, "hash_apply") == 0) {
		
		hash_action_func* actionFunc;
		
		if (strcmp(param, "square") == 0) 
			actionFunc = hash_square;
		else if (strcmp(param, "triple") == 0) 
			actionFunc = hash_triple;
		else {
			fprintf(stdout, "Invalid command \n");
			return;
		}
		
		hash_apply(curHash->hash, actionFunc);
		return;
	}
	else if (strcmp(option, "hash_insert") == 0) {
		
		struct hash_item* newHash = (struct hash_item*)malloc(sizeof(struct hash_item));
		newHash->data = num;
		
		hash_insert(curHash->hash, &(newHash->h_elem));
		
		return;
	}
	else if (strcmp(option, "hash_delete") == 0) {
		
		struct hash_item* delHash = (struct hash_item*)malloc(sizeof(struct hash_item));
		delHash->data = num;
		
		hash_delete(curHash->hash, &(delHash->h_elem));
		return;
	}
	else if (strcmp(option, "hash_find") == 0) {
		
		struct hash_item* findHash = (struct hash_item*)malloc(sizeof(struct hash_item));
		findHash->data = num;
		
		struct hash_elem* elemFind = hash_find(curHash->hash, &(findHash->h_elem));
		
		if (elemFind) {
			
			fprintf(stdout, "%d \n", hash_entry(elemFind, struct hash_item, h_elem)->data);
		}
		
		return;
	}
	else if (strcmp(option, "hash_replace") == 0) {
		
		struct hash_item* repHash = (struct hash_item*)malloc(sizeof(struct hash_item));
		repHash->data = num;
		
		hash_replace(curHash->hash, &(repHash->h_elem));
		return;	
	}
}