//
//  CircleBrush.cpp
//  
//
//  Created by Apple on 2018/2/14.
//

#include "CircleBrush.hpp"
#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"

extern float frand();

CircleBrush::CircleBrush( ImpressionistDoc* pDoc, char* name ) :
    ImpBrush(pDoc, name)
{
}

void CircleBrush::BrushBegin( const Point source, const Point target )
{
    //TODO
}

void CircleBrush::BrushMove( const Point source, const Point target )
{
    //TODO
}

void CircleBrush::BrushEnd( const Point source, const Point target )
{
    //TODO
}
