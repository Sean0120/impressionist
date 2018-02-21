#pragma once
#ifndef WRAPBRUSH
#define WRAPBRUSH

#include"ImpBrush.h"

class WarpBrush : public ImpBrush {
public:
	WarpBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);
	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
private:
	int effectiveR; //the brush will just effect the part within the circle
	Point lastPoint;	

	Point GetSourcePoint(const Point center, const Point target, int distance_x, int distance_y, int radius);

};


#endif // !WRAPBRUSH
