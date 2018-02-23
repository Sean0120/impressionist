// 
// impressionistDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//

#include <FL/fl_ask.H>

#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "ImpBrush.h"

// Include individual brush headers here.
#include "PointBrush.h"
#include "CircleBrush.h"
#include "LineBrush.h"
#include "ScatteredPointBrush.h"
#include "ScatteredLineBrush.h"
#include "ScatteredCircleBrush.h"
#include "BlurBrush.h"
#include "SharpeningBrush.h"
#include "WarpBrush.h"
#include "EraserBrush.h"
#include <iostream>
using namespace std;
#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

GLubyte* BLACKCOLOR = new GLubyte[3] ;
ImpressionistDoc::ImpressionistDoc() 
{
	// Set NULL image name as init. 
	m_imageName[0]	='\0';	

	m_nWidth		= -1;
	m_ucBitmap		= NULL;
	m_ucPainting	= NULL;
	m_ucUndoPainting = NULL;
	m_ucPaintingWithDim = NULL;



	memset(BLACKCOLOR, 0, 3);
	// create one instance of each brush
	ImpBrush::c_nBrushCount	= NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes	= new ImpBrush* [ImpBrush::c_nBrushCount];

	ImpBrush::c_pBrushes[BRUSH_POINTS]	= new PointBrush( this, "Points" );

	// Note: You should implement these 5 brushes.  They are set the same (PointBrush) for now
	ImpBrush::c_pBrushes[BRUSH_LINES]				
		= new LineBrush( this, "Lines" );
	ImpBrush::c_pBrushes[BRUSH_CIRCLES]				
		= new CircleBrush( this, "Circles" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS]	
		= new ScatteredPointBrush( this, "Scattered Points" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]		
		= new ScatteredLineBrush( this, "Scattered Lines" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES]	
		= new ScatteredCircleBrush( this, "Scattered Circles" );
	//the new brush :: blur
	ImpBrush::c_pBrushes[BRUSH_BLUR]
		= new BlurBrush(this, "Blur");
	//the new brush :: sharpening
	ImpBrush::c_pBrushes[BRUSH_SHARPENING]
		= new SharpeningBrush(this, "Sharpening");
	//warp brush
	ImpBrush::c_pBrushes[BRUSH_WARP]
		= new WarpBrush(this, "warp");

	//Eraser
	ImpBrush::c_pBrushes[BRUSH_ERASER]
		= new EraserBrush(this, "warp");

	// make one of the brushes current
	m_pCurrentBrush	= ImpBrush::c_pBrushes[0];

}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui) 
{
	m_pUI	= ui;
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName() 
{
	return m_imageName;
}

//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type)
{
	m_pCurrentBrush	= ImpBrush::c_pBrushes[type];
}

//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getSize()
{
	return m_pUI->getSize();
}
//  return the line width of the line brush
int ImpressionistDoc::getLineWidth()
{
	return m_pUI->getLineWidth();
}
//  return the line angle of the line brush
int ImpressionistDoc::getLineAngle()
{
	return m_pUI->getLineAngle();
}
//return the alpha
float ImpressionistDoc::getAlpha() {
	return m_pUI->getAlpha();
}
//get the stroke direction
int ImpressionistDoc::getStrokeDirection()
{
	return m_pUI->getStrokeDirection();
}

//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(char *iname) 
{
	// try to open the image to read
	unsigned char*	data;
	int				width, 
					height;

	if ( (data=readBMP(iname, width, height))==NULL ) 
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	// reflect the fact of loading the new image
	m_nWidth		= width;
	m_nPaintWidth	= width;
	m_nHeight		= height;
	m_nPaintHeight	= height;

	// release old storage
	if ( m_ucBitmap ) delete [] m_ucBitmap;
	if ( m_ucPainting ) delete [] m_ucPainting;
	if (m_ucUndoPainting) delete[] m_ucUndoPainting;
	if (m_ucPaintingWithDim) delete[] m_ucPaintingWithDim;

	m_ucBitmap		= data;

	// allocate space for draw view
	m_ucPainting	= new unsigned char [width*height*3];
	memset(m_ucPainting, 0, width*height*3);
	m_ucPaintingWithDim = new unsigned char[width*height * 3];
	memset(m_ucPaintingWithDim, 0, width*height * 3);

	m_ucUndoPainting = new unsigned char[width*height * 3];
	memset(m_ucUndoPainting, 0, width*height * 3);

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
								m_pUI->m_mainWindow->y(), 
								width*2, 
								height+25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);	
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);	
	m_pUI->m_paintView->refresh();


	return 1;
}


