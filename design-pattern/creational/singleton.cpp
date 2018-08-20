//
//  singleton.cpp
//  design-pattern
//
//  Created by nelson lin on 8/20/18.
//  Copyright © 2018 nelson lin. All rights reserved.
//

#include "singleton.hpp"
class Number {
public:
    static Number* instance();
    static void setType(std::string t);
    
    virtual void setValue(int in) {
        value = in;
    }
    virtual int getValue() {
        return value;
    }
protected:
    int value;
    
    Number() {
        std::cout << "ctor: ";
    }
private:
    static Number *_inst;
    static std::string type;
};

std::string Number::type = "decimal";
Number* Number::_inst = 0;

void Number::setType(std::string t) {
    type = t;
    delete _inst;
    _inst = 0;
};

class Octal: public Number {
public:
    friend class Number; // can direct let Number operate octal non-public member
                         // here, we constrain constructor of Octal
    void setValue(int in) override {
        char buf[10];
        sprintf(buf, "%o", in);
        sscanf(buf, "%d", &value);
    }
protected:
    Octal() {};
};


Number* Number::instance() {
    if (!_inst) {
        if (type=="octal") {
            _inst = new Octal();
        } else {
            _inst = new Number();
        }
    }
    return _inst;
};

TEST(Creational, Singleton) {
    Number::instance()->setValue(42); // Number
    std::cout << "value is " << Number::instance()->getValue() << std::endl;
    
    Number::instance()->setType("octal");
    Number::instance()->setValue(64);
    std::cout << "value is " << Number::instance()->getValue() << std::endl;
};
