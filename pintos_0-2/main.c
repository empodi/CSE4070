#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "list.h"
#include "hash.h"
#include "bitmap.h"
#include "list_helper.h"
#include "bitmap_helper.h"
#include "hash_helper.h"
#include "structure_helper.h"


int main() {
	
	char input[CMD_LEN];
	char argArr[8][30] = {'\0',};
	int argCnt;
	
	listNum = 0;
	bitmapNum = 0;
	hashNum = 0;


	while (1) {
		
		argCnt = 0;
		
		fgets(input, CMD_LEN, stdin);
		
		if (input[0] == '\n') {
			continue;
		}
		
		if (input[0] == 'n') {
			
			fprintf(stdout, "list num: %d \n", listNum);
			fprintf(stdout, "bitmap num: %d \n", bitmapNum);
			fprintf(stdout, "hash num: %d \n", hashNum);
		}
		
		char* ptr = strtok(input, " ");
		
		while (ptr != NULL) {
			
			strcpy(argArr[argCnt++], ptr);
			ptr = strtok(NULL, " ");
		}
		
		char tempCMD[50] = {'\0', };
		strcpy(tempCMD, argArr[0]);
		
		argArr[argCnt - 1][strlen(argArr[argCnt - 1]) - 1] = '\0';
		
		if (strcmp(argArr[0], "create") == 0) {

			createHandler(argArr[1], argArr[2], argArr[3]);
		}
		else if (strcmp(argArr[0], "dumpdata") == 0) {

			dumpdataHandler(argArr[1]);
		}
		else if (strcmp(argArr[0], "delete") == 0) {
			
			deleteHandler(argArr[1]);
		}
		else if (strcmp(argArr[0], "quit") == 0) {
			
			if (quitHandler())
				break;
			else
				fprintf(stdout, "Error while freeing memory \n");
		}
		
		char* ds = strtok(argArr[0], "_");
		
		if (strcmp(ds, "list") == 0) {
			
			switch(argCnt) {
				
				case 2: 
					listHandlerTwoArgs(tempCMD, argArr[1]);
					break;
				case 3:
					listHandlerThreeArgs(tempCMD, argArr[1], argArr[2]);
					break;
				case 4:
					listHandlerFourArgs(tempCMD, argArr[1], argArr[2], argArr[3]);
					break;
				case 6:
					listHandlerSixArgs(tempCMD, argArr[1], argArr[2], argArr[3], argArr[4], argArr[5]);
					break;
				default:
					continue;
				
			}
			
		}
		else if (strcmp(ds, "bitmap") == 0) {
			
			//fprintf(stdout, "argCnt:%d %s %s %s %s\n",argCnt, tempCMD, argArr[1], argArr[2], argArr[3], argArr[4]);

			switch(argCnt) {
				
				case 2: 
					bitmapHandlerTwoArgs(tempCMD, argArr[1]);
					break;
				case 3:
					bitmapHandlerThreeArgs(tempCMD, argArr[1], argArr[2]);
					break;
				case 4:
					bitmapHandlerFourArgs(tempCMD, argArr[1], argArr[2], argArr[3]);
					break;
				case 5:
					bitmapHandlerFiveArgs(tempCMD, argArr[1], argArr[2], argArr[3], argArr[4]);
					break;
				default:
					continue;
				
			}
		}
		else if (strcmp(ds, "hash") == 0) {
			
			switch(argCnt) {
				
				case 2: 
					hashHandlerTwoArgs(tempCMD, argArr[1]);
					break;
				case 3:
					hashHandlerThreeArgs(tempCMD, argArr[1], argArr[2]);
					break;
				default:
					continue;
				
			}
		}
		
	}
	

	return 0;
}
