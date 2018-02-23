//
// paintview.cpp
//
// The code maintaining the painting view of the input images
//

#include "Impressionist.h"
#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include "paintview.h"
#include "ImpBrush.h"
#include <iostream>
#include <math.h>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<algorithm>
using namespace std;

#define LEFT_MOUSE_DOWN		1
#define LEFT_MOUSE_DRAG		2
#define LEFT_MOUSE_UP		3
#define RIGHT_MOUSE_DOWN	4
#define RIGHT_MOUSE_DRAG	5
#define RIGHT_MOUSE_UP		6


#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#define max(a, b)	( ( (a)>(b) ) ? (a) : (b) )
#endif

static int		eventToDo;
static int		isAnEvent=0;
static Point	coord;

PaintView::PaintView(int			x,
	int			y,
	int			w,
	int			h,
	const char*	l)
	: Fl_Gl_Window(x, y, w, h, l), rightMouseStart(), rightMouseEnd(), leftMouseStart(), leftMouseEnd()
{
	m_nWindowWidth = w;
	m_nWindowHeight = h;
    
    isAutoDraw=false;//for auto draw
}


void PaintView::draw()
{
	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_FRONT_AND_BACK);
	#endif // !MESA

	if(!valid())
	{

		glClearColor(0.7f, 0.7f, 0.7f, 1.0);

		// We're only using 2-D, so turn off depth 
		glDisable( GL_DEPTH_TEST );

		ortho();

		glClear( GL_COLOR_BUFFER_BIT );

		// Enable Alpha
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	Point scrollpos;// = GetScrollPosition();
	scrollpos.x = 0;
	scrollpos.y	= 0;

	m_nWindowWidth	= w();
	m_nWindowHeight	= h();

	int drawWidth, drawHeight;
	drawWidth = min( m_nWindowWidth, m_pDoc->m_nPaintWidth );
	drawHeight = min( m_nWindowHeight, m_pDoc->m_nPaintHeight );

	int startrow = m_pDoc->m_nPaintHeight - (scrollpos.y + drawHeight);
	if ( startrow < 0 ) startrow = 0;

	m_pPaintBitstart = m_pDoc->m_ucPainting + 
		3 * ((m_pDoc->m_nPaintWidth * startrow) + scrollpos.x);
	m_pDimBitstart = m_pDoc->m_ucPaintingWithDim +
		3 * ((m_pDoc->m_nPaintWidth * (startrow)) + scrollpos.x);


	m_nDrawWidth	= drawWidth;
	m_nDrawHeight	= drawHeight;

	m_nStartRow		= startrow;
	m_nEndRow		= startrow + drawHeight;
	m_nStartCol		= scrollpos.x;
	m_nEndCol		= m_nStartCol + drawWidth;

	if ( m_pDoc->m_ucPainting && !isAnEvent)
	{
		RestoreContent();

	}
		

	if ( m_pDoc->m_ucPainting && isAnEvent) 
	{



		// Clear it after processing.
		isAnEvent	= 0;	

		Point source( coord.x + m_nStartCol, m_nEndRow - coord.y );
		Point target( coord.x, m_nWindowHeight - coord.y );
		
		// This is the event handler
		switch (eventToDo) 
		{
		case LEFT_MOUSE_DOWN:
			if (source.x > m_nDrawWidth || source.y < 0)
				break;
			if (m_pDoc->getStrokeDirection() == BRUSH_DIRECTION) {

				leftMouseStart = target;
				break;
			}
			SaveUndoPainting();
			m_pDoc->m_pCurrentBrush->BrushBegin( source, target );

			SaveCurrentContent();
			RestoreContent();

			break;
		case LEFT_MOUSE_DRAG:
			if (source.x > m_nDrawWidth || source.y < 0)
				break;
			if (m_pDoc->getStrokeDirection() == BRUSH_DIRECTION) {
				leftMouseEnd = target;
				int angle;
				double xDiff = leftMouseEnd.x - leftMouseStart.x;
				double yDiff = leftMouseEnd.y - leftMouseStart.y;
				if (xDiff == 0) {
					if (yDiff == 0)
						break;
					else if (yDiff>0)
						angle = 90;
					else
						angle = 270;
				}
				else {
					double arcAngle = atan(yDiff / xDiff);
					const double Pi = 3.1415926536;
					angle = arcAngle / Pi * 180;
					if (xDiff>0) {
						if (yDiff == 0)
							angle = 0;
						else if (yDiff<0)
							angle = 360 + angle;
					}
					else if (xDiff<0) {
						angle = angle + 180;
					}
				}
				m_pUI->setLineAngle(angle);

				m_pDoc->m_pCurrentBrush->BrushMove(source, target);

				leftMouseStart = target;

				break;
			}
			m_pDoc->m_pCurrentBrush->BrushMove( source, target );


			SaveCurrentContent();
			RestoreContent();


			break;
		case LEFT_MOUSE_UP:
			m_pDoc->m_pCurrentBrush->BrushEnd( source, target );
			SaveCurrentContent();
			RestoreContent();
		
			break;
		case RIGHT_MOUSE_DOWN:
			if (m_pDoc->getStrokeDirection() == SLIDER) {
				SaveCurrentContent();

				rightMouseStart = target;
			}   //set the origin of right mouse


			break;

		case RIGHT_MOUSE_UP:
			if (m_pDoc->getStrokeDirection() == SLIDER) {
				rightMouseEnd = target;
				int angle;
				double xDiff = rightMouseEnd.x - rightMouseStart.x;
				double yDiff = rightMouseEnd.y - rightMouseStart.y;
				if (xDiff == 0) {
					if (yDiff == 0)
						break;
					else if (yDiff>0)
						angle = 90;
					else
						angle = 270;
				}
				else {
					double arcAngle = atan(yDiff / xDiff);
					const double Pi = 3.1415926536;
					angle = arcAngle / Pi * 180;
					if (xDiff>0) {
						if (yDiff == 0)
							angle = 0;
						else if (yDiff<0)
							angle = 360 + angle;
					}
					else if (xDiff<0) {
						angle = angle + 180;
					}
				}
				m_pUI->setLineAngle(angle);
				RestoreContent();
			}
			break;

		default:
			printf("Unknown event!!\n");		
			break;
		}
	}
    
    //Check if allow auto draw
    if(isAutoDraw==true)
    {
        //SaveUndoPainting();
        autoDraw();
		
		isAutoDraw = false;
		
    }
	if (m_pUI->m_nAlphaOfBackground != 0) {
		switchToDim();
		//glDrawBuffer(GL_BACK);
		glRasterPos2i(0, m_nWindowHeight - drawHeight);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, m_pDoc->m_nWidth);
		glDrawPixels(drawWidth, drawHeight, GL_RGB, GL_UNSIGNED_BYTE, m_pDimBitstart);
	}
	glFlush();


	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_BACK);
	#endif // !MESA

}


