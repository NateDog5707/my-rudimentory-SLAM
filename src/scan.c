 /*	scan.c
		
		need to somehow do this
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <time.h>


#include "scan.h"

void scanAround(float angle, CLIST *list, float midX, float midY, float angToA, float angToB, float angToC, float angToD,
									float slopeAB, float slopeBC, float slopeCD, float slopeDA, float yIntAB, float yIntBC, float yIntCD, float yIntDA,
								 		int vertAB, int vertBC, int vertCD, int vertDA){
										 	
	int side = 0; // 0, 1, 2, 3 = side AB, BC, CD, DA
	int vertCurr = 0;
	//tan() trig function gives slope, cuz rise/run
  
  angle = round(angle * 10000) / 10000;  //fixing floating point rounding error
	float angleInDeg = angle;
	angle = (angle * PI / 180.0);
  angle = round(angle * 10000) / 10000; //FPRE
  
	float currSlope;
	
	currSlope = tan(angle);
  currSlope = round(currSlope *10000) / 10000; //FPRE
/*  
	printf("angle = %g\n", angleInDeg);
	printf("rad = %f\n", angle);
	printf("currSlope = %f\n", currSlope);
*/	
	
 //find which side im working with the currAngle

	if (angleInDeg >= angToB || angleInDeg < angToC){
		side = 1;
	}
	else if (angleInDeg >= angToC && angleInDeg < angToD){
		side = 2;
	}
	else if (angleInDeg >= angToD && angleInDeg < angToA){
		side = 3;
	}
	//else, side = 0
	
 
	//check for vert lines in currSlope
	if (angleInDeg == 270 || angleInDeg == 90){
		vertCurr = 1;
	}
	
	
	//calcumalations
	//need to solve the intercepting points between scan ray and side of shape.
	if (side == 0){ //side AB
		scanOnce(list, currSlope, midX, midY, vertCurr, slopeAB, yIntAB, vertAB, side);
		//printf("===\nScanned Side AB\n===\n");
	}
	else if (side == 1){ //side BC
		scanOnce(list, currSlope, midX, midY, vertCurr, slopeBC, yIntBC, vertBC, side);
		//printf("===\nScanned Side BC\n===\n");
	}
	else if (side == 2){ //side CD
		scanOnce(list, currSlope, midX, midY, vertCurr, slopeCD, yIntCD, vertCD, side);
		//printf("===\nScanned Side CD\n===\n");
	} 
	else if (side == 3){ //side DA
		scanOnce(list, currSlope, midX, midY, vertCurr, slopeDA, yIntDA, vertDA, side);
		//printf("===\nScanned Side DA\n===\n");
	}
	
	
}// EOF scanAround


void scanOnce(CLIST *list, float currSlope, float midX, float midY, int currVert, float sideSlope, float sideYInt, int sideVert, int side){
	//float currSlope, midX, midY; y = mx+b 
	//y = mx + b, y = mx+b
	float x, y; 
	float currYInt = midY - (currSlope * midX);
	
	//printf("scanOnce:\n\tcurrVert = %d\n\tsideVert = %d\n", currVert, sideVert);
	if (currVert == 0 && sideVert == 0){
		x = (sideYInt - currYInt) / ( currSlope - sideSlope);
		y = (currSlope * x) + currYInt;
	}
	
	else {
		//either currVert or sideVert = 1
		if (currVert == 1){
      //printf("Current slope is a vertical line===\n");
			//scanning slope is a vertical line
			x = midX;
			y = sideYInt + (sideSlope * midX);
		}
		else { // side slope is vertical line
      //printf("Side slope is a vertical line---\n");
			switch (side){
			case 0:
				x = CORNER_AX;
				break;
			case 1:
				x = CORNER_BX;
				break;
			case 2:
				x = CORNER_CX;
				break;
			case 3:
				x = CORNER_DX;
				break;
			default:
				x = -131; //if it ever reaches this,something has gone wrong
			}// switch end
			
			y = (currSlope * x) + currYInt;
		}
	}
	//printf("Interception at (%.4f, %.4f)\n", x, y);
 
  //LATEST ADD - rounding the appended coords
  x = round(x * 10000) / 10000;
  y = round(y * 10000) / 10000;
	AppendCoords(list, x, y);
}

void moveRobot(float *midX, float *midY){
  time_t t;

  srand((unsigned) time(&t));
  float distX, distY;
  float angle = rand() % 360;
  float radius;
  angle = angle / PI * 180;
  
  //this function returns the two middle most corner values for X coords and Y coords. this will help to limit the moveRobot as to not extend past the border somewhat.
	placeRobot(&distX, &distY);
  
  if (distX > distY){
    radius = rand() % (int)( round(distY));
    if (radius == 0){
      radius = distY/5;
    }
    *midX = *midX + (radius * cos(angle));
    *midY = *midY + (radius * sin(angle));
  }
  
  else{
    radius = rand() % (int)( round(distX));
    if (radius == 0){
      radius = distX/5;
    }
    *midX = *midX + (radius * cos(angle));
    *midY = *midY + (radius * sin(angle));
  }
  


}
