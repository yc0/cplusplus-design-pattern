//
//  proxy.cpp
//  design-pattern
//
//  Created by nelson lin on 8/21/18.
//  Copyright © 2018 nelson lin. All rights reserved.
//

#include "proxy.hpp"

class Subject {
public:
    virtual void execute() = 0;
};

class Real : public Subject {
public:
    Real(std::string s) : _str(s) {}
    void execute() override { std::cout << _str << std::endl;}
private:
    std::string _str;
};

class Proxy : public Subject {
public:
    Proxy(std::string s);
    ~Proxy() {delete _ptr;}
    
    Real* operator->();
    void execute();
    
private:
    Real *_ptr;
    std::string first, second, third;
};

Proxy::Proxy(std::string s) {
    char a[48], b[48], c[48], rest[256];
    sscanf(s.c_str(),"%[a-zA-Z0-9] %[a-zA-Z0-9] %[a-zA-Z0-9] %[^\n]", a, b, c, rest);
    first = std::string(a);
    second = std::string(b);
    third = std::string(c);
    _ptr = new Real(std::string(rest));
//    sscanf(s.c_str(),"%[a-zA-Z0-9] %[a-zA-Z0-9] %[a-zA-Z0-9]", first, second, third);
}
Real* Proxy::operator->() {
    printf("%s %s   ", first.c_str(), second.c_str());
    return _ptr;   // proxy->execute => _ptr->execute()
}
void Proxy::execute() {
    printf("%s %s   ", first.c_str(), third.c_str());
    _ptr->execute();
}

TEST(Structual, Proxy) {
    Proxy obj("the quick brown fox jumped over the dog");
    obj->execute();
    obj.execute();
};
