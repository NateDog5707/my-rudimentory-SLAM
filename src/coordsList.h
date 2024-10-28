/* coordsList.h
		
		linked list stuff :) for coordinates to add to a dynamic array
		
	
*/

#ifndef COORDSLIST_H
#define COORDSLIST_H

#include "setup.h"

typedef struct CoordsEntry CENTRY;
typedef struct CoordsList CLIST;

struct CoordsEntry{
	CLIST *List;
	CENTRY *Next;
	CENTRY *Prev;
	float valX;
	float valY;
	
};
 
struct CoordsList{
	unsigned int Length;
	CENTRY *First;
	CENTRY *Last;
};


//start of COORDS functions
CENTRY *CreateCoordsEntry(float x, float y);

void DeleteCoordsEntry(CENTRY *coords);

float GetCoordsValX(const CENTRY *coords);

float GetCoordsValY(const CENTRY *coords);

//start of CLIST functions
CLIST *CreateCoordsList(void);

void DeleteCoordsList(CLIST *list);

void AppendCoords(CLIST *list, float x, float y);


// compiles two lists together by grouping closed magnitude points together
void SortTwoLists(CLIST *list, CLIST *list2, CLIST *compileList);

//algorithm that compares slopes together. if slopes are MASSIVELY different, there is a corner
void FindCorners(CLIST *list, CLIST *cornersList);

//prints out the coordinates for any list of coords
void PrintAllCoords(CLIST *list);

//filters out two of the same coords if they are really close to each other
void FilterSameCoords(CLIST *list);

//void FilterForCornerCoords(CLIST *list);

#endif