//
//  ScatteredCircleBrush.hpp
//  
//
//  Created by Apple on 2018/2/14.
//

#ifndef ScatteredCircleBrush_hpp
#define ScatteredCircleBrush_hpp

#include "ImpBrush.h"

class ScatteredCircleBrush : public ImpBrush
{
public:
    ScatteredCircleBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL);
    
    void BrushBegin( const Point source, const Point target );
    void BrushMove( const Point source, const Point target );
    void BrushEnd( const Point source, const Point target );
    char* BrushName( void );
};

#endif /* ScatteredCircleBrush_hpp */
