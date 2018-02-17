//
//  LineBrush.cpp
//  
//
//  Created by Apple on 2018/2/14.
//

#include "LineBrush.hpp"
#include "impressionistDoc.h"
#inlcude "impressionistUI.h"

extern float frand();

LineBrush::LineBrush( ImpressionistDoc* pDoc, char* name) :
    Impbrush(pDoc, name)
{
}

void LineBrush::BrushBegin( const Point source, const Point target )
{
    //TODO
}

void LineBrush::BrushMove( const Point source, const Point target )
{
    //TODO
}

void LineBrush::BrushEnd( const Point source, const point target )
{
    //TODO
}
