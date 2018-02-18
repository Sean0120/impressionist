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
private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

	// All attributes here
	int		m_nSize;
	int		m_nLineWidth;
	int		m_nLineAngle;
	float   m_nAlpha;
	// Static class members
	static Fl_Menu_Item		menuitems[];
	static Fl_Menu_Item		brushTypeMenu[NUM_BRUSH_TYPE+1];

	static ImpressionistUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 
	// static
	static void	cb_load_image(Fl_Menu_* o, void* v);
	static void	cb_save_image(Fl_Menu_* o, void* v);
	static void	cb_brushes(Fl_Menu_* o, void* v);
	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void	cb_exit(Fl_Menu_* o, void* v);
	static void	cb_about(Fl_Menu_* o, void* v);
	static void	cb_brushChoice(Fl_Widget* o, void* v);
	static void	cb_clear_canvas_button(Fl_Widget* o, void* v);
	static void	cb_sizeSlides(Fl_Widget* o, void* v);
	static void cb_lineWidthSlides(Fl_Widget * o, void * v);
	static void cb_lineAngleSlides(Fl_Widget * o, void * v);
	static void cb_alphaSlides(Fl_Widget * o, void * v);
	//add some new helper function here for "file" in menu bar
	// the prototype may be wrong
	static void cb_switch_view(Fl_Menu_ * o, void * v);
	static void	cb_colors(Fl_Widget* o, void* v);
	static void	cb_paintly(Fl_Widget* o, void* v);
	static void	cb_load_edge_image(Fl_Widget* o, void* v);
	static void	cb_load_another_image(Fl_Widget* o, void* v);
	//add some new helper function here for "Display" in menu bar
	static void	cb_original__image(Fl_Widget* o, void* v);
	static void	cb_edge_image(Fl_Widget* o, void* v);
	static void	cb_another_image(Fl_Widget* o, void* v);
	//add spme new helper functopn here for "Options" in menu bar
	static void	cb_faster(Fl_Widget* o, void* v);
	static void	cb_safer(Fl_Widget* o, void* v);


};

#endif
