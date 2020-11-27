#include "UIEngine.h"

/* 
Member functions for UIElement 
Written by Thomas Li 
11/27/2020 
*/
void UIElement::render() {
    // render element itself, followed by all children
    renderSelf();
    children->renderElements();
}
bool UIElement::handleClick(int x, int y) {
    // check if children were clicked
    if (children->handleClick(x, y)) {
        // terminate callback if any were clicked
        return true;
    }
    // check if this element itself was clicked
    if (listenForClick && isClicked(x, y)) {
        // if clicked, execute the click handler
        // and return true to indicate that the element was clicked
        clickHandler();
        return true;
    }
    // return false if nothing was clicked
    return false;
}

void UIElement::setClickHandler(void (*func)()) {
    clickHandler = func; // assign handler
    listenForClick = true; // enable click detection
}
void UIElement::disableClickHandler() { listenForClick = false; }
void UIElement::enableClickHandler() { listenForClick = true; }

void UIElement::addChild(UIElement* childPtr) {
    children->addElement(childPtr); // add element to child subtree
    childPtr->parent = this; // set parent of child
}
void UIElement::removeChild(UIElement* childPtr) {
    // remove child from subtree if present there
    if (children->removeElement(childPtr)) {
        // set parent of child if child was removed
        childPtr->parent = nullptr;
    }
}

void UIElement::addSelf(UIElement* parentPtr){
    // add element to subtree of parent
    parentPtr->addChild(this);
}
void UIElement::removeSelf() {
    // remove element from subtree of parent
    parent->removeChild(this);
}

int UIElement::getX() { return xPos; }
int UIElement::getY() { return yPos; }
void UIElement::setPos(int x, int y) {
    xPos = x; // assign coordinates
    yPos = y;
}

void UIElement::freeMemory() {
    // free element's child subtree, followed by element itself
    children->freeElements();
    delete this;
}

void UIElement::renderSelf() {
    // do nothing for generic element
}

bool UIElement::isClicked(int x, int y) {
    // always return false for generic element
    return false;
}

/* 
Member functions for UIElement::ElementList 
Written by Thomas Li 
11/27/2020 
*/
void UIElement::ElementList::addElement(UIElement* element) {
    // set head to point to element if head is null
    if (!head) {
        head = new ElementListNode;
        head->elementPtr = element;
        
    }
    else {
        // otherwise, iterate through list until finding null node
        ElementListNode* iter = head;
        while (iter->next) {
            iter = iter->next;
        }
        // and create new list node that points to element
        iter->next = new ElementListNode;
        iter->next->elementPtr = element;
    }
}
bool UIElement::ElementList::removeElement(UIElement* element) {
    // do nothing if list is empty
    if (!head) return false;
    // if head points to element, replace head with next element
    if (head->elementPtr == element) {
        ElementListNode* newHead = head->next;
        delete head;
        head = newHead;
        // return true to indicate element deletion
        return true; 
    }
    // otherwise, search through list for node that points to element
    ElementListNode* iter = head;
    while (iter->next) {
        if (iter->next->elementPtr == element) {
            // remove node from list if element found
            ElementListNode* newNext = iter->next->next;
            delete iter->next;
            iter->next = newNext;
            // return true to indicate element deletion
            return true;
        }
        // move on to next element otherwise
        iter = iter->next;
    }
    // return false if no deletion was made
    return false;
}
void UIElement::ElementList::renderElements() {
    // iterate through list, call render function for each element
    // if list is empty, nothing happens
    ElementListNode* iter = head;
    while (iter) {
        iter->elementPtr->render();
        iter = iter->next;
    }
}
bool UIElement::ElementList::handleClick(int x, int y) {
    // iterate through list, call handleClick function on each element
    // return true if any calls return true
    // if list is empty, nothing happens
    ElementListNode* iter = head;
    while (iter) {
        if (iter->elementPtr->handleClick(x, y)) {
            return true;
        }
        else {
            iter = iter->next;
        }
    }
    return false;
}
void UIElement::ElementList::freeElements() {
    // iterate through list, call freeMemory function on each element
    // if list is empty, nothing happens
    ElementListNode* iter = head;
    while (iter) {
        iter->elementPtr->freeMemory();
        iter = iter->next;
    }
}

/*
Member functions for PolygonElement
Written by Thomas Li
11/27/2020
*/
// single-member assignments, fairly self-explanatory
void PolygonElement::setFillColor(colorT color) { fillColor = color; }
void PolygonElement::setLineColor(colorT color) { lineColor = color; }

// virtual functions - to be overridden by subclasses
void PolygonElement::renderSelf() { }
bool PolygonElement::isClicked(int x, int y) { return false; }

/*
Member functions for RectangleElement 
Written by Thomas Li
11/27/2020
*/
// constructors
RectangleElement::RectangleElement(int x, int y, int w, int h) {
    // assign members
    xPos = x;
    yPos = y;
    width = w;
    height = h;
}
RectangleElement::RectangleElement(int x, int y, int w, int h, colorT fill, colorT line) {
    // assign members
    xPos = x;
    yPos = y;
    width = w;
    height = h;

    fillColor = fill;
    lineColor = line;
}
    
// render prodecure override
void RectangleElement::renderSelf() {
    // fill rectangle with given dimensions and color
    LCD.SetFontColor(fillColor);
    LCD.FillRectangle(xPos, yPos, width, height);
    // draw rectangle border if line color differs from fill color
    if (fillColor != lineColor) {
        LCD.SetFontColor(lineColor);
        LCD.DrawRectangle(xPos, yPos, width, height);
    }
}

// isClicked function override
bool RectangleElement::isClicked(int x, int y) {
    return x >= xPos && x <= xPos + width && y >= yPos && y <= yPos + height;
}

void RectangleElement::setDimensions(int w, int h) {
    // assign dimensions
    width = w;
    height = h;
}
// single-member accessors
int RectangleElement::getWidth() { return width; }
int RectangleElement::getHeight() { return height; }

/* 
Member functions for CircleElement
Written by Thomas Li
11/27/2020
*/
// constructors
CircleElement::CircleElement(int x, int y, int r) {
    xPos = x;
    yPos = y;
    radius = r;
}
CircleElement::CircleElement(int x, int y, int r, colorT fill, colorT line) {
    xPos = x;
    yPos = y;
    radius = r;
    fillColor = fill;
    lineColor = line;
}

// render procedure override
void CircleElement::renderSelf() {
    // fill circle with given dimensions and color
    LCD.SetFontColor(fillColor);
    LCD.FillCircle(xPos, yPos, width, radius);
    // draw circle border if line color differs from fill color
    if (fillColor != lineColor) {
        LCD.SetFontColor(lineColor);
        LCD.DrawCircle(xPos, yPos, width, radius);
    }
}

// single-member assignment/access
void CircleElement::setRadius(int r) { radius = r; }
int CircleElement::getRadius() { return radius; }

/*
Member functions for TextElement
Written by Thomas Li
11/27/2020
*/
// single-member assignment
void TextElement::setFontColor(colorT c) { fontColor = c; }
// virtual functions - to be overridden by subclasses
void TextElement::renderSelf() { }
bool TextElement::isClicked(int x, int y) { return false; }

/*
Member functions for StringElement
*/

/*
Member functions for ValueElement
*/

/*
Member functions for SpriteElement
*/