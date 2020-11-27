#include "FEHLCD.h"

typedef FEHLCD::FEHLCDColor colorT;
typedef char* stringT;

colorT defaultFill = LCD.Black;
colorT defaultLine = LCD.White;

/*
Proteus UI Engine 
Created 11/25/2020
Last Modified: 11/26/2020

With this game being heavily UI-dependent and the FEHLCD library, being 
somewhat limited, I decided to try implementing a cheap knockoff of the 
JavaScript Document Object Model to make it easier for us to create graphics

Similar to HTML, elements are stored in a tree structure with parents and
children. Elements can be added or removed to the tree, causing them to 
appear or disappear when the screen is cleared and a recursive render function
is called from a root element. 

Composite elements like menu panels may comprise a subtree with multiple layers
of children representing things like text, buttons, or icons. The entire panel
can easily be placed on or taken off the screen with a single function call, or 
alternatively individual child elements can be modified while everything else is
left where it is.

The generic element (UIElement class) can be rendered, respond to clicks, be 
assigned to or removed from a parent element, have child elements assigned to or 
removed from it, and be assigned an x and y position

Objects can be placed on the screen using the following classes derived from the 
UIElement base class:

    - RectangleElement: Renders a rectangle of a specified width, height, border
      color, and fill color, all of which can be changed later

    - CircleElement: Renders a circle of a specified radius, border color, and 
      fill color, all of which can be changed later

    - StringElement: Writes a specified text string with a specified font color, 
      with the color and string content both being changeable.

    - ValueElement: Similar to StringElement, except instead of a string it has a
      function pointer with an int return type and upon rendering will write 
      whatever value is returned by that function. This will be useful for 
      displaying game statistics like cash and inventory as the shown value will
      be automatically updated when the elements are rerendered

    - SpriteElement: Can be assigned a 2D array of color enums and will draw 
      pixels on the screen corresponding to those colors

We'll likely be depending a lot on RectangleElement, TextElement, and 
ValueElement to generate the UI. I decided to make the CircleElement and 
SpriteElement classes just in case we needed them for extra decoration.

*/

/*
UIElement Class
Written By Thomas Li
Created 11/25/2020
Last Modified 11/27/2020

This is the base class that all elements are derived from, containing methods
for rendering, touch detection, parent/child handling, and positioning that are 
common to all element types. 


void UIElement::render()
Calls the rendering procedure for the element itself, and then renders each of 
the elements child subtrees

bool UIElement::handleClick(int x, int y)
Determines if the element has been clicked given x and y as the coordinates of
the click. If the element has a click handler enabled and is determined to have
been clicked on, then click handler is called and the function returns true.
This function calls itself for each of the of the element's child subtrees before 
applying to the element itself. If any call returns true, the callback stops in 
order to save time and to ensure that only one click handler is executed at once.


The public render and handleClick methods are recursive and apply to the entire
element subtree. If all elements intended to be shown on the screen are children
of a single root element, then these methods will only need to be called once in 
each iteration of the main program loop in order to apply to the entire screen.

The procedures for rendering the element itself or determining if the element 
itself has been clicked are handled by the protected virtual renderSelf and 
isClicked methods, which are intended to be overwritten with different functions 
for each specific element type. 

Elements are polled for click detection in the opposite order that they get 
rendered in given that objects drawn last will show up on top. One goal of this
engine is to make layering easy to handle.


void UIElement::setClickHandler(void (*func)())
Stores func as the element's click handler so that it will be called if the 
element is clicked on, marks the element's click detection as enabled.

void UIElement::disableClickHandler()
Mark the element's click detection as disabled

void UIElement::enableClickHandler()
Mark the element's click detection as enabled without changing the click handler


The setClickHandler method is probably the most important part of the interface 
as it is what allows the objects on the screen to actually do anything when 
interacted with. The function passed into it has to take no arguments of void
return type.

C++ fortunately has anonymous functions (syntax: [] { function body goes here })
so we don't have to separately define every procedure that we want to attach to 
any button.

Disabling click detection makes it so that the handleClick function won't check
if that particular element has been clicked on. The original intention is putting
this in was so that child elements with no click handler won't interfere with 
the click detection of any parent elements that they're rendered over, but that
situation probably won't occur too often now that I think of it. Might as well
leave this here just in case.


void UIElement::addChild(UIElement* childPtr)
Adds childPtr to the element's child subtree, marks this element as the child's
parent

void UIElement::removeChild(UIElement* childPtr)
Removes childPtr from the element's child subtree and sets the child's parent 
pointer to NULL if childPtr is present in the subtree

void UIElement::addSelf(UIElement* parentPtr)
Adds this element to parentPtr's child subtree, marks parentPtr as this element's
parent

void UIElement::removeSelf()
Removes this element from its parent's child subtree and sets its own parent 
pointer to NULL


The internal mechanism for managing the element tree is handled by a linked list 
class nested in the UIElement class, leaving these four methods as all that's 
needed from the public perspective 


int getX()
Returns the internal x-position of the element

int getY()
Returns the internal y-position of the element

void setPos(int x, int y)
Sets the internal x-position of the element to x and the internal y-position of the
element to y


All elements have internal coordinates dictating where the element will be drawn, 
so the position members are included in the generic element class even though they
don't get utilized in it


void freeMemory()
Frees the memory of all child elements in the element subtree, and then frees the 
memory of the element itself


Depending on how we go about programming this game, some elements might be stored
as global objects that get swapped in and out of the main tree as needed, while 
others might get initialized dynamically. In the case of the latter, the freeMemory
method is prevent potential memory leaks. 

This method frees the memory allocated for the entire element subtree, so if only 
the parent element needs to be freed while the child elements are left as-is, then
the built-in free() function should be used

*/
class UIElement {
    public:
    // public interface - see above for details
    void render();
    bool handleClick(int x, int y);

    void setClickHandler(void (*func)());
    void disableClickHandler();
    void enableClickHandler();

    void addChild(UIElement* childPtr);
    void removeChild(UIElement* childPtr);

    void addSelf(UIElement* parentPtr);
    void removeSelf();

    int getX();
    int getY();
    void setPos(int x, int y);

    void freeMemory();

    protected:
    // each element type has a different rendering procedure consisting
    // of one or more FEHLCD library function calls
    // this function gets called by the public render function, which
    // also renders all of the elements children
    // for the generic UI element class, this function does nothing
    virtual void renderSelf();

    // if the element doesn't do anything when clicked, as is default, 
    // then this member is set to false to both save time in the click
    // detection procedure and to make sure that the element doesn't 
    // interfere with the click detection of any elements that it's 
    // layered over (e.g. a text element serving as a button label)
    // if the element is assigned a click handler, this member is 
    // automatically set to true
    bool listenForClick = false;

    // elements have a function to determine whether they've been 
    // touched given an x and y coordinate for the touch
    // this function gets called by the public handleClick function
    // which also checks if any of the element's children are clicked
    virtual bool isClicked(int x, int y);

    // pointer to the function to be called when the element is clicked
    // by default, this points to an empty function
    void (*clickHandler)() = [] {};

    // keep track of the element's position on the screen
    // all derived classes will need this for rendering
    int xPos, yPos;

    // keep track of parent element - this pointer gets assigned
    // in the add and remove functions
    UIElement* parent = nullptr;
    
    // singly-linked list provides internal mechanism for
    // managing child elements
    class ElementList {
        public:
        void addElement(UIElement* element);
        bool removeElement(UIElement* element);

        void renderElements();
        void handleClick(int x, int y);

        void freeElements();

        private:
        struct ElementListNode {
            UIElement* elementPtr = nullptr;
            ElementListNode* next = nullptr;
        };

        ElementListNode* head = nullptr;
        ElementListNode* tail = nullptr;
    };

    ElementList* children = new ElementList();
};

/*
PolygonElement class
Written By Thomas Li
Created 11/25/2020 
Last Modified 11/25/2020

This class inherits from UIElement and adds members for tracking
the fill color and line color of the element, attributes which are
used for both rectangles and circles. This class is not intended 
to be used on its own but rather to serve as a base for 
RectangleElement and CircleElement
*/
class PolygonElement : UIElement {
    public:
    void setFillColor(colorT color);
    void setLineColor(colorT color);

    protected:
    colorT fillColor = defaultFill, lineColor = defaultLine;
};

/*
RectangleElement class
Written By Thomas Li
Created 11/25/2020 
Last Modified 11/25/2020

This class inherits from PolygonElement, adds members for tracking
width and height along with constructors that along width, height, 
and color to be specified, overrides the renderSelf function to 
draw a rectangle at the stored position with the stored dimensions 
and color, and overrides the isClicked function to return true if
the location of the click is within the bounds of the rectangle as
determined by the position and dimensions
*/
class RectangleElement : PolygonElement {
    public:
    RectangleElement(int x, int y, int w, int h);
    RectangleElement(int x, int y, int w, int h, colorT fill, colorT line);
    
    void setDimensions(int w, int h);
    int getWidth();
    int getHeight();

    private:
    int width, height;
};

/*
CircleElement class
Written By Thomas Li
Created 11/25/2020 
Last Modified 11/25/2020

This class inherits from PolygonElement, adds members for tracking
radius along with a constructor which can be used to specify radius
and color, and overrides the renderSelf function to draw a circle at 
the stored position with the stored dimensions and color

An override for the isClicked function hasn't been implemented since
we probably aren't going to use any circular buttons
*/
class CircleElement : PolygonElement {
    public:
    CircleElement(int x, int y, int r);
    CircleElement(int x, int y, int r, colorT fill, colorT line);

    void setRadius(int r);
    void getRadius();

    private:
    int radius;
};

/*
TextElement class
Written By Thomas Li
Created 11/27/2020
Modified 11/27/2020

This class inherits from UIElement, serves as a base for all element 
subclasses that involve writing text to the screen, which in this case 
includes StringElement and ValueElement, and adds attributes common to 
all such classes, which in this case includes the font color
*/
class TextElement : UIElement {
    public:
    void setFontColor(colorT c);

    protected:
    colorT fontColor;
};

/*
StringElement class
Written By Thomas Li
Created 11/27/2020 
Last Modified 11/27/2020

This class inherits from TextElement, adds members for storing a text string
along with a constructor which can be used to specify the string and color, 
and overrides the renderSelf function to write the text string to
the screen at the stored position with the stored font color

An isClicked override hasn't been implemented for this subclass. Touch 
detection for buttons will most likely be handled by the rectangle 
portion of the button rather than the text portion so I figured it 
wouldn't be worth the effort
*/
class StringElement : TextElement {
    public:
    StringElement(int x, int y, stringT s);
    StringElement(int x, int y, stringT s, colorT c);

    void setString(stringT s);
    stringT getString();

    private:
    stringT textString;
};

/*
ValueElement class
Written By Thomas Li
Created 11/27/2020 
Last Modified 11/27/2020

This class inherits from UIElement, adds members for storing the pointer
to the value function along with a constructor that can be used to assign
the function pointer and font color, and overrides the renderSelf function
to write the return value of the value function to the screen at the 
stored position with the stored font color 
*/
class ValueElement : TextElement {
    public:
    ValueElement(int x, int y, int (*func)());
    ValueElement(int x, int y, int (*func)(), colorT c);

    private:
    int (*valueFunction)();
};

/*
SpriteElement class
Written By Thomas Li
Created 11/27/2020 
Last Modified 11/27/2020

This class inherits from UIElement, adds members for storing the width,
height, and color pattern of the sprite along with a constructor which can
be used to set them, overrides the renderSelf function to draw a formation
of pixels on screen using the stored position, dimensions, and color pattern,
and overrides the isClicked function to return true if the click falls 
within the bounds of the sprite as determined by the position and dimensions.

*/
class SpriteElement : UIElement {
    public:
    SpriteElement(int x, int y, int w, int h);
    SpriteElement(int x, int y, int w, int h, colorT** p);

    void resize(int w, int h);
    void setPattern(colorT** p);

    private:
    int width, height;
    colorT** pattern;
};