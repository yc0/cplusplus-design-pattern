//
//  composite.cpp
//  design-pattern
//
//  Created by nelson lin on 8/25/18.
//  Copyright © 2018 nelson lin. All rights reserved.
//
//  Composite Design Pattern
//  Because having to query the "type" type of each object before attempting
//  to process  it is not desirable, applications need to manipulate a hierarchical collection of "primitive" and "composite" objects.
//  Compose objects into tree structures to represent whole-part hierarchies. Composite lets clients treat individual objects and compositions of objects uniformly.
//
//  1-to-many "has a" up the "is a" hierarchy

#include "composite.hpp"
class Component {
protected:
    int _value;
public:
    virtual void traverse() = 0;
};

class Primitive: public Component {
public:
    Primitive(int value);
    void traverse() override {
        std::cout << _value << " ";
    }
};

Primitive::Primitive(int value) {
    _value = value;
}

class Composite : public Component {
public:
    //Composite(int value):_value(value){};
    // Why can we write in initializer list way?
    // According to C++ Standard n3337 § 12.6.2/10,
    //  virtual base classes are initialized in the order they appear on a depth-first left-to-right traversal of the directed acyclic graph of base classes, where “left-to-right” is the order of appearance of the base classes in the derived class base-specifier-list.
    Composite(int value) {
        _value = value;
    }
    void add(Component *);
    void traverse() override {
        std::cout << _value << " ";
        for (size_t i=0; i < _children.size(); i++) {
            _children[i]->traverse();
        }
    }
private:
    std::vector<Component*> _children;
};

void Composite::add(Component *c) {
    _children.push_back(c);
}


class Row: public Composite {
public:
    Row(int v) : Composite(v) {}
    
    void traverse() override;
};
void Row::traverse() {
    std::cout << "Row";
    Composite::traverse();
}
class Column: public Composite {
public:
    Column(int v) : Composite(v) {}
    void traverse() override;
};
void Column::traverse() {
    std::cout << "Column";
    Composite::traverse();
}

TEST(Structural, Composite) {
    Row first(1);
    Column second(2);
    Column third(3);
    
    Row fourth(4);
    Row fifth(5);
    
    first.add(&second);
    first.add(&third);
    
    third.add(&fourth);
    third.add(&fifth);
    
    Primitive p6(6);
    Primitive p7(7);
    Primitive p8(8);
    Primitive p9(9);
    Primitive p10(10);
    first.add(&p6);
    second.add(&p7);
    third.add(&p8);
    fourth.add(&p9);
    fifth.add(&p10);
    first.traverse();
    std::cout << std::endl;
}
