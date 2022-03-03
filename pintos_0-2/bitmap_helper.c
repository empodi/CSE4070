#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "bitmap.h"
#include "bitmap_helper.h"

void bitmapHandlerTwoArgs(char* option, char* bitmapName) {
	
	int i;
	bitmapStore* curBitmap;
	int isFound = 0;
		
	if (strlen(bitmapName) == 0) {
		
		fprintf(stdout, "No Name for bitmap \n");
		return;
	}
	
	for (i = 0 ; i < MAX_NUM; i++) {
		
		if (bitmapStorage[i] && strcmp(bitmapStorage[i]->name, bitmapName) == 0) {
			
			isFound = 1;
			curBitmap = bitmapStorage[i];
			break;
		}
	}
	if (!isFound) {
		fprintf(stdout, "Bitmap Not Found \n");
		return;
	}
		
	if (strcmp(option, "bitmap_size") == 0) {
		
		fprintf(stdout, "%zu \n", bitmap_size(curBitmap->bm));
		return;
	}
	else if (strcmp(option, "bitmap_dump") == 0) {
		
		bitmap_dump(curBitmap->bm);
		return;
	}
	
}


void bitmapHandlerThreeArgs(char* option, char* bitmapName, char* param) {
	
	int i;
	bitmapStore* curBitmap;
	int isFound = 0;
		
	if (strlen(bitmapName) == 0) {
		
		fprintf(stdout, "No Name for bitmap \n");
		return;
	}
	
	for (i = 0 ; i < MAX_NUM; i++) {
		
		if (bitmapStorage[i] && strcmp(bitmapStorage[i]->name, bitmapName) == 0) {
			
			isFound = 1;
			curBitmap = bitmapStorage[i];
			break;
		}
	}
	if (!isFound) {
		fprintf(stdout, "Bitmap Not Found \n");
		return;
	}
	
	int num = atoi(param);
	
	//fprintf(stdout, "%d\n", num);
	
	if (strcmp(option, "bitmap_set_all") == 0) {
		
		if (strcmp(param, "true") == 0) 
			bitmap_set_all(curBitmap->bm, true);
		else if (strcmp(param, "false") == 0)
			bitmap_set_all(curBitmap->bm, false);
		return;
	}
	else if (strcmp(option, "bitmap_mark") == 0) {
		
		bitmap_mark_handle(curBitmap->bm, num);
		return;
	}
	else if (strcmp(option, "bitmap_flip") == 0) {
		
		bitmap_flip(curBitmap->bm, num);
		return;
	}
	else if (strcmp(option, "bitmap_reset") == 0) {
		
		bitmap_reset(curBitmap->bm, num);
		return;
	}
	else if (strcmp(option, "bitmap_test") == 0) {
		
		fprintf(stdout, "%s \n", (bitmap_test(curBitmap->bm, num) ? "true" : "false"));
		return;
	}
	else if (strcmp(option, "bitmap_expand") == 0) {
		
		curBitmap->bm = bitmap_expand(curBitmap->bm, num);
	}
}


void bitmapHandlerFourArgs(char* option, char* bitmapName, char* param1, char* param2) {
	
	int i;
	bitmapStore* curBitmap;
	int isFound = 0;
	
	if (strlen(bitmapName) == 0) {
		
		fprintf(stdout, "No Name for bitmap \n");
		return;
	}
	
	for (i = 0 ; i < MAX_NUM; i++) {
		
		if (bitmapStorage[i] && strcmp(bitmapStorage[i]->name, bitmapName) == 0) {
			
			isFound = 1;
			curBitmap = bitmapStorage[i];
			break;
		}
	}
	if (!isFound) {
		fprintf(stdout, "Bitmap Not Found \n");
		return;
	}

	
	int pos = atoi(param1);
	int range = atoi(param2);
	
	if (strcmp(option, "bitmap_mark") == 0) {
		
		bitmap_mark_handle(curBitmap->bm, pos);
		return;
	}
	else if (strcmp(option, "bitmap_reset") == 0) {

		bitmap_reset(curBitmap->bm, pos);
		return;
	}
	
	if (strcmp(option, "bitmap_set") == 0) {
		
		if (strcmp(param2, "true") == 0)
			bitmap_set(curBitmap->bm, pos, true);
		else if (strcmp(param2, "false") == 0)
			bitmap_set(curBitmap->bm, pos, false);
		
		return;
	}
	else if (strcmp(option, "bitmap_all") == 0) {
		
		fprintf(stdout, "%s \n", (bitmap_all(curBitmap->bm, pos, range) ? "true" : "false"));
		return;
	}
	else if (strcmp(option, "bitmap_any") == 0) {
		
		fprintf(stdout, "%s \n", (bitmap_any(curBitmap->bm, pos, range) ? "true" : "false"));
		return;
	}
	else if (strcmp(option, "bitmap_none") == 0) {
		
		fprintf(stdout, "%s \n", (bitmap_none(curBitmap->bm, pos, range) ? "true" : "false"));
		return;
	}
}


void bitmapHandlerFiveArgs(char* option, char* bitmapName, char* param1, char* param2, char* param3) {
	
	int i;
	bitmapStore* curBitmap;
	int isFound = 0;
		
	if (strlen(bitmapName) == 0) {
		
		fprintf(stdout, "No Name for bitmap \n");
		return;
	}
	
	for (i = 0 ; i < MAX_NUM; i++) {
		
		if (bitmapStorage[i] && strcmp(bitmapStorage[i]->name, bitmapName) == 0) {
			
			isFound = 1;
			curBitmap = bitmapStorage[i];
			break;
		}
	}
	if (!isFound) {
		fprintf(stdout, "Bitmap Not Found \n");
		return;
	}
	
	
	int pos = atoi(param1);
	int range = atoi(param2);
	bool val = true;
	
	if (strcmp(param3, "false") == 0)
		val = false;
	
	if (strcmp(option, "bitmap_contains") == 0) {
		
		fprintf(stdout, "%s \n", (bitmap_contains(curBitmap->bm, pos, range, val) ? "true" : "false"));
		return;
	}
	else if (strcmp(option, "bitmap_set_multiple") == 0) {
		
		bitmap_set_multiple(curBitmap->bm, pos, range, val);
		return;
	}
	else if (strcmp(option, "bitmap_count") == 0) {
		
		fprintf(stdout, "%zu \n", bitmap_count(curBitmap->bm, pos, range, val));
		return;
	}
	else if (strcmp(option, "bitmap_scan") == 0) {
		
		fprintf(stdout, "%zu \n", bitmap_scan(curBitmap->bm, pos, range, val));
		return;
	}
	else if (strcmp(option, "bitmap_scan_and_flip") == 0) {
		
		fprintf(stdout, "%zu \n", bitmap_scan_and_flip(curBitmap->bm, pos, range, val));
		return;
	}
	
}
