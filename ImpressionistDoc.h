// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include "impressionist.h"
#include "bitmap.h"

class ImpressionistUI;

class ImpressionistDoc 
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int		loadImage(char *iname);			// called by the UI to load image
	int		saveImage(char *iname);			// called by the UI to save image


	int     clearCanvas();                  // called by the UI to clear the drawing canvas
	int     loadAnotherImage(char* iname);	//dissolve two image
	void	setBrushType(int type);			// called by the UI to set the brushType
	int		getSize();						// get the UI size
	void	setSize(int size);				// set the UI size£¬i have no idea about the aim
	int     getLineWidth();					//new: get the line width of line brush
	int     getLineAngle();					//get the line angle of line brush
	float   getAlpha();						//get the alpha
	char*	getImageName();					// get the current image name
	int     getStrokeDirection();           //get the stroke direction
	int		setMuralImage(char* iname);		//the function for New Mural Image
	int		autoDraw();						//Auto draw
	int		applyKernel();					//apply kernel on the current paintview
	void	drawEdge();						//draw the edges
// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth, 
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, 
					m_nPaintHeight;	
	// Bitmaps for original image and painting.
	unsigned char*	m_ucBitmap;
	unsigned char*	m_ucPainting;
	//Bitmaps for undo paiting
	unsigned char*  m_ucUndoPainting;
	//Bitmaps for background
	unsigned char* m_ucPaintingWithDim;


	// The current active brush.
	ImpBrush*			m_pCurrentBrush;	
	// Size of the brush.
	int m_nSize;							

	ImpressionistUI*	m_pUI;

// Operations
public:
	// Get the color of the original picture at the specified coord
	GLubyte* GetOriginalPixel( int x, int y );   
	// Get the color of the original picture at the specified point	
	GLubyte* GetOriginalPixel( const Point p );  
	void SetPaintPixel(int x, int y, const GLubyte* color);
	GLubyte* GetOriginalPixelBlack(const Point p);// if the point is out of the image, set the color to black

	// Helper function to compute the gradient
	int getGx(const Point p);
	int getGy(const Point p);


private:
	char			m_imageName[256];

};

extern void MessageBox(char *message);

#endif
