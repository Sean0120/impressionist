//
// impressionistUI.h
//
// The user interface part for the program.
//


#include <FL/fl_ask.h>

#include <math.h>
#include<iostream>
#include "impressionistUI.h"
#include "impressionistDoc.h"
#include <iostream>
using namespace std;
//test
/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the 
project.  You can copy and paste these into your code and then change them to 
make them look how you want.  Descriptions for all of the widgets here can be found 
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------
	
	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions
		
		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
    m_mainWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v) 
	{	
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
    mySlider->labelfont(FL_COURIER);
    mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}
	

//------------Choice---------------------------------------
	
	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);
	
	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------
	
	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

    //---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o)	
{
	return ( (ImpressionistUI*)(o->parent()->user_data()) );
}


//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}


//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp" );
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_brushDialog->show();
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}
void ImpressionistUI::cb_colors(Fl_Menu_* o, void* v)
{
	whoami(o)->m_colorSelectionDialog->show();
}
//load another image
void ImpressionistUI::cb_load_another_image(Fl_Menu_* o, void* v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadAnotherImage(newfile);
	}
}
//set new mural image
void ImpressionistUI::cb_set_mural_image(Fl_Menu_* o, void* v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->setMuralImage(newfile);
	}
}
//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();

}

//new bonus: load a gradient image
void ImpressionistUI::cb_load_gradient_image(Fl_Menu_* o, void* v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadGradientImage(newfile);
	}
}

//function for switching the view 
void ImpressionistUI::cb_switch_view(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();
	unsigned char* temp = pDoc->m_ucBitmap;
	pDoc->m_ucBitmap = pDoc->m_ucPainting;
	pDoc->m_ucPainting = temp;
	//do not forge to refresh, otherwise the view will refresh only the cursor move in the painting
	whoami(o)->m_origView->refresh();
	whoami(o)->m_paintView->refresh();
};
//the function for undoing painting
void ImpressionistUI::cb_undo_painting(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();
	unsigned char* temp = pDoc->m_ucUndoPainting;
	pDoc->m_ucUndoPainting = pDoc->m_ucPainting;
	pDoc->m_ucPainting = temp;
	whoami(o)->m_paintView->refresh();
	
}

//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) 
{
	fl_message("Impressionist FLTK version for CS4411, Spring 2018");
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;
	pUI->m_nCurrentBrush = type;
	//  Activate the sliders and choice when it is line brush
	if (type == BRUSH_LINES || type == BRUSH_SCATTERED_LINES)
	{
		pUI->m_LineWidthSlider->activate();
		pUI->m_LineAngleSlider->activate();
		pUI->m_StrokeDirectionChoice->activate();
		pUI->m_AnotherGradientButton->activate();
	}
	else {
		pUI->m_LineWidthSlider->deactivate();
		pUI->m_LineAngleSlider->deactivate();
		pUI->m_StrokeDirectionChoice->deactivate();
		pUI->m_AnotherGradientButton->deactivate();
	}

	pDoc->setBrushType(type);
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}


//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSize=int( ((Fl_Slider *)o)->value() ) ;
}

//-----------------------------------------------------------
// Updates the line width to use from the value of the line width  slider
// Called by the UI when the line width slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_lineWidthSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLineWidth = int(((Fl_Slider *)o)->value());
}
//-----------------------------------------------------------
// Updates the line Angle to use from the value of the line Angle slider
// Called by the UI when the line  Angle slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_lineAngleSlides(Fl_Widget* o, void* v)
{
	if (((ImpressionistUI*)(o->user_data()))->m_StrokeDirection == SLIDER)
		((ImpressionistUI*)(o->user_data()))->m_nLineAngle = int(((Fl_Slider *)o)->value());
}

//Callback function for stroke direction choice
void ImpressionistUI::cb_strokeDirectionChoice(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_StrokeDirection = int(((Fl_Choice *)o)->value());
}

//-----------------------------------------------------------
// Updates the Alpha to use from the value of the Alpha slider
// Called by the UI when the Alpha slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_alphaSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nAlpha = float(((Fl_Slider *)o)->value());
}
//set the blending color
void ImpressionistUI::cb_color_selection(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_ncolors[0] = float(((Fl_Color_Chooser *)o)->r());
	((ImpressionistUI*)(o->user_data()))->m_ncolors[1] = float(((Fl_Color_Chooser *)o)->g());
	((ImpressionistUI*)(o->user_data()))->m_ncolors[2] = float(((Fl_Color_Chooser *)o)->b());
};

