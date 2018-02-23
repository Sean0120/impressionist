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
#include<math.h>
extern float frand();
const GLfloat Pi = 3.1415926536f;

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
	int width = pDoc->getLineWidth();
	int angle = pDoc->getLineAngle();
	if (pDoc == NULL) {
		printf("ScatteredLineBrush::BrushMove  document is NULL\n");
		return;
	}
	glLineWidth(width);
	srand((unsigned)time(NULL));
	if (pDoc->getStrokeDirection() == SLIDER || pDoc->getStrokeDirection() == BRUSH_DIRECTION) {
		for (int i = 0; i < 4; ++i) {
			int position_x = rand() % size - size / 2;
			int position_y = rand() % size - size / 2;
			const Point new_source(source.x + position_x, source.y + position_y);
			glBegin(GL_LINES);
			SetColor(new_source);
			//to rotate the line, change here, use a theta 
			glVertex2d(target.x - size / 2 * cos(2 * Pi*angle / 360) + position_x, target.y + position_y - size / 2 * sin(2 * Pi*angle / 360));
			glVertex2d(target.x + size / 2 * cos(2 * Pi*angle / 360) + position_x, target.y + position_y + size / 2 * sin(2 * Pi*angle / 360));

			glEnd();
		}
	}
	else if (pDoc->getStrokeDirection() == GRADIENT) {
		for (int i = 0; i < 4; ++i) {
			int position_x = rand() % size - size / 2;
			int position_y = rand() % size - size / 2;
			const Point new_source(source.x + position_x, source.y + position_y); int Gx = pDoc->getGx(source);
			int Gy = pDoc->getGy(new_source);
			double cosAngle = Gy / sqrt(Gx*Gx + Gy*Gy);
			double sinAngle = -Gx / sqrt(Gx*Gx + Gy*Gy);
			glBegin(GL_LINES);
			SetColor(new_source);
			//to rotate the line, change here, use a theta 
			glVertex2d(target.x - size / 2 * cosAngle + position_x, target.y + position_y - size / 2 * sinAngle);
			glVertex2d(target.x + size / 2 * cosAngle + position_x, target.y + position_y + size / 2 * sinAngle);

			glEnd();
		}
	}
}
void ScatteredLineBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

