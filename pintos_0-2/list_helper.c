#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "main.h"
#include "list_helper.h"
#include "limits.h"

void listHandlerTwoArgs (char* option, char* listName) {
	
	int i;
	listStore* curList;
	int isFound = 0;
	
	if (strlen(listName) == 0) {
		
		fprintf(stdout, "No Name for list \n");
		return;
	}
	
	for (i = 0 ; i < MAX_NUM; i++) {
		
		if (listStorage[i] && strcmp(listStorage[i]->name, listName) == 0) {
			
			isFound = 1;
			curList = listStorage[i];
			break;
		}
	}
	if (!isFound) {
		fprintf(stdout, "List Not Found \n");
		return;
	}
	
	
	
	if (strcmp(option, "list_front") == 0) {
		
		struct list_elem* Node = list_front(curList->list);
		fprintf(stdout, "%d \n", list_entry(Node, struct list_item, elem)->data);
		return;
	}
	else if (strcmp(option, "list_back") == 0) {
		
		struct list_elem* Node = list_back(curList->list);
		fprintf(stdout, "%d \n", list_entry(Node, struct list_item, elem)->data);
		return;
	}	
	else if (strcmp(option, "list_empty") == 0) {
		
		if (list_empty(curList->list))
			fprintf(stdout, "true \n");
		else
			fprintf(stdout, "false \n");
		return;
	}
	else if (strcmp(option, "list_size") == 0) {
			
		fprintf(stdout, "%zu \n", list_size(curList->list));
		return;
	}
	else if (strcmp(option, "list_max") == 0) {
		
		list_less_func* myFunc;
		myFunc = isLess;

		struct list_elem* Node = list_max(curList->list, myFunc, NULL);
		fprintf(stdout, "%d \n", list_entry(Node, struct list_item, elem)->data);
		
		return;
	}
	else if (strcmp(option, "list_min") == 0) {
		
		list_less_func* myFunc;
		myFunc = isLess;

		struct list_elem* Node = list_min(curList->list, myFunc, NULL);
		fprintf(stdout, "%d \n", list_entry(Node, struct list_item, elem)->data);

		return;
	}
	else if (strcmp(option, "list_reverse") == 0){

		list_reverse(curList->list);
		return;
	}
	else if (strcmp(option, "list_sort") == 0) {
		
		list_less_func* myFunc;
		myFunc = isLess;

		list_sort(curList->list, myFunc, NULL);

		return;
	}
	else if (strcmp(option, "list_pop_back") == 0) {
		
		list_pop_back(curList->list);
		return;
	}
	else if (strcmp(option, "list_pop_front") == 0) {
		
		list_pop_front(curList->list);
		return;
	}
	else if (strcmp(option, "list_unique") == 0) {
		
		list_less_func* myFunc;
		myFunc = isLess;
		
		list_unique(curList->list, NULL, myFunc, NULL);
	}
	else if (strcmp(option, "list_shuffle") == 0) {
		
		list_shuffle(curList->list);
		return;
	}
}



void listHandlerThreeArgs(char* option, char* listName, char* target) {
	
	int i;
	listStore* curList;
	int isFound = 0;
	
	if (strlen(listName) == 0) {
		
		fprintf(stdout, "No Name for list \n");
		return;
	}
	
	for (i = 0 ; i < MAX_NUM; i++) {
		
		if (listStorage[i] && strcmp(listStorage[i]->name, listName) == 0) {
			
			isFound = 1;
			curList = listStorage[i];
			break;
		}
	}
	if (!isFound) {
		fprintf(stdout, "List Not Found \n");
		return;
	}
	
	
	if (strcmp(option, "list_unique") == 0) {
		
		listStore* targetList;
			
		for (i = 0; i < listNum; i++) {
				
			if (strcmp(listStorage[i]->name, target) == 0) {
					
				targetList = listStorage[i];
				break;
			}
		}
			
		if (i >= listNum) {
			fprintf(stdout, "%s Not Found \n", target);
			return;
		}
		
		list_less_func* myFunc;
		myFunc = isLess;
		
		list_unique(curList->list, targetList->list, myFunc, NULL);
		return;
	}
	
	int num = atoi(target);
	
	if (strcmp(option, "list_remove") == 0) {
		
		int nodeCnt = list_size(curList->list);
		
		//fprintf(stdout, "node cnt: %d \n", nodeCnt);
		
		if (num >= nodeCnt || num < 0) {
			fprintf(stdout, "node #%d does not exist. \n", num);
			return;
		}
		
		struct list_elem* targetElem = list_begin(curList->list);
		
		for (i = 0; i < num; i++)
			targetElem = list_next(targetElem);
		
		list_remove(targetElem);
		return;
	}
	
	struct list_item* newNode = (struct list_item*)malloc(sizeof(struct list_item));
	newNode->data = num;
	
	if (strcmp(option, "list_push_back") == 0) {
		
		list_push_back(curList->list, &(newNode->elem));
		return;
	}
	else if(strcmp(option, "list_push_front") == 0) {
		
		list_push_front(curList->list, &(newNode->elem));
		return;
	}
	else if (strcmp(option, "list_insert_ordered") == 0) {
		
		list_less_func* myFunc;
		myFunc = isLess;
		
		list_insert_ordered(curList->list, &(newNode->elem), myFunc, NULL);
		return;
	}
}


