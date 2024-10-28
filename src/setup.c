/*	setup.c
		
		goal: to get the linear slopes between all "X" corners of the boundaries
																								4 sides temp.
*/
#include <math.h>
#include <stdio.h> //for debug
#include "setup.h"

/*returns slopes and yInts for each of 4 sides for solving things linearly
	if undefined slope (vertical line as a side), returns a flag
	CALLING FUNCTION: needs to handle vertical side as a case.
*/
void getBoundSlopes(float *slopeAB, float *slopeBC, float *slopeCD, float *slopeDA, 
											float *yIntAB, float *yIntBC, float *yIntCD, float *yIntDA,
											   int *vertAB, int *vertBC, int *vertCD, int *vertDA){
	//CORNER_AX, CORNER_AY is a point
	
	if ( (CORNER_BX - CORNER_AX) != 0 ){
		*slopeAB = ((CORNER_BY - CORNER_AY) / (CORNER_BX - CORNER_AX));
		*yIntAB = CORNER_AY - (*slopeAB * (CORNER_AX - 0));
		*vertAB = 0;
	}
	else {//divide by 0 error
		*vertAB = 1;
	}
	if ( (CORNER_CX - CORNER_BX) != 0 ){
		*slopeBC = (CORNER_CY - CORNER_BY) / (CORNER_CX - CORNER_BX);
		*yIntBC = CORNER_BY - (*slopeBC * (CORNER_BX - 0));
		*vertBC = 0;
	}
	else {//divide by 0 error
		*vertBC = 1;
	}
	if ( (CORNER_DX - CORNER_CX) != 0 ){
		*slopeCD = (CORNER_DY - CORNER_CY) / (CORNER_DX - CORNER_CX);
		*yIntCD = CORNER_CY - (*slopeCD * (CORNER_CX - 0));
		*vertCD = 0;
	}
	else {//divide by 0 error
		*vertCD = 1;
	}
	if ( (CORNER_AX - CORNER_DX) != 0 ){
		*slopeDA = (CORNER_AY - CORNER_DY) / (CORNER_AX - CORNER_DX);
		*yIntDA = CORNER_DY - (*slopeDA * (CORNER_DX - 0));
		*vertDA = 0;
	}
	else {//divide by 0 error
		*vertDA = 1;
	}
	
	
} //EOF




//a simple place robot function. finds the midpoint in x and y values and yeah. 
void placeRobot(float *midX, float *midY){
	//need to sort all corners' X and Y, find the mid of the two inner points
	float temp;
	float cornersX[NUM_CORNERS] = {CORNER_AX, CORNER_BX, CORNER_CX, CORNER_DX};
	float cornersY[NUM_CORNERS] = {CORNER_AY, CORNER_BY, CORNER_CY, CORNER_DY};
	
	
	
		for (int i = 0; i < NUM_CORNERS-1; i++){
			for (int j = i; j < NUM_CORNERS-1; j++){
				if (cornersX[j] > cornersX[j+1]){
					temp = cornersX[j];
					cornersX[j] = cornersX[j+1];
					cornersX[j+1] = temp;
				}
			
				if (cornersY[j] > cornersY[j+1]){
					temp = cornersY[j];
					cornersY[j] = cornersY[j+1];
					cornersY[j+1] = temp;
				}
		
			}
		}

	//assume both arrays are sorted now
	
	*midX = (cornersX[1] + cornersX[2]) / 2.0;
	*midY = (cornersY[1] + cornersY[2]) / 2.0;
 
  *midX = round(*midX * 1000) / 1000;
  *midY = round(*midY * 1000) / 1000;
 
  //printf("MidX, MidY = %f, %f\n", *midX, *midY);

} //EOF


void getToCornerSlopes(const float midX, const float midY, float *angToA, float *angToB, float *angToC, float *angToD){

	float slopeToA, slopeToB, slopeToC, slopeToD;
	int vertToA, vertToB, vertToC, vertToD;
	
	if ( (CORNER_AX - midX) != 0 ){
		slopeToA = ((CORNER_AY - midY) / (CORNER_AX - midX));
		vertToA = 0;
	}
	else {//divide by 0 error
		vertToA = 1;
	}
	if ( (CORNER_BX - midX) != 0 ){
		slopeToB = ((CORNER_BY - midY) / (CORNER_BX - midX));
		vertToB = 0;
	}
	else {//divide by 0 error
		vertToB = 1;
	}
	if ( (CORNER_CX - midX) != 0 ){
		slopeToC = ((CORNER_CY - midY) / (CORNER_CX - midX));
		vertToC = 0;
	}
	else {//divide by 0 error
		vertToC = 1;
	}
	if ( (CORNER_DX - midX) != 0 ){
		slopeToD = ((CORNER_DY - midY) / (CORNER_DX - midX));
		vertToD = 0;
	}
	else {//divide by 0 error
		vertToD = 1;
	}
	
	if(vertToA == 0){
		*angToA = atan(slopeToA) * 180 / PI;
		*angToA += 180;
	}
	if(vertToB == 0){
		*angToB = atan(slopeToB) * 180 / PI;
		*angToB += 360;
	}
	if(vertToC == 0){
		*angToC = atan(slopeToC) * 180 / PI;
	}
	if(vertToD == 0){
		*angToD = atan(slopeToD) * 180 / PI;
		*angToD += 180;
	}
	
	*angToA = round( *angToA * 1000) / 1000;
  *angToB = round( *angToB * 1000) / 1000;
  *angToC = round( *angToC * 1000) / 1000;
  *angToD = round( *angToD * 1000) / 1000;

	//printf("angToA = %f\nangToB = %f\nangToC = %f\nangToD = %f\n", *angToA, *angToB, *angToC, *angToD);

	
}


void printGivenCorners(){
	printf("Given corners:\n");
	printf("Corner A, X: %.1lf, Y: %.1lf\n", CORNER_AX, CORNER_AY);
	printf("Corner B, X: %.1lf, Y: %.1lf\n", CORNER_BX, CORNER_BY);
	printf("Corner C, X: %.1lf, Y: %.1lf\n", CORNER_CX, CORNER_CY);
	printf("Corner D, X: %.1lf, Y: %.1lf\n", CORNER_DX, CORNER_DY);

}
