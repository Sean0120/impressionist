
//the cpp file for warpbrush
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "WarpBrush.h"
#include <math.h>

extern float frand();

WarpBrush::WarpBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void WarpBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	effectiveR = pDoc->getSize();
	//after mouse down, we need to record the current point for further reference, without this the first drag function will be wrong
	lastPoint = target;
	BrushMove(source, target);
}

void WarpBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("WarpBrush::BrushMove  document is NULL\n");
		return;
	}
	//first we need to get the displacement, if it is zero, we are done 
	int distance_x = target.x - lastPoint.x;
	int distance_y = target.y - lastPoint.y;
	if (distance_x == 0 && distance_y == 0) return;
	// the function just set the color of some part, do not need to use gl draw, but we need to buffer to store the position and its correponding color 
	GLubyte * ColorBuffer = new GLubyte[effectiveR * effectiveR * 4 * 3];//the circle is not easy to store, we store a square and then check whether it is in the circle
	//the start point of the square
	Point start(target.x - effectiveR, target.y - effectiveR);
	//calculate each element in the buffer 
	for (int i = 0; i < effectiveR * 2; i++) {
		for (int j = 0; j < effectiveR * 2; j++) {
			Point new_start(start.x + j, start.y + i);
			memcpy(ColorBuffer + 3 * (j + i * 2 * effectiveR), pDoc->GetOriginalPixelBlack(GetSourcePoint(target, new_start, distance_x, distance_y, effectiveR)), 3);
		}
	}
	//set the color to the bitmap
	for (int i = 0; i < effectiveR * 2; ++i)
		for (int j = 0; j < effectiveR * 2; ++j)
		{
			pDoc->SetPaintPixel(start.x + j, start.y + i , ColorBuffer + 3 * (i * 2 * effectiveR + j));
		}
	delete[] ColorBuffer;
	lastPoint = target;
	dlg->m_paintView->RestoreContent();

}

void WarpBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

//this is the function to calculate where should the target get its color 
Point WarpBrush::GetSourcePoint(const Point center, const Point target, int distance_x, int distance_y, int radius) {
	//check whether this point is in the circle
	double distanceC_P = sqrt((target.x - center.x)*(target.x - center.x) + (target.x - center.x)*(target.x - center.x));
	if (distanceC_P > radius) return target;// not in the circle, return the original point

	//calculate the distance the mouse moved
	double distance = sqrt(distance_x * distance_x + distance_y * distance_y);
	//this formular is from internet
	Point result = Point(target.x - (0.9  * (1 - pow(distanceC_P / radius, 2)) ) * distance_x, target.y - (0.9  * (1 - pow(distanceC_P / radius, 2))) * distance_y);
	return result;
}
