#ifndef SETUP_H
#define SETUP_H

#define PI 3.14159
#define CORNER_DETECT_THRESHOLD 0.05
#define DIFF_COMPARE_THRESHOLD 0.0005
#define SCAN_INTERVAL_DEG 1
#define FILTER_CORNER_MAG 1

#define NUM_CORNERS 4

#define	CORNER_AX	-10.0
#define	CORNER_AY	-10.0

#define	CORNER_BX	10.0
#define	CORNER_BY	-10.0

#define	CORNER_CX	10.0
#define	CORNER_CY	10.0
	
#define	CORNER_DX	-14.0
#define	CORNER_DY	2.0

//gets the slopes and y-ints of the sides, so we can use it later in linear equations
void getBoundSlopes(float *slopeAB, float *slopeBC, float *slopeCD, float *slopeDA, 
											float *yIntAB, float *yIntBC, float *yIntCD, float *yIntDA,
											   int *vertAB, int *vertBC, int *vertCD, int *vertDA);
								   
//place the robot inside the boundaries - temporarily as centered as possibe - should make it more random later
void placeRobot(float *midX, float *midY);

//get the slopes from robot location to corners, we will use to determine which side to solve linear equation from
void getToCornerSlopes(const float midX, const float midY, float *angToA, float *angToB, float *angToC, float *angToD);

//print out initialized corners, located above
void printGivenCorners();

#endif