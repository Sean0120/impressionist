//
//  LineBrush.cpp
//  
//
//  Created by Apple on 2018/2/14.
//
#include<iostream>
#include "LineBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include <math.h>
using namespace std;
extern float frand();
const GLfloat Pi = 3.1415926536f;
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
	int width = pDoc->getLineWidth();
	int angle = pDoc->getLineAngle();
	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}
	glLineWidth(width);
	glBegin(GL_LINES);
	SetColor(source);
	if (pDoc->getStrokeDirection() == SLIDER || pDoc->getStrokeDirection() == BRUSH_DIRECTION) {
		//to rotate the line, change here, use a theta 
		glVertex2d(target.x - size / 2 * cos(2 * Pi*angle / 360), target.y - size / 2 * sin(2 * Pi*angle / 360));
		glVertex2d(target.x + size / 2 * cos(2 * Pi*angle / 360), target.y + size / 2 * sin(2 * Pi*angle / 360));

	}
	else if (pDoc->getStrokeDirection() == GRADIENT && (pDoc->getAnotherGradient() == false)) {
		int Gx = pDoc->getGx(source);
		int Gy = pDoc->getGy(source);
		double cosAngle = Gy / sqrt(Gx*Gx + Gy*Gy);
		double sinAngle = -Gx / sqrt(Gx*Gx + Gy*Gy);
		glVertex2d(target.x - size / 2 * cosAngle, target.y - size / 2 * sinAngle);
		glVertex2d(target.x + size / 2 * cosAngle, target.y + size / 2 * sinAngle);
	}
	else if ((pDoc->getStrokeDirection() == GRADIENT) && (pDoc->getAnotherGradient() == true)) {
		int Gx = pDoc->getAnotherGx(source);
		int Gy = pDoc->getAnotherGy(source);
		double cosAngle = -Gy / sqrt(Gx*Gx + Gy*Gy);
		double sinAngle = Gx / sqrt(Gx*Gx + Gy*Gy);
		glVertex2d(target.x - size / 2 * cosAngle, target.y - size / 2 * sinAngle);
		glVertex2d(target.x + size / 2 * cosAngle, target.y + size / 2 * sinAngle);
	}
	glEnd();
}

void LineBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}
