//
//  LineBrush.cpp
//  
//
//  Created by Apple on 2018/2/14.
//

#include "LineBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"

extern float frand();

LineBrush::LineBrush( ImpressionistDoc* pDoc, char* name) :
    ImpBrush(pDoc, name)
{
}

void LineBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	

	BrushMove(source, target);
}

void LineBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int size = pDoc->getSize();


	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}
	glLineWidth(1);
	glBegin(GL_LINES);
	SetColor(source);
	//to rotate the line, change here, use a theta 
	glVertex2d(target.x-size/2, target.y);
	glVertex2d(target.x + size / 2, target.y );

	glEnd();
}

void LineBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}