int PaintView::handle(int event)
{
	coord.x = Fl::event_x();
	coord.y = Fl::event_y();
	Point marker(coord.x, m_nWindowHeight - coord.y);

	switch(event)
	{
	case FL_ENTER:
	    redraw();
		break;
	case FL_PUSH:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DOWN;
		else
			eventToDo=LEFT_MOUSE_DOWN;
		isAnEvent=1;
		redraw();
		break;
	case FL_DRAG:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DRAG;
		else
			eventToDo=LEFT_MOUSE_DRAG;
		isAnEvent=1;
		//set the maker here 
		m_pUI->setMarkerPoint(marker);
		
		
		redraw();
		break;
	case FL_RELEASE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_UP;
		else
			eventToDo=LEFT_MOUSE_UP;
		isAnEvent=1;
		redraw();
		break;
	case FL_MOVE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		//set the marker here 
		m_pUI->setMarkerPoint(marker);
		break;
	default:
		return 0;
		break;

	}



	return 1;
}

void PaintView::refresh()
{
	redraw();
}

void PaintView::resizeWindow(int width, int height)
{
	resize(x(), y(), width, height);
}

void PaintView::SaveCurrentContent()
{
	// Tell openGL to read from the front buffer when capturing
	// out paint strokes
	glReadBuffer(GL_FRONT);

	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei( GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	
	glReadPixels( 0, 
				  m_nWindowHeight - m_nDrawHeight, 
				  m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart );
}


void PaintView::RestoreContent()
{
	glDrawBuffer(GL_BACK);

	glClear( GL_COLOR_BUFFER_BIT );

	glRasterPos2i( 0, m_nWindowHeight - m_nDrawHeight );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glPixelStorei( GL_UNPACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	glDrawPixels( m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart);

//	glDrawBuffer(GL_FRONT);
}

void PaintView::SaveUndoPainting() {
	if(m_pDoc->m_ucUndoPainting) delete[] m_pDoc->m_ucUndoPainting;
	int buffer_size = m_pDoc->m_nPaintWidth*m_pDoc->m_nPaintHeight * 3;
	m_pDoc->m_ucUndoPainting = new unsigned char[buffer_size];
	memcpy(m_pDoc->m_ucUndoPainting, m_pDoc->m_ucPainting,buffer_size);
	
}

//for auto draw
void PaintView::allowAutoDraw()
{
    isAutoDraw=true;
	redraw();
}


void PaintView::autoDraw()
{
	
	
	srand(time(NULL));
	vector<int> index;
	int spacing = m_pUI->getAutoDrawSpace();
	int height = m_pDoc->m_nHeight;
	int width = m_pDoc->m_nWidth;

	ImpBrush* currentBrush = m_pDoc->m_pCurrentBrush;

	//randAttr part
	bool randAttr = m_pUI->getRandomSize();
	int size = m_pUI->getSize();
	int lineWidth = m_pUI->getLineAngle();
	int lineAngle = m_pUI->getLineAngle();
	
	//calculate how many points there are 
	int xTimes = width / spacing;
	int yTimes = height / spacing;

	for (int i = 0; i < xTimes*yTimes; i++)
		index.push_back(i);
	random_shuffle(index.begin(), index.end());
	//the start y is not zero
	int offset = m_nWindowHeight - m_nDrawHeight;
	int startX = spacing / 2;
	int startY = spacing / 2 + offset;
	//start point is the left down corner

	for (int i = 0; i < index.size(); i++) {
		int position = index.at(i);
		int x = startX + (position % xTimes)*spacing;
		int y = startY + (position / xTimes)*spacing;
		Point target(x, y);
		if (randAttr) {
			m_pUI->setSize(size + rand() % 10 - 5);
			m_pUI->setLineAngle(lineAngle + rand() % 90 - 45);
			m_pUI->setLineWidth(lineWidth + rand() % 10 - 5);
		}
		currentBrush->BrushBegin(target, target);
		currentBrush->BrushEnd(target, target);
		
	}
	
	//set back to origin
	m_pUI->setSize(size);
	m_pUI->setLineAngle(lineAngle);
	m_pUI->setLineWidth(lineWidth);
	//save the current content
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth);

	glReadPixels(0,
		m_nWindowHeight - m_nDrawHeight,
		m_nDrawWidth,
		m_nDrawHeight,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		m_pPaintBitstart);


	/*
    bool randomSize=m_pUI->getRandomSize();
    int space=m_pUI->getAutoDrawSpace();
    int ori_Size=m_pUI->getSize();
    srand((unsigned)time(NULL));
    for(int i=0;i<m_nDrawWidth/space+1;i++)
    {
        for(int j=0;j<m_nDrawHeight/space+1;j++)
        {
            Point current_Source(space*i+m_nStartCol, space*j-m_nWindowHeight+m_nStartRow);
            Point current_Target(space*i, space*j);
            if(randomSize==true)
            {
                m_pUI->setSize(rand()%(ori_Size)+1);
            }
            m_pDoc->m_pCurrentBrush->BrushBegin( current_Source, current_Target );
        }
    }
	
	
    m_pUI->setSize(ori_Size);
	
	*/
}
float old_alpha = 0;
//To calculate the dim version
void PaintView::switchToDim() {

	float Alpha = m_pUI->m_nAlphaOfBackground;
	for (int i = 0; i < m_pDoc->m_nHeight *m_pDoc->m_nWidth * 3 ; i = i + 3) {
		bool judgement1 = (int(old_alpha*m_pDoc->m_ucBitmap[i]) == m_pDoc->m_ucPainting[i]);
		bool judgement2 = (int(old_alpha*m_pDoc->m_ucBitmap[i+1]) == m_pDoc->m_ucPainting[i+1]);
		bool judgement3 = (int(old_alpha*m_pDoc->m_ucBitmap[i+2]) == m_pDoc->m_ucPainting[i+2]);
		if (judgement1 && judgement2 && judgement3) {
			m_pDoc->m_ucPaintingWithDim[i] = Alpha * m_pDoc->m_ucBitmap[i];
			m_pDoc->m_ucPaintingWithDim[i+1] = Alpha * m_pDoc->m_ucBitmap[i+1];
			m_pDoc->m_ucPaintingWithDim[i+2] = Alpha * m_pDoc->m_ucBitmap[i+2];

		}
		else
		{
			m_pDoc->m_ucPaintingWithDim[i] = m_pDoc->m_ucPainting[i];
			m_pDoc->m_ucPaintingWithDim[i+1] = m_pDoc->m_ucPainting[i+1];
			m_pDoc->m_ucPaintingWithDim[i+2] = m_pDoc->m_ucPainting[i+2];
		}
	}
	
	if (Alpha > 0.0) {
	unsigned char* temp = m_pDoc->m_ucPaintingWithDim;
	m_pDoc->m_ucPaintingWithDim = m_pDoc->m_ucPainting;
	m_pDoc->m_ucPainting = temp;
	}
	m_pUI->m_paintView->refresh();
	old_alpha = Alpha;
}