void listHandlerFourArgs(char* option, char* listName, char* param1, char* param2) {
	
	int i;
	listStore* curList;
	int isFound = 0;
	
	if (strlen(listName) == 0) {
		
		fprintf(stdout, "No Name for list \n");
		return;
	}
	
	for (i = 0 ; i < MAX_NUM; i++) {
		
		if (listStorage[i] && strcmp(listStorage[i]->name, listName) == 0) {
			
			isFound = 1;
			curList = listStorage[i];
			break;
		}
	}
	
	if (!isFound) {
		fprintf(stdout, "%s Not Found \n", listName);
		return;
	}
	
	int pos = atoi(param1);
	int num = atoi(param2);
	
	if (strcmp(option, "list_insert") == 0) {
		
		int nodeCnt = list_size(curList->list);
		
		if (pos > nodeCnt) {
			fprintf(stdout, "invalid range \n");
			return;
		}
		
		struct list_item* newNode = (struct list_item*)malloc(sizeof(struct list_item));
		newNode->data = num;
		
		if (pos == 0) {
			
			list_push_front(curList->list, &(newNode->elem));
			return;
		}
		else if (pos == nodeCnt) {
			
			list_push_back(curList->list, &(newNode->elem));
			return;
		}
		
		struct list_elem* targetElem = list_begin(curList->list);
		
		for (i = 0; i < pos; i++)
			targetElem = list_next(targetElem);
		
		list_insert(targetElem, &(newNode->elem));
		return;
		
	}
	
	if (strcmp(option, "list_swap") == 0) {
		
		int pos1 = pos;
		int pos2 = num;
		num = list_size(curList->list);
		
		if (pos1 == pos2) return;
		if (pos1 >= num || pos2 >= num || pos1 < 0 || pos2 < 0) return; 
		
		if (pos1 > pos2) {
			
			int temp = pos1;
			pos1 = pos2;
			pos2 = temp;
		}
		
		struct list_elem* elem = list_begin(curList->list);
		
		struct list_elem* node1, *node2;
		
		for (i = 0; i < num; i++) {
			
			if (i == pos1) node1 = elem;
			if (i == pos2) node2 = elem;
			
			elem = list_next(elem);
		}
		
		list_swap(node1, node2);
	}
	
}

void listHandlerSixArgs(char* option, char* listName1, char* num1, char* listName2, char* num2, char* num3) {
	
	int i, flag = 0;
	listStore* destList, *srcList;
	
	if (strcmp(option, "list_splice") != 0) {
		fprintf(stdout, "Invalid command \n");
		return;
	}
	
	if (strlen(listName1) == 0 || strlen(listName2) == 0) {
		
		fprintf(stdout, "No Name for list \n");
		return;
	}
	
	for (i = 0 ; i < MAX_NUM; i++) {
		
		if (listStorage[i] && strcmp(listStorage[i]->name, listName1) == 0) {
			destList = listStorage[i];
			flag++;
		}
		if (listStorage[i] && strcmp(listStorage[i]->name, listName2) == 0) {
			srcList = listStorage[i];
			flag++;
		}
	}
	
	if (flag != 2) {
		fprintf(stdout, "List configuration fail \n");
		return;
	}
	
	int destPos = atoi(num1);
	int srcPos1 = atoi(num2);
	int srcPos2 = atoi(num3);
	
	struct list_elem* destElem = list_begin(destList->list);
	struct list_elem* srcStart = list_begin(srcList->list);
	struct list_elem* srcEnd = srcStart;
	
	for (i = 0; i < destPos; i++)
		destElem = list_next(destElem);
	for (i = 0; i < srcPos1; i++)
		srcStart = list_next(srcStart);
	for (i = 0; i < srcPos2; i++)
		srcEnd = list_next(srcEnd);
	
	list_splice(destElem, srcStart, srcEnd);
	
	return;
}
