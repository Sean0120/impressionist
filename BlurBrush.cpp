//
// BlurBrush.cpp
//
// The implementation of Blur Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "BlurBrush.h"

extern float frand();

BlurBrush::BlurBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void BlurBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();



	glPointSize((float)size);

	BrushMove(source, target);
}

void BlurBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("BlurBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_POINTS);
	for (int i = -3; i < 4; ++i) {
		for (int j = -3; j < 4; ++j) {
			if (source.x + i < pDoc->m_nWidth && source.x >0 && source.y + j < pDoc->m_nHeight && source.y + j > 0) {
				Point new_source(source.x + i, source.y + j);
				SetBlurColor(source);
				glVertex2d(target.x + i, target.y + j);
			}
		}
	}
	glEnd();
}

void BlurBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

void BlurBrush::SetBlurColor(const Point source) {
	ImpressionistDoc* pDoc = GetDocument();

	float* new_color = pDoc->m_pUI->getColor();
	GLubyte color[3];
	float alpha = pDoc->getAlpha();
	int new_alpha = alpha * 255;
	int new_color_result[3] = {0};
	int count = 0;
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			if (source.x + i < pDoc->m_nWidth && source.x >0 && source.y + j < pDoc->m_nHeight && source.y + j > 0) {
				memcpy(color, pDoc->GetOriginalPixel(source.x,source.y), 3);
				new_color_result[0] += color[0] * new_color[0];
				new_color_result[1] += color[1] * new_color[1];
				new_color_result[2] += color[2] * new_color[2];
				count++;
			}
		}
	}
	glColor4ub(new_color_result[0]/count, new_color_result[1]/count, new_color_result[2]/count, new_alpha);


}