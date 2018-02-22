//
// ImpBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//
#include<iostream>
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ImpBrush.h"
using namespace std;
// Static class member initializations
int			ImpBrush::c_nBrushCount	= 0;
ImpBrush**	ImpBrush::c_pBrushes	= NULL;

ImpBrush::ImpBrush(ImpressionistDoc*	pDoc, 
				   char*				name) :
					m_pDoc(pDoc), 
					m_pBrushName(name)
{
}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::GetDocument(void)
{
	return m_pDoc;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpBrush::BrushName(void)
{
	return m_pBrushName;
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
void ImpBrush::SetColor (const Point source)
{
	ImpressionistDoc* pDoc = GetDocument();
	//this is for the color ratio
	float* new_color = pDoc->m_pUI->getColor();
	GLubyte color[3];
	float alpha = pDoc->getAlpha();
	int new_alpha = alpha * 255;
	memcpy(color, pDoc->GetOriginalPixel(source), 3);
	int new_color_result[3] = { 0 };
	new_color_result[0] = color[0] * new_color[0];
	new_color_result[1] = color[1] * new_color[1];
	new_color_result[2] = color[2] * new_color[2];
	for (int i = 0; i < 3; i++) {
		if (new_color_result[i] == 0) {
			new_color_result[i] = 1;
		}
	}
	glColor4ub(new_color_result[0], new_color_result[1], new_color_result[2], new_alpha);

}