//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(char *iname) 
{

	writeBMP(iname, m_nPaintWidth, m_nPaintHeight, m_ucPainting);

	return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas() 
{


	if (m_ucPaintingWithDim)
	{
		delete[] m_ucPaintingWithDim;
		m_ucPaintingWithDim = new unsigned char[m_nPaintWidth*m_nPaintHeight * 3];
		memset(m_ucPaintingWithDim, 0, m_nPaintWidth*m_nPaintHeight * 3);
	}
	if (m_ucUndoPainting)
	{
		delete[] m_ucUndoPainting;
		m_ucUndoPainting = new unsigned char[m_nPaintWidth*m_nPaintHeight * 3];
		memset(m_ucUndoPainting, 0, m_nPaintWidth*m_nPaintHeight * 3);


	}
	// Release old storage
	if ( m_ucPainting ) 
	{
		delete [] m_ucPainting;

		// allocate space for draw view
		m_ucPainting	= new unsigned char [m_nPaintWidth*m_nPaintHeight*3];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight*3);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}
	
	return 0;
}

//load another image
int ImpressionistDoc::loadAnotherImage(char *iname)
{
	// try to open the image to read
	unsigned char*	data;
	int				width,
		height;

	if ((data = readBMP(iname, width, height)) == NULL)
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	// reflect the fact of loading the new image
	if (m_nWidth != width || m_nPaintWidth != width || m_nHeight != height) {
		fl_alert("Dimension is different from the previous one");
		return 0;
	}
	

	// release old storage
	
	if (m_ucPainting) delete[] m_ucPainting;
	
	for (int i = 0; i < width*height * 3; i++) {
		m_ucBitmap[i] = (m_ucBitmap[i] + data[i]) / 2;
	}
	delete [] data;
	// allocate space for draw view
	m_ucPainting = new unsigned char[width*height * 3];
	memset(m_ucPainting, 0, width*height * 3);

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(),
		m_pUI->m_mainWindow->y(),
		width * 2,
		height + 25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);
	m_pUI->m_paintView->refresh();


	return 1;
}
//the function for New Mural Image
int ImpressionistDoc::setMuralImage(char* iname) {
	// try to open the image to read
	unsigned char*	data;
	int				width,
		height;

	if ((data = readBMP(iname, width, height)) == NULL)
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	// reflect the fact of loading the new image
	if (m_nWidth != width || m_nPaintWidth != width || m_nHeight != height) {
		fl_alert("Dimension is different from the previous one");
		return 0;
	}


	// release old storage

	if (m_ucBitmap) delete[] m_ucBitmap;
	m_ucBitmap =  data;

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);
	m_pUI->m_origView->refresh();



}

int	ImpressionistDoc::autoDraw()
{
    m_pUI->m_paintView->allowAutoDraw();
	
	return 0;
}
int	ImpressionistDoc::applyKernel() 
{
	GLubyte color[3];
	//first we need to calculate the big the kernel is 
	int xR = m_pUI->m_nKernelWidth/2;
	int yR = m_pUI->m_nKernelHeight/2;
	//cout <<"sss" <<yR << endl;
	for (int i = 0; i < m_nPaintHeight * m_nPaintWidth; ++i) {
		//check whether this point is valid
		Point target(i%m_nPaintWidth, i / m_nPaintWidth);
		if (target.x + xR < m_nPaintWidth && target.x - xR > 0 && target.y + yR < m_nPaintHeight && target.y - yR > 0) {
			//it is valid, now apply the kernel
			int new_color_result[3] = { 0 };
			for (int j = -xR; j < xR + 1; ++j) {
				for (int k = -yR; k < yR + 1; ++k) {
					int position = (xR + j) + (yR + k) * m_pUI->m_nKernelWidth;
					
						
					memcpy(color,GetOriginalPixel(target.x + j, target.y - k), 3);
					//if (i < 1000)
						//cout << int(color[0]) << "ss " << int(color[1]) << "ss" << int(color[2]) << "ss" << atoi(m_pUI->m_MatrixInput[position]->value())<<endl;
					new_color_result[0] += color[0] * atoi(m_pUI->m_MatrixInput[position]->value());
					new_color_result[1] += color[1] * atoi(m_pUI->m_MatrixInput[position]->value());
					new_color_result[2] += color[2] * atoi(m_pUI->m_MatrixInput[position]->value());
					//if (i < 1000)
						//cout << new_color_result[0] << "xxx"<< new_color_result[1] << "ddd" << new_color_result[2] <<endl;
				}
			}
			if (m_pUI->m_nNormalized) {
				int add_result = 0;
				for (int m = 0; m < m_pUI->m_nKernelWidth*m_pUI->m_nKernelHeight; m++) {
					add_result += atoi(m_pUI->m_MatrixInput[m]->value());
				}
				new_color_result[0] /= add_result;
				new_color_result[1] /= add_result;
				new_color_result[2] /= add_result;
			}
			if (new_color_result[0] > 255)
				new_color_result[0] = 255;
			if (new_color_result[1] > 255)
				new_color_result[1] = 255;
			if (new_color_result[2] > 255)
				new_color_result[2] = 255;
			m_ucPainting[3*i] = new_color_result[0];
			m_ucPainting[3*i+1] = new_color_result[1];
			m_ucPainting[3*i+2] = new_color_result[2];

		}
	}
	
	m_pUI->m_paintView->refresh();
	return 1;
}