//Callback functions for auto draw
void ImpressionistUI::cb_autoDrawSpaceSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nAutoDrawSpace = int(((Fl_Slider *)o)->value());
}

void ImpressionistUI::cb_randomSizeButton(Fl_Widget* o, void* v)
{
	ImpressionistUI *pUI = ((ImpressionistUI*)(o->user_data()));

	if (pUI->m_nRandomSize == TRUE) pUI->m_nRandomSize = FALSE;
	else pUI->m_nRandomSize = TRUE;
}

void ImpressionistUI::cb_autoDrawButton(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->autoDraw();
}

//for the dim background
void ImpressionistUI::cb_dim(Fl_Menu_* o, void* v) {
	whoami(o)->m_DimDialog->show();
}
void ImpressionistUI::cb_dimsliders(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nAlphaOfBackground = float(((Fl_Slider *)o)->value());
	((ImpressionistUI*)(o->user_data()))->m_paintView->refresh();

}

void ImpressionistUI::cb_kernel_setting(Fl_Menu_* o, void* v) {
	whoami(o)->m_KernelSettingDialog->show();
}
void ImpressionistUI::cb_kernel_apply(Fl_Widget* o, void* v) {
	ImpressionistUI *pUI = ((ImpressionistUI*)(o->user_data()));
	pUI->m_nKernelWidth = atoi( pUI->m_NumOfColsInput->value());
	pUI->m_nKernelHeight = atoi(pUI->m_NumOfRowsInput->value());
	pUI->m_KernelSettingDialog->hide();

	//if the input is illegal, stop
	if (pUI->m_nKernelWidth % 2 == 0 || pUI->m_nKernelHeight % 2 == 0) {
		fl_alert("we need two odd numbers");
		return;
	}

	//after getting the basic dimension,we need to calcalate the width and height of the window
	int WindowWidth = pUI->m_nKernelWidth * 50;
	int WindowHeight = pUI->m_nKernelHeight * 50;
	//clear the vector
	if (!pUI->m_MatrixInput.empty()) {
		vector<Fl_Float_Input*>::iterator p =   pUI->m_MatrixInput.begin();
		while (p != pUI->m_MatrixInput.end()) {
			p = pUI->m_MatrixInput.erase(p);
		}
		pUI->m_MatrixInput.clear();
	}
	//set up for the input window
	if (pUI->m_KernelInputDialog) delete pUI->m_KernelInputDialog;
	if (pUI->m_Normalized)delete pUI->m_Normalized;
	if (pUI->m_Applykernel)delete pUI->m_Applykernel;
	pUI->m_KernelInputDialog = new Fl_Window(WindowWidth, WindowHeight, "Please input the kernel");
	//set up the input of kernel

	for (int i = 0; i < pUI->m_nKernelHeight * pUI->m_nKernelWidth; ++i) {
		Fl_Float_Input* input = new Fl_Float_Input(5 + (i%pUI->m_nKernelWidth) * 40, 5 + (i / pUI->m_nKernelWidth) * 30, 20, 20, "");
		input->value("0");
		pUI->m_MatrixInput.push_back(input);
	}
	
	pUI->m_Normalized = new Fl_Light_Button(20, WindowHeight - 30, 100, 25, "&Normalize");
	pUI->m_Normalized->user_data((void*)(pUI));
	pUI->m_Normalized->callback(cb_normalize_button);
	pUI->m_Normalized->value(pUI->m_nNormalized);
	
	pUI->m_Applykernel = new Fl_Button(WindowWidth - 100, WindowHeight - 50, 60, 30, "&Apply");
	pUI->m_Applykernel->user_data((void*)(pUI));
	pUI->m_Applykernel->callback(cb_executeKernel);



	pUI->m_KernelInputDialog->end();
	pUI->m_KernelInputDialog->show();
};
void ImpressionistUI::cb_normalize_button(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nNormalized = !((ImpressionistUI*)(o->user_data()))->m_nNormalized;
}

void ImpressionistUI::cb_executeKernel(Fl_Widget* o, void* v) {
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	pDoc->applyKernel();
	
}


void ImpressionistUI::cb_anotherGradientButton(Fl_Widget* o, void* v)
{
	ImpressionistUI *pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc * pDoc = pUI->getDocument();
	if (pDoc->m_ucGradientImage == NULL || pUI->getStrokeDirection() != GRADIENT)
	{
		((Fl_Button*)o)->clear();
		return;
	}

	if (pUI->m_nAnotherGradient == true) pUI->m_nAnotherGradient = false;
	else pUI->m_nAnotherGradient = true;

}


