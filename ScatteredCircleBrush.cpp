//
//  ScartteredCircleBrush.cpp
//  
//
//  Created by Apple on 2018/2/14.
//

#include "ScatteredCircleBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include <math.h>
#include<cstdlib>
#include<ctime>
extern float frand();
const int n = 200;
static GLfloat R;
const GLfloat Pi = 3.1415926536f;

ScatteredCircleBrush::ScatteredCircleBrush( ImpressionistDoc* pDoc, char* name) :
    ImpBrush(pDoc, name)
{
}

void ScatteredCircleBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc * pDoc = GetDocument();
	ImpressionistUI *dlg = pDoc->m_pUI;
	int size = pDoc->getSize();
	R = (float)size * 0.5;
	BrushMove(source, target);
}

void ScatteredCircleBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int size = pDoc->getSize();
	if (pDoc == NULL) {
		printf("ScatteredCircleBrush::BrushMove  document is NULL\n");
		return;
	}
	srand((unsigned)time(NULL));
	for (int i = 0; i < 4; i++) {
		int position_x = rand() % size - size / 2;
		int position_y = rand() % size - size / 2;
		const Point new_source(source.x + position_x, source.y + position_y);
		glBegin(GL_POLYGON);
		SetColor(new_source);
		for (int i = 0; i < n; i++)
			glVertex2f(target.x + R*cos(2 * Pi / n*i) + position_x, target.y + R*sin(2 * Pi / n*i) + position_y);
		glEnd();
	}
}

void ScatteredCircleBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}


