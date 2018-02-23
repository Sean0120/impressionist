//
// impressionistUI.h
//
// The header file for the UI part
//

#ifndef ImpressionistUI_h
#define ImpressionistUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_file_chooser.H>		// FLTK file chooser
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL\Fl_Color_Chooser.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Int_Input.H>
#include <FL\Fl_Float_Input.H>
#include "Impressionist.h"
#include "OriginalView.h"
#include "PaintView.h"
#include<vector>
#include<algorithm>
#include "ImpBrush.h"
using namespace std;

class ImpressionistUI {
public:
	ImpressionistUI();

	// The FLTK widgets
	Fl_Window*			m_mainWindow;
	Fl_Menu_Bar*		m_menubar;
								
	PaintView*			m_paintView;
	OriginalView*		m_origView;

	// for brush dialog
	Fl_Window*			m_brushDialog;
	Fl_Choice*			m_BrushTypeChoice;

	Fl_Slider*			m_BrushSizeSlider;
	Fl_Button*          m_ClearCanvasButton;
	Fl_Slider*			m_LineWidthSlider;
	Fl_Slider*			m_LineAngleSlider;
	Fl_Slider*			m_AlphaSlider;
	Fl_Choice*          m_StrokeDirectionChoice;    //new choice
	//for color selection dialog
	Fl_Window*			m_colorSelectionDialog;
	Fl_Color_Chooser*   m_colorChooser;
	//for dim background 
	Fl_Window*          m_DimDialog;
	Fl_Slider*			m_DimSlider;
	Fl_Slider*			m_AutoDrawSpaceSlider;	//for auto draw
	Fl_Light_Button*	m_RandomSizeButton;
	Fl_Button*			m_AutoDrawButton;
	//for edge draw
	Fl_Slider*			m_ThresholdSlider;
	Fl_Button*			m_EdgeButton;
	//the setting of kernel dialog
	Fl_Window*			m_KernelSettingDialog;
	Fl_Int_Input*		m_NumOfRowsInput;
	Fl_Int_Input*		m_NumOfColsInput;
	Fl_Button*			m_ConfirmButton;
	//the window for kernel inout
	Fl_Window*			m_KernelInputDialog;
	Fl_Button*			m_Normalized;
	Fl_Button*			m_Applykernel;
	vector<Fl_Float_Input*>  m_MatrixInput;
	//the width and height of Kernel
	int		m_nKernelWidth;
	int		m_nKernelHeight;
	bool	m_nNormalized;
	
	// Member functions
	void				setDocument(ImpressionistDoc* doc);
	ImpressionistDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);

	// Interface to get attribute

	int					getSize();
	void				setSize(int size);

	int					m_nEgdeThreshold;
	
	//for auto draw
	int					getAutoDrawSpace();
	void				setAutoDrawSpace(int space);
	bool				getRandomSize();
	void				setRandomSize(bool isRandom);


	//for line width 
	int					getLineWidth();
	void				setLineWidth(int width);

	//for line angle
	int					getLineAngle();
	void				setLineAngle(int angle);
	//for alpha 
	float				getAlpha();
	void				setAlpha(float alpha);
	//for the marker in the original vew
	void				setMarkerPoint(Point p);
	//for color selection 
	float*				getColor();
	void				setColor(float r, float g, float b);

	//for stroke direction
	int                 getStrokeDirection();
	void                setStrokeDirection(int direction);

	float				m_nAlphaOfBackground;// i am too lazy to build a get function, so i make it public
	bool				m_nInDim;//indicate whether is in dim background mode
private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

	// All attributes here
	int		m_nSize;
	int		m_nLineWidth;
	int		m_nLineAngle;
	float   m_nAlpha;
	float   m_ncolors[3];
	int     m_StrokeDirection;  //type of direction
	int		m_nAutoDrawSpace;	//Auto draw space
	bool	m_nRandomSize;

	// Static class members
	static Fl_Menu_Item		menuitems[];
	static Fl_Menu_Item		brushTypeMenu[NUM_BRUSH_TYPE+1];
	static Fl_Menu_Item     strokeDirectionMenu[3 + 1]; //menu items of stroke direction choice

	static ImpressionistUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 
	// static
	static void	cb_load_image(Fl_Menu_* o, void* v);
	static void	cb_save_image(Fl_Menu_* o, void* v);
	static void	cb_brushes(Fl_Menu_* o, void* v);
	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void	cb_load_another_image(Fl_Menu_* o, void* v);
	static void cb_set_mural_image(Fl_Menu_* o, void* v);
	static void	cb_exit(Fl_Menu_* o, void* v);
	static void	cb_about(Fl_Menu_* o, void* v);
	static void	cb_brushChoice(Fl_Widget* o, void* v);
	static void	cb_clear_canvas_button(Fl_Widget* o, void* v);

	static void	cb_sizeSlides(Fl_Widget* o, void* v);
	static void cb_lineWidthSlides(Fl_Widget * o, void * v);
	static void cb_lineAngleSlides(Fl_Widget * o, void * v);
	static void cb_alphaSlides(Fl_Widget * o, void * v);
	static void cb_strokeDirectionChoice(Fl_Widget* o, void* v);//new callback for new choice

	static void cb_autoDrawSpaceSlides(Fl_Widget* o, void* v);	//Callback functions for auto draw
	static void cb_randomSizeButton(Fl_Widget* o, void* v);
	static void cb_autoDrawButton(Fl_Widget* o, void* v);
	static void cb_dim(Fl_Menu_* o, void* v);
	static void cb_dimsliders(Fl_Widget* o, void* v);
	static void	cb_colors(Fl_Menu_* o, void* v);
	static void	cb_color_selection(Fl_Widget* o, void* v);
	static void cb_undo_painting(Fl_Menu_* o, void* v);
	static void cb_switch_view(Fl_Menu_ * o, void * v);
	//add some new helper function here for "file" in menu bar
	// the prototype may be wrong
	static void	cb_paintly(Fl_Widget* o, void* v);
	static void	cb_load_edge_image(Fl_Widget* o, void* v);
	//add some new helper function here for "Display" in menu bar
	static void	cb_original__image(Fl_Widget* o, void* v);
	static void	cb_edge_image(Fl_Widget* o, void* v);
	static void	cb_another_image(Fl_Widget* o, void* v);
	//add spme new helper functopn here for "Options" in menu bar
	static void	cb_faster(Fl_Widget* o, void* v);
	static void	cb_safer(Fl_Widget* o, void* v);
	//the function of kernel setting
	static void cb_kernel_setting(Fl_Menu_* o, void* v);
	static void cb_kernel_apply(Fl_Widget* o, void* v);
	static void cb_normalize_button(Fl_Widget* o, void* v);
	static void cb_executeKernel(Fl_Widget* o, void* v);
	//edge detector
	static void cb_edge_threshold(Fl_Widget* o, void * v);
	static void cb_paint_edge(Fl_Widget* o, void * v);
};

#endif
