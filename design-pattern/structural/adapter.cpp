//
//  adapter.cpp
//  design-pattern
//
//  Created by nelson lin on 8/22/18.
//  Copyright © 2018 nelson lin. All rights reserved.
//
//  1.Convert the interface of a class into another interface clients expect. Adapter lets classes work together that couldn't otherwise because of incompatible interfaces.
//  2. Wrap an existing class with a new interface.
//  3. Impedance match an old component to a new system
#include "adapter.hpp"

class ExecuteInterface {
public:
    // 1. specify the new interface
    virtual ~ExecuteInterface(){}
    virtual void execute() = 0;
};

// Design a "wrapper" or "adapter" class
template <class TYPE>
class ExecuteAdapter: public ExecuteInterface {
public:
    ExecuteAdapter(TYPE *o, void(TYPE:: *m)()) {
        _obj = o;
        _method = m;
    }
    ~ExecuteAdapter() {delete _obj;}
    // 4. The adapter / wrapper MAPS the new to the legacy implementation
    void execute() {
        (_obj->*_method)();
    }
private:
    TYPE *_obj;
    void(TYPE:: *_method)(); // ptr-to-member-function attribute
};

// The old : three total impcompatible classes
// no common base class

class Fea {
public:
    ~Fea() {
        std::cout << "Fea::dtor" << std::endl;
    }
    void doThis() {
         std::cout << "Fea::doThis()" << std::endl;
    }
};

class Feye {
public:
    ~Feye() {
        std::cout << "Feye::dtor" << std::endl;
    }
    void doThat() {
        std::cout << "Feye::doThat()" << std::endl;
    }
};

class Pheau {
public:
    ~Pheau() {
        std::cout << "Pheau::dtor" << std::endl;
    }
    void doOthers() {
        std::cout << "Pheau::doOthers()" << std::endl;
    }
};


ExecuteInterface **initializate() {
    ExecuteInterface **eifs = new ExecuteInterface *[3];
    eifs[0] = new ExecuteAdapter<Fea>(new Fea(), &Fea::doThis);
    eifs[1] = new ExecuteAdapter<Feye>(new Feye(), &Feye::doThat);
    eifs[2] = new ExecuteAdapter<Pheau>(new Pheau(), &Pheau::doOthers);
    return eifs;
}

TEST(Structural, Adapter) {
    ExecuteInterface **eifs =initializate();
    
    // 3. Client uses the new (polymporphism)
    for(size_t i=0; i < 3; i++) {
        eifs[i]->execute();
    }
    
    // RAII Resource Acquisition Is Initialization
    for(size_t i=0; i < 3; i++) {
        delete eifs[i];
    }
    
    delete eifs;
};
