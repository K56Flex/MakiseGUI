#ifndef _MAKISE_H_G_EL
#define _MAKISE_H_G_EL 1

typedef struct _MElement MElement;
typedef struct _MPosition MPosition;

#define MState_Disable 0b0000
#define MState_Idle    0b0001
#define MState_Focused 0b0010
#define MState_Pressed 0b0100

#include "makise_gui.h"
#include "makise_gui_container.h"

typedef struct _MPosition
{
    int32_t x; //relative position
    int32_t y; //relative position
    
    int32_t width;
    int32_t height;

    int32_t real_x; //position on the screen
    int32_t real_y; //position on the screen
} MPosition;

typedef struct _MElement
{
    MakiseGUI *gui; //current gui

    uint32_t id; //unique id
    
    MElement *prev; //previous if exists
    MElement *next; //next element if exists
    MContainer *parent; //parent element, if exists

    uint8_t enabled;    //if enabled - methods will be executed
    MPosition position; //relative position of the element

    uint8_t focus_prior; //relative position in focus queu. 0 means focus doesn't required
    
    void* data;
    uint8_t    (*draw    )(MElement* el);
    uint8_t    (*predraw )(MElement* el); //count real position for every element
    uint8_t    (*update  )(MElement* el);
    MInputResultEnum (*input   )(MElement* el, MInputData data);
    MFocusEnum (*focus   )(MElement* el, MFocusEnum act);
    uint8_t    (*free    )(MElement* el);
    
} MElement;

uint8_t m_element_call(MElement* el, uint8_t type);
uint8_t m_element_focus(MElement* el, uint8_t event);
uint8_t m_element_input(MElement* el, uint8_t event, uint32_t i);

typedef struct {
    MakiseGUI *gui;
    MElement el;

    char* text;
    uint32_t bgcolor;
    uint32_t fontcolor;
    uint32_t bordercolor;

    uint8_t state;    
} MButton;
void m_button_create(MButton* b, MContainer *c,
		     int32_t x, int32_t y, uint32_t w, uint32_t h,
		     char* text,
		     uint32_t bgcolor, uint32_t fontcolor, uint32_t bordercolor);



#endif