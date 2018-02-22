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

#include "Impressionist.h"
#include "OriginalView.h"
#include "PaintView.h"

#include "ImpBrush.h"

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

	Fl_Slider*			m_AutoDrawSpaceSlider;	//for auto draw
	Fl_Light_Button*	m_RandomSizeButton;
	Fl_Button*			m_AutoDrawButton;

	//for color selection dialog
	Fl_Window*			m_colorSelectionDialog;
	Fl_Color_Chooser*   m_colorChooser;

	// Member functions
	void				setDocument(ImpressionistDoc* doc);
	ImpressionistDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);

	// Interface to get attribute

	int					getSize();
	void				setSize(int size);

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

	//for auto draw
	int					getAutoDrawSpace();
	void				setAutoDrawSpace(int space);
	bool				getRandomSize();
	void				setRandomSize(bool isRandom);


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

	//add some new helper function here for "file" in menu bar
	// the prototype may be wrong
	static void	cb_colors(Fl_Menu_* o, void* v);
	static void	cb_color_selection(Fl_Widget* o, void* v);
	static void	cb_paintly(Fl_Widget* o, void* v);
	static void	cb_load_edge_image(Fl_Widget* o, void* v);
	//add some new helper function here for "Display" in menu bar
	static void cb_undo_painting(Fl_Menu_* o, void* v);
	static void cb_switch_view(Fl_Menu_ * o, void * v);
	static void	cb_original__image(Fl_Widget* o, void* v);
	static void	cb_edge_image(Fl_Widget* o, void* v);
	static void	cb_another_image(Fl_Widget* o, void* v);
	//add spme new helper functopn here for "Options" in menu bar
	static void	cb_faster(Fl_Widget* o, void* v);
	static void	cb_safer(Fl_Widget* o, void* v);


};

#endif
