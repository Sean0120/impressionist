//
//  ScatteredPointBrush.hpp
//  
//
//  Created by Apple on 2018/2/14.
//

#ifndef ScatteredPointBrush_hpp
#define ScatteredPointBrush_hpp

#inclued "ImpBrush.h"

class ScatteredPointBrush : public ImpBrush
{
public:
    ScatteredPointBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL);
    
    void BrushBegin( const Point source, const Point target );
    void BrushMove( const Point source, const Point target );
    void BrushEnd( const Point source, const Point target );
    char* BrushName( void );
};

#endif /* ScatteredPointBrush_hpp */
