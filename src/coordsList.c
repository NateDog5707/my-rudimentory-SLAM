/* coordsList.c
  
  place to implement the coords list stuff


*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "coordsList.h"


//create new cords
CENTRY *CreateCoordsEntry(float x, float y){
	
	CENTRY *coords = (CENTRY *)malloc(sizeof(CENTRY));
	if (coords == NULL){
		return NULL;
	}
	
	coords->valX = x;
	coords->valY = y;
	
	coords->List = NULL;
	coords->Next = NULL;
	coords->Prev = NULL; 
	
	
	return coords;
}


float GetCoordsValX (const CENTRY *coords){
	assert(coords);
	return coords->valX;
	
}
float GetCoordsValY (const CENTRY *coords){
	assert(coords);
	return coords->valY;
	
}

///CLIST STUFF
CLIST *CreateCoordsList(void){

	CLIST *list;
	list = (CLIST *)malloc(sizeof(CLIST));
	if (list == NULL){
		 return NULL;
		 }
 	 list->Length = 0;
	 list->First = NULL;
   list->Last = NULL;
   return list;

}
void DeleteCoordsEntry(CENTRY *coords){
  
  assert(coords);
  assert(coords->List);
  
  if (coords->List->Length <= 1){
    DeleteCoordsList(coords->List);
    return;
  }
  else if (coords->List->First == coords){
    coords->List->First = coords->Next;
    coords->Next->Prev = NULL;
  }
  else if (coords->List->Last == coords){
    coords->List->Last = coords->Prev;
    coords->Prev->Next = NULL;
  }
  else{
    coords->Prev->Next = coords->Next;
    coords->Next->Prev = coords->Prev;
  }
  
  coords->List->Length--;
  coords->Next = NULL;
  coords->Prev = NULL;
  coords->List = NULL;
  
  
  
  free(coords);
  
}

void DeleteCoordsList(CLIST *list)
{
	int count = 0;
	/* to be implemented */
	assert(list);
	
	CENTRY *current = list->First;
	CENTRY *next = NULL;

	while (count < list->Length){
		//for moving to next entry
		next = current->Next;
		
		current->Prev = NULL;
		current->Next = NULL;
		current->List = NULL;
		
		
		free(current);
		current = next;
		count++;

		
	}
		
		list->First = NULL;
		list->Last = NULL;
		
		free(list);
	
		list = NULL;
}

void AppendCoords(CLIST *list, float x, float y){

	CENTRY* coords = CreateCoordsEntry(x, y);
	
	assert(list);
	assert(coords);
	
	coords->List = list;
	coords->Next = NULL;
	
	if(list->Last!= NULL){
		list->Last->Next = coords;
		coords->Prev = list->Last;
		list->Last = coords;
	}
	else{
		list->First = coords;
		list->Last = coords;
		coords->Prev = NULL;
		
	}
	list->Length++;
	
}


void SortTwoLists(CLIST *list, CLIST *list2, CLIST *compileList){
  //TODO
  //idea, get both lists. compare beginning items. find out where y-values meet. once we have the right area, start interweaving the two. 
  CENTRY *currOne, *currTwo, *currCompile;
  float magOne, magTwo;
  
  currOne = list->First;
  currTwo = list2->First;
  
  if (currOne->valY > currTwo->valY){
    //go down the list of list2 to find where to start plugging in items
    do{
      AppendCoords(compileList, currTwo->valX, currTwo->valY);
      currTwo = currTwo->Next;
    } while(currOne->valY > currTwo->valY);
      //after loop, the two points will be next to each other
  }
  
  else{
  //go down the list of list2 to find where to start plugging in items
    do{
      AppendCoords(compileList, currOne->valX, currOne->valY);
      currOne = currOne->Next;
    } while(currTwo->valY > currOne->valY);
      //after loop, the two points will be next to each other
  }
  
  //add to list back and forth
  //find the magnitude difference. append the closer ones.
  
  
  while((currOne != list->Last) || (currTwo != list2->Last)){
    
    currCompile = compileList->Last;
  
    if (currOne == list->Last){
      AppendCoords(compileList, currTwo->valX, currTwo->valY);
      currTwo = currTwo->Next;
      continue;
    }
    else if (currTwo == list2->Last){
      AppendCoords(compileList, currOne->valX, currOne->valY);
      currOne = currOne->Next;
      continue;
    }
    
  
    magOne = sqrt(pow(currCompile->valX - currOne->valX, 2) + pow(currCompile->valY - currOne->valY, 2));
    magTwo = sqrt(pow(currCompile->valX - currTwo->valX, 2) + pow(currCompile->valY - currTwo->valY, 2));
    
    if (magOne < magTwo){
      AppendCoords(compileList, currOne->valX, currOne->valY);
      currOne = currOne->Next;

    }
    else{
      AppendCoords(compileList, currTwo->valX, currTwo->valY);
      currTwo = currTwo->Next;

    }
    
  }
}




