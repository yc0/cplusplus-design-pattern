//
//  decorator.cpp
//  design-pattern
//
//  Created by nelson lin on 8/25/18.
//  Copyright © 2018 nelson lin. All rights reserved.
//

//  Decorator Pattern
//  Attach additional responsibilities to an object dynamically. Decorators provide a flexible alternative to subclassing for extending functionali

//  Client-specified embellishment of a core object by recursively wrapping it.


#include "decorator.hpp"
// 1. "lowest common denominator"
class Widget {
public:
    virtual void draw() = 0;
};

class TextField : public Widget {
public:
    TextField(int w, int h):_width(w),_height(h) {}
    void draw() override {
        printf("Textfield %d, %d\n", _width, _height);
    }
private:
    // 3. "Core" class & "is a"
    int _width, _height;
};

// 2. 2nd level base class
class Decorator : public Widget { // 4. "is a" relationship
public:
    Decorator(Widget *w) : _wid(w) {}
    void draw() override {
        _wid->draw();
    }
private:
    //  ** key part 4. "has a" relationship **
    Widget* _wid;
};

class BorderDecorator : public Decorator {
public:
    // 6. Optional embellishment
    BorderDecorator(Widget *w) : Decorator(w){}
    
    // virtual
    void draw() override {
        Decorator::draw();
        std::cout << "   BorderDecorator" << std::endl;
    }
};

class ScrollDecorator : public Decorator {
public:
    ScrollDecorator(Widget *w):Decorator(w) {}
    void draw() override {
        Decorator::draw();
        std::cout << "   ScrollDecorator" << std::endl;
    }
};

TEST(Structural, Decorator) {
    Widget *a = new BorderDecorator(new BorderDecorator(new ScrollDecorator(new TextField(80,25))));
    a->draw();
    delete a;
};