void ImpressionistUI::cb_edge_threshold(Fl_Widget* o, void * v) {
	((ImpressionistUI*)(o->user_data()))->m_nEgdeThreshold = int(((Fl_Slider *)o)->value());

};
void ImpressionistUI::cb_paint_edge(Fl_Widget* o, void * v) {
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	pDoc->drawEdge();
};

//------------------------------
//some new functions wothout implementation 
//TODO:


void ImpressionistUI::cb_paintly(Fl_Widget* o, void* v) {};
void ImpressionistUI::cb_load_edge_image(Fl_Widget* o, void* v) {};


void ImpressionistUI::cb_original__image(Fl_Widget* o, void* v) {};
void ImpressionistUI::cb_edge_image(Fl_Widget* o, void* v) {};
void ImpressionistUI::cb_another_image(Fl_Widget* o, void* v) {};

void ImpressionistUI::cb_faster(Fl_Widget* o, void* v) {};
void ImpressionistUI::cb_safer(Fl_Widget* o, void* v) {};

//------------------------------




//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument()
{
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
	m_origView->size(w,h);
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc)
{
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

//------------------------------------------------
// Return the brush size
//------------------------------------------------
int ImpressionistUI::getSize()
{
	return m_nSize;
}

//-------------------------------------------------
// Set the brush size
//-------------------------------------------------
void ImpressionistUI::setSize( int size )
{
	m_nSize=size;

	if (size<=40&&m_paintView->isAutoDraw==false) //!!!!!!!Remeber to check/delete this if there is a bug
		m_BrushSizeSlider->value(m_nSize);
}
//------------------------------------------------
// Return the line width
//------------------------------------------------
int ImpressionistUI::getLineWidth()
{
	return m_nLineWidth;
}

//-------------------------------------------------
// Set the line width
//-------------------------------------------------
void ImpressionistUI::setLineWidth(int width)
{
	m_nLineWidth = width;

	if (width <= 40)
		m_LineWidthSlider->value(m_nLineWidth);
}



//------------------------------------------------
// Return the line angle
//------------------------------------------------
int ImpressionistUI::getLineAngle()
{
	return m_nLineAngle;
}

//-------------------------------------------------
// Set the line angle
//-------------------------------------------------
void ImpressionistUI::setLineAngle(int angle)
{
	m_nLineAngle = angle;

	if (m_StrokeDirection == SLIDER&&(m_nCurrentBrush==BRUSH_LINES||m_nCurrentBrush==BRUSH_SCATTERED_LINES))
		if (angle <= 359)
			m_LineAngleSlider->value(m_nLineAngle);
}

//Get the type of stroke direction
int ImpressionistUI::getStrokeDirection()
{
	return m_StrokeDirection;
}

//Set the type of stroke direction
void ImpressionistUI::setStrokeDirection(int direction)
{
	m_StrokeDirection = direction;
}
//------------------------------------------------
// Return the line angle
//------------------------------------------------
float ImpressionistUI::getAlpha()
{

	
	return m_nAlpha;
}

//-------------------------------------------------
// Set the line angle
//-------------------------------------------------
void ImpressionistUI::setAlpha(float alpha)
{
	m_nAlpha = alpha;

	if (alpha <= 1.00)
		m_AlphaSlider->value(m_nAlpha);
}

void ImpressionistUI::setMarkerPoint(Point p) {
	m_origView->setMarkerPoint(p);
}
//for color selection 
float*ImpressionistUI::getColor() {
	return 	m_ncolors;
};
void  ImpressionistUI::setColor(float r, float g, float b) {
	m_ncolors[0] = r;
	m_ncolors[1] = g;
	m_ncolors[2] = b;
}

//for auto draw
int ImpressionistUI::getAutoDrawSpace()
{
	return m_nAutoDrawSpace;
}

void ImpressionistUI::setAutoDrawSpace(int space)
{
	m_nAutoDrawSpace = space;

	if (space <= 16)
		m_AutoDrawSpaceSlider->value(m_nAutoDrawSpace);
}

bool ImpressionistUI::getRandomSize()
{
	return m_nRandomSize;
}

void ImpressionistUI::setRandomSize(bool isRandom)
{
	m_nRandomSize = isRandom;

	m_RandomSizeButton->value(m_nRandomSize);
}

//for another gradient
bool ImpressionistUI::getAnotherGradient()
{
	return m_nAnotherGradient;
}

void ImpressionistUI::setAnotherGradient(bool gradient)
{
	m_nAnotherGradient = gradient;

	m_AnotherGradientButton->value(m_nAnotherGradient);
}


// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes }, 
		{ "&Clear Canvas", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas, 0, FL_MENU_DIVIDER },
		//add some new button here 
		{ "&Colors",	FL_ALT + 'k', (Fl_Callback *)ImpressionistUI::cb_colors },
		{ "&Paintly",	FL_ALT + 'p', (Fl_Callback *)ImpressionistUI::cb_paintly, 0, FL_MENU_DIVIDER},

		{ "Set Mural Image",	FL_ALT + 'm', (Fl_Callback *)ImpressionistUI::cb_set_mural_image },
		{ "Load Edge Image...",	FL_ALT + 'e', (Fl_Callback *)ImpressionistUI::cb_load_edge_image },
		{ "Load Gradient Image...", FL_ALT+'g', (Fl_Callback *)ImpressionistUI::cb_load_gradient_image},
		{ "Load Another Image...",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_load_another_image, 0, FL_MENU_DIVIDER },


		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
		{ 0 },
	{ "&Display",		0, 0, 0, FL_SUBMENU },
		{ "&Kelnel setting",			FL_ALT + 'k', (Fl_Callback *)ImpressionistUI::cb_kernel_setting},

		{ "&Dim Background",			FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_dim },

		{ "&Undo",			FL_ALT + 'd', (Fl_Callback *)ImpressionistUI::cb_undo_painting },
		{ "&Switch views",			FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_switch_view },
		{ "&Original Image",			FL_ALT + 'o', (Fl_Callback *)ImpressionistUI::cb_original__image },
		{ "&Edge Image",			FL_ALT + 'e', (Fl_Callback *)ImpressionistUI::cb_edge_image },
		{ "&Another Image...",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_another_image, 0, FL_MENU_DIVIDER },
		{0},

	{ "&Options",		0, 0, 0, FL_SUBMENU },
		{ "&Faster",			FL_ALT + 'f', (Fl_Callback *)ImpressionistUI::cb_faster },
		{ "&Safer",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_safer, 0, FL_MENU_DIVIDER },
		{0},

		//end here
	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
		{ 0 },

	{ 0 }
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE+1] = {
  {"Points",			FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS},
  {"Lines",				FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES},
  {"Circles",			FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
  {"Scattered Points",	FL_ALT+'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
  {"Scattered Lines",	FL_ALT+'m', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
  {"Scattered Circles",	FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES},
  {"Blur",				FL_ALT+'b', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_BLUR },
  { "Sharpenning",		FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SHARPENING },
  { "Warp",		FL_ALT + 'w', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_WARP },

  { "Eraser",		FL_ALT + 'e', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_ERASER },



  {0}
};


//  Stroke direction choice menu definition
Fl_Menu_Item ImpressionistUI::strokeDirectionMenu[3 + 1] = {
	{ "Slider/Right Mouse", FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_strokeDirectionChoice, (void *)SLIDER },
	{ "Gradient", FL_ALT + 'g', (Fl_Callback *)ImpressionistUI::cb_strokeDirectionChoice, (void *)GRADIENT },
	{ "Brush Direction", FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_strokeDirectionChoice, (void *)BRUSH_DIRECTION },
	{ 0 }
};


//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "Impressionist");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
		m_menubar->menu(menuitems);

		// Create a group that will hold two sub windows inside the main
		// window
		Fl_Group* group = new Fl_Group(0, 25, 600, 275);

			// install paint view window
			m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
			m_paintView->box(FL_DOWN_FRAME);
			m_paintView->m_pUI = this; // store the UI pointer in the paint to build a bridge between the original view and paint view
			
			// install original view window
			m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
			m_origView->box(FL_DOWN_FRAME);
			m_origView->deactivate();

		group->end();
		Fl_Group::current()->resizable(group);
    m_mainWindow->end();

	// init values

	m_nSize = 10;
	m_nLineWidth = 1;
	m_nLineAngle = 0;
	m_nAlpha = 1.00;
	m_ncolors[0] = 1.0;
	m_ncolors[1] = 1.0;
	m_ncolors[2] = 1.0;
	m_StrokeDirection = SLIDER;
	m_nAutoDrawSpace = 1;
	m_nRandomSize = true;
	m_nAlphaOfBackground = 0.0;
	m_nInDim = FALSE;
	m_nNormalized = FALSE;
	m_KernelInputDialog = NULL;
	m_Normalized = NULL;
	m_Applykernel = NULL;

	m_nAnotherGradient = false;
	m_nCurrentBrush = BRUSH_POINTS;


	m_nEgdeThreshold = 50;

	// brush dialog definition
	m_brushDialog = new Fl_Window(400, 325, "Brush Dialog");
		// Add a brush type choice to the dialog
		m_BrushTypeChoice = new Fl_Choice(50,10,150,25,"&Brush");
		m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushTypeChoice->menu(brushTypeMenu);
		m_BrushTypeChoice->callback(cb_brushChoice);

		//Add the stroke direction choice to the dialog
		m_StrokeDirectionChoice = new Fl_Choice(125, 45, 150, 25, "&Stroke Direction");
		m_StrokeDirectionChoice->user_data((void*)(this));
		m_StrokeDirectionChoice->menu(strokeDirectionMenu);
		m_StrokeDirectionChoice->callback(cb_strokeDirectionChoice);
		m_StrokeDirectionChoice->deactivate();

		m_ClearCanvasButton = new Fl_Button(240,10,150,25,"&Clear Canvas");
		m_ClearCanvasButton->user_data((void*)(this));
		m_ClearCanvasButton->callback(cb_clear_canvas_button);


		// Add brush size slider to the dialog 
		m_BrushSizeSlider = new Fl_Value_Slider(10, 80, 300, 20, "Size");
		m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushSizeSlider->labelfont(FL_COURIER);
        m_BrushSizeSlider->labelsize(12);
		m_BrushSizeSlider->minimum(1);
		m_BrushSizeSlider->maximum(40);
		m_BrushSizeSlider->step(1);
		m_BrushSizeSlider->value(m_nSize);
		m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_BrushSizeSlider->callback(cb_sizeSlides);

		// Add line width and angle slider to dialog
		m_LineWidthSlider = new Fl_Value_Slider(10, 110, 300, 20, "Line Width");
		m_LineWidthSlider->user_data((void*)(this));
		m_LineWidthSlider->type(FL_HOR_NICE_SLIDER);
		m_LineWidthSlider->labelfont(FL_COURIER);
		m_LineWidthSlider->labelsize(12);
		m_LineWidthSlider->minimum(1);
		m_LineWidthSlider->maximum(40);
		m_LineWidthSlider->step(1);
		m_LineWidthSlider->value(m_nLineWidth);
		m_LineWidthSlider->align(FL_ALIGN_RIGHT);
		m_LineWidthSlider->callback(cb_lineWidthSlides);
		m_LineWidthSlider->deactivate();

		m_LineAngleSlider = new Fl_Value_Slider(10, 140, 300, 20, "Line Angle");
		m_LineAngleSlider->user_data((void*)(this));
		m_LineAngleSlider->type(FL_HOR_NICE_SLIDER);
		m_LineAngleSlider->labelfont(FL_COURIER);
		m_LineAngleSlider->labelsize(12);
		m_LineAngleSlider->minimum(0);
		m_LineAngleSlider->maximum(359);
		m_LineAngleSlider->step(1);
		m_LineAngleSlider->value(m_nLineAngle);
		m_LineAngleSlider->align(FL_ALIGN_RIGHT);
		m_LineAngleSlider->callback(cb_lineAngleSlides);
		m_LineAngleSlider->deactivate();
		
		//add one slider for alpha
		m_AlphaSlider = new Fl_Value_Slider(10, 170, 300, 20, "Alpha");
		m_AlphaSlider->user_data((void*)(this));
		m_AlphaSlider->type(FL_HOR_NICE_SLIDER);
		m_AlphaSlider->labelfont(FL_COURIER);
		m_AlphaSlider->labelsize(12);
		m_AlphaSlider->minimum(0.00);
		m_AlphaSlider->maximum(1.00);
		m_AlphaSlider->step(0.01);
		m_AlphaSlider->value(m_nAlpha);
		m_AlphaSlider->align(FL_ALIGN_RIGHT);
		m_AlphaSlider->callback(cb_alphaSlides);

		//add one slider for auto draw space
		m_AlphaSlider = new Fl_Value_Slider(10, 200, 140, 20, "Spacing");
		m_AlphaSlider->user_data((void*)(this));
		m_AlphaSlider->type(FL_HOR_NICE_SLIDER);
		m_AlphaSlider->labelfont(FL_COURIER);
		m_AlphaSlider->labelsize(12);
		m_AlphaSlider->minimum(1);
		m_AlphaSlider->maximum(16);
		m_AlphaSlider->step(1);
		m_AlphaSlider->value(m_nAutoDrawSpace);
		m_AlphaSlider->align(FL_ALIGN_RIGHT);
		m_AlphaSlider->callback(cb_autoDrawSpaceSlides);

		//add a lighting button for random size
		m_RandomSizeButton = new Fl_Light_Button(210, 200, 90, 20, "&Size Rand.");
		m_RandomSizeButton->user_data((void*)(this));   // record self to be used by static callback functions
		m_RandomSizeButton->callback(cb_randomSizeButton);
		m_RandomSizeButton->set();

		//add a button to auto draw
		m_AutoDrawButton = new Fl_Button(310, 200, 50, 20, "&Paint");
		m_AutoDrawButton->user_data((void*)(this));   // record self to be used by static callback functions
		m_AutoDrawButton->callback(cb_autoDrawButton);

		
		//add a light button for another gradient
		m_AnotherGradientButton = new Fl_Light_Button(10, 260, 100, 20, "Another Gra.");
		m_AnotherGradientButton->user_data((void*)(this));
		m_AnotherGradientButton->callback(cb_anotherGradientButton);
		m_AnotherGradientButton->deactivate();


		////add a slider for edge threshold
		m_ThresholdSlider = new Fl_Value_Slider(10, 230, 200, 20, "Threshold");
		m_ThresholdSlider ->user_data((void*)(this));
		m_ThresholdSlider ->type(FL_HOR_NICE_SLIDER);
		m_ThresholdSlider ->labelfont(FL_COURIER);
		m_ThresholdSlider ->labelsize(12);
		m_ThresholdSlider ->minimum(1);
		m_ThresholdSlider ->maximum(500);
		m_ThresholdSlider ->step(1);
		m_ThresholdSlider ->value(m_nEgdeThreshold);
		m_ThresholdSlider ->align(FL_ALIGN_RIGHT);
		m_ThresholdSlider ->callback(cb_edge_threshold);

		////add a button 
		m_AutoDrawButton = new Fl_Button(310, 230, 50, 20, "&Edge Paint");
		m_AutoDrawButton->user_data((void*)(this));   // record self to be used by static callback functions
		m_AutoDrawButton->callback(cb_paint_edge);
    m_brushDialog->end();


	m_colorSelectionDialog = new Fl_Window(200, 200, "Color Selection");

	m_colorChooser = new Fl_Color_Chooser(10, 20, 190,180, "Color Selection");
	m_colorChooser->user_data((void*)(this));
	m_colorChooser->callback(cb_color_selection);
	m_colorChooser->rgb(1.0, 1.0, 1.0);

	m_colorSelectionDialog->end();

	m_DimDialog = new Fl_Window(200, 200, "Dim Alpha Chooser");
		m_DimSlider = new Fl_Value_Slider(10, 10, 150, 20, "Alpha");
		m_DimSlider->user_data((void*)(this));
		m_DimSlider->type(FL_HOR_NICE_SLIDER);
		m_DimSlider->labelfont(FL_COURIER);
		m_DimSlider->labelsize(12);
		m_DimSlider->minimum(0.00);
		m_DimSlider->maximum(1.00);
		m_DimSlider->step(0.01);
		m_DimSlider->value(m_nAlphaOfBackground);
		m_DimSlider->align(FL_ALIGN_RIGHT);
		m_DimSlider->callback(cb_dimsliders);


	m_DimDialog->end();

	m_KernelSettingDialog = new Fl_Window(250, 100, "Kernel Setting Dialog");
		m_NumOfRowsInput = new Fl_Int_Input(60, 10, 40, 20, "Height:");
		m_NumOfRowsInput->labelfont(FL_COURIER);
		m_NumOfRowsInput->labelsize(12);
		m_NumOfRowsInput->value("3");

		m_NumOfColsInput = new Fl_Int_Input(160, 10, 40, 20, "Width:");
		m_NumOfColsInput->labelfont(FL_COURIER);
		m_NumOfColsInput->labelsize(12);
		m_NumOfColsInput->value("3");
		
		m_ConfirmButton = new Fl_Button(130, 40, 70, 20, "&Apply");
		m_ConfirmButton->user_data((void*)(this));
		m_ConfirmButton->callback(cb_kernel_apply);




	m_KernelSettingDialog->end();
}
