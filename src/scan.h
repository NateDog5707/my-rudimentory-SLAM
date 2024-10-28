/*	scan.h
		the* scan function
*/

#ifndef SCAN_H
#define SCAN_H

#include "coordsList.h"
#include "setup.h"

//from robot position, gather points of the boundaries in a full 360 rotation
void scanAround(float angle, CLIST *list, float midX, float midY, float angToA, float angToB, float angToC, float angToD,
									float slopeAB, float slopeBC, float slopeCD, float slopeDA, float yIntAB, float yIntBC, float yIntCD, float yIntDA,
								 		int vertAB, int vertBC, int vertCD, int vertDA);

//from robot position, scan in one direction for a wall/boundary and store the location
void scanOnce(CLIST *list, float currSlope, float midX, float midY, int currVert, float sideSlope, float sideYInt, int sideVert, int side);

//move robot's position a short distance in a random direction
void moveRobot(float *midX, float *midY);

#endif