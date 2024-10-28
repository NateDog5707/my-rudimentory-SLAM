/*	main.c
	
	
	
*/

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>

#include "setup.h"
#include "coordsList.h"
#include "scan.h"
int main(void){

//variable declarations
	float slopeAB = 0, slopeBC = 0, slopeCD = 0, slopeDA = 0;
	float yIntAB = 0, yIntBC = 0, yIntCD = 0, yIntDA = 0;
	int vertAB = 0, vertBC, vertCD, vertDA;

	float midX, midY;
	
//	float slopeToA =0, slopeToB =0, slopeToC =0, slopeToD =0;
//	int vertToA =0, vertToB =0, vertToC =0, vertToD =0;
	float angToA =0, angToB =0, angToC =0, angToD = 0;
	
	
	float angleIter = 0;
	
	CLIST *coordsList = CreateCoordsList();
  CLIST *cornersList = CreateCoordsList();
  CLIST *coordsList2= CreateCoordsList();
  CLIST *compileList = CreateCoordsList();
	
//main function start

	//setup functions based on consts inside setup.h
	getBoundSlopes(&slopeAB, &slopeBC, &slopeCD, &slopeDA, &yIntAB, &yIntBC, 
										&yIntCD, &yIntDA, &vertAB, &vertBC, &vertCD, &vertDA);
	
	placeRobot(&midX, &midY);
	
	//slope2corner
	getToCornerSlopes(midX, midY, &angToA, &angToB, &angToC, &angToD);
	
	//debug for setup section
	/*
	printf("The corners are - A: %.1f,%.1f, B: %.1f,%.1f, C: %.1f,%.1f D: %.1f,%.1f\n", CORNER_AX, CORNER_AY, CORNER_BX, CORNER_BY, CORNER_CX, CORNER_CY, CORNER_DX, CORNER_DY);
	printf("The side's slopes are - AB: %.2f, BC: %.2f, CD: %.2f, DA: %.2f\n", slopeAB, slopeBC, slopeCD, slopeDA);
	printf("The side's yInts are  - AB: %.2f, BC: %.2f, CD: %.2f, DA: %.2f\n", yIntAB, yIntBC, yIntCD, yIntDA);
	*/
//	printf("The 2Corner slopes are - A: %.2f, B: %.2f, C: %.2f, D: %.2f\n", slopeToA, slopeToB, slopeToC, slopeToD);
	
	
	//scanning around
	for (angleIter = 0; angleIter < 360; angleIter+=SCAN_INTERVAL_DEG){
	
		scanAround(angleIter, coordsList, midX, midY, angToA, angToB, angToC, angToD,
							slopeAB, slopeBC, slopeCD, slopeDA, yIntAB, yIntBC, yIntCD, yIntDA, vertAB, vertBC, vertCD, vertDA);
	}
 
 	//debug
	//PrintAllCoords(coordsList);

   moveRobot(&midX, &midY);
   //debug
	 //printf("NEW: midX: %f, midY: %f\n", midX, midY);
   
	 getToCornerSlopes(midX, midY, &angToA, &angToB, &angToC, &angToD);
   //debug for setup section
   /*
		printf("The corners are - A: %.1f,%.1f, B: %.1f,%.1f, C: %.1f,%.1f D: %.1f,%.1f\n", CORNER_AX, CORNER_AY, CORNER_BX, CORNER_BY, CORNER_CX, CORNER_CY, CORNER_DX, CORNER_DY);
		printf("The side's slopes are - AB: %.2f, BC: %.2f, CD: %.2f, DA: %.2f\n", slopeAB, slopeBC, slopeCD, slopeDA);
		printf("The side's yInts are  - AB: %.2f, BC: %.2f, CD: %.2f, DA: %.2f\n", yIntAB, yIntBC, yIntCD, yIntDA);
   */
   
   //scanning around A SECOND TIME
	for (angleIter = 0; angleIter < 360; angleIter+=SCAN_INTERVAL_DEG){
	
		scanAround(angleIter, coordsList2, midX, midY, angToA, angToB, angToC, angToD,
							slopeAB, slopeBC, slopeCD, slopeDA, yIntAB, yIntBC, yIntCD, yIntDA, vertAB, vertBC, vertCD, vertDA);
	}
 
 	//append two lists together
 	SortTwoLists(coordsList, coordsList2, compileList);
  
  
  
	//corners vvv
  FindCorners(compileList, cornersList);
    
  FilterSameCoords(cornersList);
  
 	//print out first corners
 	printGivenCorners();
  
  
  //print out solved corners
  {  
    printf("List of corners:\n");
    if (cornersList->First != NULL){
      printf("List Length: %d\n", cornersList->Length);
      PrintAllCoords(cornersList);
    }
  	
  }
  
  //cleanup
  if (cornersList!= NULL){
  	DeleteCoordsList(cornersList);
 	}
  if (coordsList != NULL){
	  DeleteCoordsList(coordsList);
  }
  if (coordsList2 != NULL){
    DeleteCoordsList(coordsList2);
  }
  DeleteCoordsList(compileList);
}