void FindCorners(CLIST *list, CLIST *cornersList){
  //TODO
	if (list->First == NULL){
		return;
	}
	
  CENTRY* curr = list->First;
  CENTRY* next = list->First->Next;
  float slopeOne, slopeTwo;
  float percDiff, diff;
  while (next->Next != NULL){
		//printf("Coords: (%.3f, %.3f)\n", next->valX, next->valY);
		
		
    //if sides are completely vertical / share the same x point
    if ((curr->valX == next->valX)){ 
      slopeOne = 100000;
      if ((next->valX == next->Next->valX)){
        curr = next;
        next = next->Next;
    		//printf("continueing A\n");
        continue;
      }
      else{
        //slopeTwo = (next->Next->valY - next->valY) / (next->Next->valX - next->valX); 
      	slopeTwo = 1;
      	//printf("submitting A\n");
			}
    }
    //if first slope is completely horizontal
    else if ((curr->valY == next->valY)){
    	slopeOne = 0;
    	if ((next->valY == next->Next->valY)){
    		//not a corner, continues in straight line
    		curr = next;
    		next = next->Next;
    		//printf("continueing B\n");
    		continue;
    	}
    	else{
    		//goes from straight horizontal to a change in y. it should be a corner
    		slopeTwo = 100000;
  			//printf("submitting B\n");
    	}
   	
    }
    //if side isn't completely horizontal or vertical
    else {
      //compare slope from 1 to 2 with 2 to 3
      if ((next->valX == next->Next->valX)){
        // if slope suddenly shifts completely upwards, its a corner.
        slopeOne = 10000;
        slopeTwo = 1;
        //printf("submitting C\n");
      }
      /*else if ((next->valY == next->Next->valY)){
      	//if slope suddenly shifts completely horizonatal, thats a change
      	slopeOne = 10000;
      	slopeTwo = 1;
      	printf("C\n");
      }*/
      else{
      	//printf("E\n");
        //printf("curr->valY: %f, next->valY: %f, next->Next->valY: %f, curr->valX: %f, next->valX: %f, next->Next->valX: %f\n", curr->valY, next->valY, next->Next->valY, curr->valX, next->valX, next->Next->valX);
        slopeOne = (next->valY - curr->valY) / (next->valX - curr->valX);
        slopeTwo = (next->Next->valY - next->valY) / (next->Next->valX - next->valX);
        //printf("D\n");
			}
    }
    
    
    diff = slopeTwo-slopeOne;
    //calc the percent difference       formula: |A-B| / ((A+B)/2)
    percDiff = 100 * (abs(diff) / ((slopeOne+slopeTwo)/2));
    //printf("slopeOne = %f\nslopeTwo = %f\n", slopeOne, slopeTwo);
    //percDiff = abs(percDiff);
  	//printf("\tdiff: %f\n", diff);
  	//printf("\tpercDiff: %f\n", percDiff);
    if (abs(percDiff) > CORNER_DETECT_THRESHOLD){
    //  printf("=====\nadding a corner!\n=====\n");
      AppendCoords(cornersList, next->valX, next->valY);
    }
    /*
    else if ( (diff > CORNER_DETECT_THRESHOLD ) || diff < (-1 * CORNER_DETECT_THRESHOLD)){
    	printf("-----\nadding a corner through 2nd means\n-----\n");
    	AppendCoords(cornersList, next->valX, next->valY);
      curr = next;
      next = next->Next;
    }
    */

		if (next->Next != NULL){
   	 	curr = next;
    	next = next->Next;
		}
    
  }
  
}//EOF Find Corners




void PrintAllCoords(CLIST *list){
  CENTRY* curr = list->First;
  float x, y;
  int count = 1;
  
  
  do{
    x = GetCoordsValX(curr);
    y = GetCoordsValY(curr);
    printf("Entry %d: (%f, %f)\n", count, x, y);
    
    if (curr->Next != NULL){
      curr = curr->Next;
      count++;
    }
    else{
      break;
    }
  }while (curr != NULL);

}


void FilterSameCoords(CLIST *list){
	if (list->First == NULL){
		return; 
	}
	
  CENTRY * curr = list->First;
  CENTRY * next;
  float mag = 0;
  
  while (curr != list->Last){
  	//printf("hey\n");
    next = curr->Next;
    mag = sqrt(pow(curr->valX - next->valX, 2) + pow(curr->valY - next->valY, 2));
    
    if (mag < FILTER_CORNER_MAG){
      DeleteCoordsEntry(next);
      //printf("Filtered one\n");
    }
 	  if (curr->Next != NULL){
    	curr = curr->Next;
   	}
  
  }
  
}


/*
void FilterForCornerCoords(CLIST *list){
  CENTRY * curr = list->First;
  float magA, magB, magC, magD;
  
  //break statement is if the curr pointer has reached the last one.
  while (1){
    
    magA = sqrt(pow(curr->valX - CORNER_AX, 2) + pow(curr->valY - CORNER_AY, 2));
    magB = sqrt(pow(curr->valX - CORNER_BX, 2) + pow(curr->valY - CORNER_BY, 2));
    magC = sqrt(pow(curr->valX - CORNER_CX, 2) + pow(curr->valY - CORNER_CY, 2));
    magD = sqrt(pow(curr->valX - CORNER_DX, 2) + pow(curr->valY - CORNER_DY, 2));
    
    if (magA < FILTER_CORNER_MAG){
      DeleteCoordsEntry(curr);
      printf("Filtered one for being too far\n");
    }
    else if (magB < FILTER_CORNER_MAG){
      DeleteCoordsEntry(curr);
      printf("Filtered one for being too far\n");
    }
    else if (magC < FILTER_CORNER_MAG){
      DeleteCoordsEntry(curr);
      printf("Filtered one for being too far\n");
    }
    else if (magD < FILTER_CORNER_MAG){
      DeleteCoordsEntry(curr);
      printf("Filtered one for being too far\n");
    }
    
    if (curr == list->Last){
      break;
    
    curr = curr->Next;
    
    }
    
    
  }

}
*/