//
//  ScatteredPointBrush.cpp
//  
//
//  Created by Apple on 2018/2/14.
//

#include "ScatteredPointBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include<cstdlib>
#include<ctime>
extern float frand();

ScatteredPointBrush::ScatteredPointBrush( ImpressionistDoc* pDoc, char* name ) :
    ImpBrush(pDoc, name)
{
}

void ScatteredPointBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	

	BrushMove(source, target);
}

void ScatteredPointBrush::BrushMove( const Point source, const Point target )
{
	
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int size = pDoc->getSize();
	glPointSize(1);
	if (pDoc == NULL) {
		printf("ScatteredPointBrush::BrushMove  document is NULL\n");
		return;
	}
	srand((unsigned)time(NULL));
	for (int i = 0; i < size * 2; ++i) {
		int position_x = rand() % size - size/2;
		int position_y = rand() % size - size/2;
		const Point new_source(source.x + position_x, source.y + position_y);
		glBegin(GL_POINTS);
		SetColor(new_source);

		glVertex2d(target.x + position_x , target.y + position_y);

		glEnd();
	}
}

void ScatteredPointBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}


