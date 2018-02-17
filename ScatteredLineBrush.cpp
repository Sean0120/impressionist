//
//  ScatteredLineBrush.cpp
//  
//
//  Created by Apple on 2018/2/14.
//

#include "ScatteredLineBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include<cstdlib>
#include<ctime>
extern float frand();

ScatteredLineBrush::ScatteredLineBrush( ImpressionistDoc* pDoc, char* name) :
    ImpBrush(pDoc, name)
{
}

void ScatteredLineBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	BrushMove(source, target);
}
void ScatteredLineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int size = pDoc->getSize();


	if (pDoc == NULL) {
		printf("ScatteredLineBrush::BrushMove  document is NULL\n");
		return;
	}
	glLineWidth(1);
	srand((unsigned)time(NULL));
	for (int i = 0; i < 4; ++i) {
		int position_x = rand() % size - size / 2;
		int position_y = rand() % size - size / 2;
		const Point new_source(source.x + position_x, source.y + position_y);
		glBegin(GL_LINES);
		SetColor(new_source);
		//to rotate the line, change here, use a theta 
		glVertex2d(target.x - size / 2 + position_x, target.y + position_y);
		glVertex2d(target.x + size / 2 + position_x, target.y + position_y);

		glEnd();
	}
}
void ScatteredLineBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

