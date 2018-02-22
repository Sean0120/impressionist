//
//  LineBrush.hpp
//  
//
//  Created by Apple on 2018/2/14.
//

#ifndef LineBrush_hpp
#define LineBrush_hpp

#include "ImpBrush.h"

class LineBrush : public ImpBrush
{
public:
    LineBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );
    
    void BrushBegin( const Point source, const Point target );
    void BrushMove( const Point source, const Point target );
    void BrushEnd( const Point source, const Point target );
    char* BrushName( void );
};

#endif /* LineBrush_hpp */
