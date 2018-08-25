//
//  Observer.cpp
//  design-pattern
//
//  Created by nelson lin on 8/25/18.
//  Copyright © 2018 nelson lin. All rights reserved.
//
//  Observer Pattern
//  Define a one-to-many dependency between objects so that when one object changes state, all its dependents are notified and updated automatically.
//  The "View" part of Model-View-Controller.
#include "Observer.hpp"

class AbstractObserver;
class Subject {
public:
    void attach(AbstractObserver *o) {
        _views.push_back(o);
    }
    void setVal(int v) {
        _value = v;
        notify();
    }
    int getVal() {
        return _value;
    }
    void notify();
private:
    std::vector<AbstractObserver *> _views;
    int _value;
};


class AbstractObserver {
public:
    AbstractObserver(Subject *, int);
    virtual void update() = 0;
protected:
    Subject *getSubject() {
        return _sub;
    }
    int getDivisor() {
        return _denom;
    }
private:
    Subject *_sub;
    int _denom;
};

AbstractObserver::AbstractObserver(Subject *sub, int div) {
    _sub = sub;
    _denom = div;
    sub->attach(this);
}

void Subject::notify() {
    for(auto i=_views.begin(); i!= _views.end(); i++) {
        (*i)->update();
    }
}
class DivObserver:public AbstractObserver {
public:
    DivObserver(Subject *sub, int div):AbstractObserver(sub,div){}
    void update() override {
        // 6. "Pull" information of interest
        int v = getSubject()->getVal(), d = getDivisor();
        std::cout << v << " div " << d << " is " << v/d << std::endl;
    }
};


class ModObserver : public AbstractObserver {
public:
    ModObserver(Subject *sub, int div):AbstractObserver(sub, div){}
    void update() override {
        int v = getSubject()->getVal(), d = getDivisor();
        std::cout << v << " mod " <<  d << " is " << v%d << std::endl;
    }
};


TEST(Behavioral, Observer) {
    Subject sub;
    DivObserver div1(&sub, 4);
    DivObserver div2(&sub, 3);
    ModObserver mod(&sub, 3);
    sub.setVal(14);
};

