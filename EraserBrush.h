#pragma once
//
// PointBrush.h
//
// The header file for Point Brush. 
//

#ifndef ERASERBRUSH_H
#define ERASERBRUSH_H

#include "ImpBrush.h"

class EraserBrush : public ImpBrush
{
public:
	EraserBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif