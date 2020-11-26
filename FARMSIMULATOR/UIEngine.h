#include "FEHLCD.h"

/*
Proteus UI Engine 
Created 11/25/2020
Last Modified: 11/25/2020

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

    - TextElement: Writes a specified text string with a specified font color, 
      with the color and string content both being changeable.

    - ValueElement: Similar to TextElement, except instead of a string it has a
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
Last Modified 11/25/2020

TO DO: Documentation of public members
TO DO: Member function definitations
*/
class UIElement {
    public:
    void render();

    void setClickHandler(void (*func)());
    void handleClick(int x, int y);

    void addChild(UIElement* childPtr);
    void removeChild(UIElement* childPtr);

    void addSelf(UIElement* parentPtr);
    void removeSelf();

    int getX();
    int getY();
    void setPos(int x, int y);

    protected:
    // each element type has a different rendering procedure consisting
    // of one or more FEHLCD library function calls
    // this function gets called by the public render function, which
    // also renders all of the elements children
    // for the generic UI element class, this function does nothing
    virtual void renderSelf();

    // elements also have a function to determine whether they've been 
    // touched given and an x and y coordinate for the touch
    // this function gets called by the public handleClick function
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
        void removeElement(UIElement* element);
        void renderElements();
        void handleClick(int x, int y);

        private:
        struct ElementListNode {
            UIElement* elementPtr = nullptr;
            ElementListNode* next = nullptr;
        };

        ElementListNode* head = nullptr;
    };

    ElementList* children = new ElementList();
};

// I'll be adding the rest of the class prototypes in the next commit