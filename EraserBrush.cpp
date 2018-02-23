//
// EraserBrush.cpp
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "EraserBrush.h"

extern float frand();

EraserBrush::EraserBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void EraserBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();



	glPointSize((float)size);

	BrushMove(source, target);
}

void EraserBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_POINTS);

	glColor3ub(0, 0, 0);

	glVertex2d(target.x, target.y);

	glEnd();
}

void EraserBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

