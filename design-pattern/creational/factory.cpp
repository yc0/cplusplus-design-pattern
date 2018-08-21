//
//  factory.cpp
//  design-pattern
//
//  Created by nelson lin on 8/21/18.
//  Copyright © 2018 nelson lin. All rights reserved.
//
//  Factory Method is to creating objects as Template Method. A superclass specifies all standard and generic behavior (using pure virtual "placeholders" for creation steps), and then delegates the creation details to subclasses that are supplied by the client.

//  Factory Method is similar to Abstract Factory but without the emphasis on families.

//  Factory Methods are routinely specified by an architectural framework, and then implemented by the user of the framework
#include "factory.hpp"

class AbstractDocument {
public:
    AbstractDocument(char *c) {
        strcpy(name, c);
    }
    virtual void Open()  = 0;
    virtual void Close() = 0;
    
    char* getName() {
        return name;
    }
private:
    char name[20];
};


class MyDocument:public AbstractDocument {
public:
    MyDocument(char* fn):AbstractDocument(fn){}
    void Open();
    void Close();
};

void MyDocument::Open(){
    std::cout << "    My Document: Open()" << std::endl;
}

void MyDocument::Close() {
    std::cout << "    My Document: Close()" << std::endl;
}

// Framework declaration
class AbstractApplication {
public:
    AbstractApplication(): _index(0) {
        std::cout << "Application: ctor" << std::endl;
    }
    
    void NewDocument(char *name);
    void OpenDocument(){}
    void ReportDocs();
    virtual AbstractDocument* createDocument(char*) = 0;
private:
    int _index;
    AbstractDocument* _doc[10];
};

void AbstractApplication::NewDocument(char *name) {
    std::cout << "Application: NewDocument()" << std::endl;
    _doc[_index] = createDocument(name);
    _doc[_index++]->Open();
}

void AbstractApplication::ReportDocs() {
    std::cout << "Application ReportDocs" << std::endl;
    for (size_t i=0; i < _index; i++) {
        std::cout << "    " << _doc[i]->getName() << std::endl;
    }
}


class MyApplication: public AbstractApplication {
public:
    MyApplication() {
        std::cout << "MyApplication: ctor" << std::endl;
    }
    AbstractDocument* createDocument(char *fn);
};
AbstractDocument* MyApplication::createDocument(char *fn) {
    std::cout << "    Myapplication: createDocument()" << std::endl;
    return new MyDocument(fn);
}

TEST(Creational, Factory) {
    MyApplication myapp;
    
    myapp.NewDocument("foo");
    myapp.NewDocument("bar");
    
    myapp.ReportDocs();
};
