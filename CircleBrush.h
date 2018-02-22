//
//  CircleBrush.hpp
//  
//
//  Created by Apple on 2018/2/14.
//

#ifndef CircleBrush_hpp
#define CircleBrush_hpp

#include "ImpBrush.h"

class CircleBrush : public ImpBrush
{
public:
	CircleBrush(ImpressionistDoc* pDoc, char* name = NULL);

    void BrushBegin( const Point source, const Point target );
    void BrushMove( const Point source, const Point target );
    void BrushEnd( const Point course, const Point target );
    char* BrushName( void );
    
};
#endif /* CircleBrush_hpp */
