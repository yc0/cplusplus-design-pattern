//
//  bridge.cpp
//  design-pattern
//
//  Created by nelson lin on 8/21/18.
//  Copyright © 2018 nelson lin. All rights reserved.
//
//  The Bridge design pattern proposes refactoring this exponentially explosive inheritance hierarchy into two orthogonal hierarchies

#include "bridge.hpp"
class TimeImp {
public:
    TimeImp(int hr, int min):_hr(hr),_min(min){}
    virtual void tell() {
        std::cout << "time is " << std::setw(2) << std::setfill('0') << _hr << _min << std::endl;
    }
protected:
    int _hr, _min;
};


class CivilianTimeImp: public TimeImp {
public:
    CivilianTimeImp(int hr, int min, short pm):TimeImp(hr,min) {
        if (pm) {
            strcpy(_ampm, "PM");
        } else {
            strcpy(_ampm, "AM");
        }
    }
    void tell() override {
        std::cout << "time is " << _hr << ":" << _min << _ampm << std::endl;
    }
protected:
    char _ampm[4];
};

class ZuluTimeImp: public TimeImp {
public:
    ZuluTimeImp(int hr, int min, int zone):TimeImp(hr,min){
        if (zone==5) {
            strcpy(_zone, " Eastern Standard Time");
        } else {
            strcpy(_zone, " Central Standard Time");
        }
    }
    void tell() override {
        std::cout << "time is " << std::setw(2) << std::setfill('0') << _hr << _min << _zone << std::endl;
    }
protected:
    char _zone[30];
};

class Time { // encapsulator / handle
public:
    Time(){}
    Time(int hr, int min) {
        _impl = new TimeImp(hr, min);
    }
    virtual void tell() {
        _impl->tell();
    }
protected:
    TimeImp *_impl; // body
};
class CivilianTime: public Time {
public:
    CivilianTime(int hr, int min, int pm) {
        _impl = new CivilianTimeImp(hr, min, pm);
    }
};
class ZuluTime: public Time {
public:
    ZuluTime(int hr, int min, int zone) {
        _impl = new ZuluTimeImp(hr, min, zone);
    }
};

TEST(Structural, Bridge) {
    Time *times[3];
    times[0] = new Time(14,30);
    times[1] = new CivilianTime(2,30,1);
    times[2] = new ZuluTime(14,30,6);
    for (size_t i=0; i < 3; i++) {
        times[i]->tell();
    }
};
