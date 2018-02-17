//
//  CircleBrush.cpp
//  
//
//  Created by Apple on 2018/2/14.
//

#include "CircleBrush.h"
#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include <math.h>
extern float frand();
const int n = 200;
static GLfloat R ;
const GLfloat Pi = 3.1415926536f;

CircleBrush::CircleBrush( ImpressionistDoc* pDoc, char* name ) :
    ImpBrush(pDoc, name){}

void CircleBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc * pDoc = GetDocument();
	ImpressionistUI *dlg = pDoc->m_pUI;
	int size = pDoc->getSize();
	R = (float)size * 0.5;
	BrushMove(source, target);
}

void CircleBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_POLYGON);
	SetColor(source);
	for (int i = 0; i<n; i++)
		glVertex2f(target.x+R*cos(2 * Pi / n*i),target.y + R*sin(2 * Pi / n*i));
	glEnd();
}

void CircleBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}
