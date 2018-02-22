#pragma once

//this is the header file of Sharpening brush
#ifndef SHARPENINGBRUSH_H
#define SHARPENINGBRUSH_H

#include "ImpBrush.h"

class SharpeningBrush : public ImpBrush
{
public:
	SharpeningBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
	//when dealing with blur brush use this set color
	void SetSharpeningColor(const Point source);
};

#endif