void	ImpressionistDoc::drawEdge() {
	//draw the edge
	GLubyte color[3];
	for (int i = 0; i < m_nPaintHeight * m_nPaintWidth; ++i) {
		//check whether this point is valid
		Point target(i%m_nPaintWidth, i / m_nPaintWidth);
		int Gradient_x = getGx(target);
		int Gradient_y = getGy(target);
		float Gradient = sqrt(Gradient_x*Gradient_x + Gradient_y*Gradient_y);
		if (Gradient > m_pUI->m_nEgdeThreshold) {
			m_ucPainting[3 * i] = 255;
			m_ucPainting[3 * i + 1] =255;
			m_ucPainting[3 * i + 2] = 255;
		}
		else
		{
			m_ucPainting[3 * i] = 0;
			m_ucPainting[3 * i + 1] = 0;
			m_ucPainting[3 * i + 2] = 0;
		}
	}

	m_pUI->m_paintView->refresh();
	
}




//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nWidth ) 
		x = m_nWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nHeight ) 
		y = m_nHeight-1;

	return (GLubyte*)(m_ucBitmap + 3 * (y*m_nWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( const Point p )
{
	return GetOriginalPixel( p.x, p.y );
}

//get the color of the pixel in the image, if it is out of the image, set it to black
GLubyte* ImpressionistDoc::GetOriginalPixelBlack(const Point p) {
	if (p.x < m_nWidth && p.y < m_nHeight && p.x > 0 && p.y > 0)
		return (GLubyte*)(m_ucPainting + 3 * (p.y*m_nWidth + p.x));
	else
	{
		return BLACKCOLOR;
	}
}
//set the color of the pixel in the paint image
void ImpressionistDoc::SetPaintPixel(int x, int y, const GLubyte* color)
{
	//directly ignore outbound situations
	if (x < m_nWidth && y < m_nHeight && x > 0 && y > 0)
		memcpy(m_ucPainting + 3 * (y * m_nWidth + x), color, 3);
}

//Helper function to compute the gradient
int ImpressionistDoc::getGx(const Point p)
{
	return (*(GetOriginalPixel(p.x + 1, p.y - 1)) - *(GetOriginalPixel(p.x - 1, p.y - 1))) +
		(*(GetOriginalPixel(p.x + 1, p.y + 1)) - *(GetOriginalPixel(p.x - 1, p.y + 1))) +
		2 * (*(GetOriginalPixel(p.x + 1, p.y)) - *(GetOriginalPixel(p.x - 1, p.y)));
}

int ImpressionistDoc::getGy(const Point p)
{
	return (*(GetOriginalPixel(p.x + 1, p.y + 1)) - *(GetOriginalPixel(p.x + 1, p.y - 1))) +
		(*(GetOriginalPixel(p.x - 1, p.y + 1)) - *(GetOriginalPixel(p.x - 1, p.y - 1))) +
		2 * (*(GetOriginalPixel(p.x, p.y + 1)) - *(GetOriginalPixel(p.x, p.y - 1)));
}

