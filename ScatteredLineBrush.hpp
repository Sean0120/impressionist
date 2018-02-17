//
//  ScatteredLineBrush.hpp
//  
//
//  Created by Apple on 2018/2/14.
//

#ifndef ScatteredLineBrush_hpp
#define ScatteredLineBrush_hpp

#include "ImpBrush.h"

class ScatteredLineBrush : public ImpBrush
{
public:
    ScatteredLineBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );
    
    void BrushBegin( const Point source, const Point target );
    void BrushMove( const Point source, const Point target );
    void BrushEnd( const Point source, const Point target );
    char* BrushName( void );
};

#endif /* ScatteredLineBrush_hpp */
