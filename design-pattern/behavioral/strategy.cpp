//
//  strategy.cpp
//  design-pattern
//
//  Created by nelson lin on 8/21/18.
//  Copyright © 2018 nelson lin. All rights reserved.
//
//  The object-oriented design approach shown in figure is all about minimizing coupling. Since the client is coupled only to an abstraction (i.e. a useful fiction), and not a particular realization of that abstraction, the client could be said to be practicing "abstract coupling" . an object-oriented variant of the more generic exhortation "minimize coupling".

//  A more popular characterization of this "abstract coupling" principle is "Program to an interface, not an implementation".


#include "strategy.hpp"

class AbstractStrategy {
public:
    AbstractStrategy(int width):_width(width){}
    void format();
protected:
    int _width;
private:
    virtual void justify(char *line) = 0;

};

void AbstractStrategy::format() {
    char line[80], word[30];
    std::ifstream infile("/Users/nelson/Documents/developer/cplusplus/design-pattern/design-pattern/behavioral/quota.txt",std::ios::in);
    line[0] = '\0';
    
    infile >> word;
    strcat(line, word);
    
    while (infile >> word) {
        if(strlen(line)+strlen(word)+1>_width) {
            justify(line);
        } else {
            strcat(line, " ");
        }
        strcat(line, word);
    }
    justify(line);
    infile.close();
}


class LeftStrategy : public AbstractStrategy {
public:
    LeftStrategy(int width):AbstractStrategy(width){}
private:
    void justify(char *line) override;
};

void LeftStrategy::justify(char *line) {
    std::cout << line << std::endl;
    line[0] = '\0';
}

class RightStrategy: public AbstractStrategy {
public:
    RightStrategy(int width):AbstractStrategy(width){}
private:
    void justify(char *line) override;
};

void RightStrategy::justify(char *line) {
    char buf[80];
    int offset = _width - strlen(line);
    memset(buf, ' ', 80);
    std::strcpy(&(buf[offset]), line);
    std::cout << buf << std::endl;
    line[0] = '\0';
}

class CenterStrategy: public AbstractStrategy {
public:
    CenterStrategy(int width):AbstractStrategy(width){}
private:
    void justify(char *line) override;
};
void CenterStrategy::justify(char *line) {
    char buf[80];
    int offset = (_width - strlen(line))/2;
    memset(buf, ' ', 80);
    std::strcpy(&(buf[offset]), line);
    std::cout << buf << std::endl;
    line[0] = '\0';
}



class Testbed {
public:
    enum StrategyType {
        Dummy, Left, Center, Right
    };
    Testbed() {
        _strategy = nullptr;
    }
    void setStrategy(StrategyType,int);
    void doIt();
private:
    AbstractStrategy* _strategy;
};

void Testbed::setStrategy(Testbed::StrategyType type, int width) {
    delete _strategy;
    switch( type) {
        case Left:
            _strategy = new LeftStrategy(width);
            break;
        case Center:
            _strategy = new CenterStrategy(width);
            break;
            
        case Right:
            _strategy = new RightStrategy(width);
            break;
        default:
            _strategy = nullptr;
    }
}

void Testbed::doIt() {
    _strategy->format();
}

TEST(Behavioral, Strategy) {
    Testbed testbed;
    
    int answer, width;
    std::cout << "Exit(0) Left(1) Center(2) Right(3)" << std::endl;
    std::cin >> answer;
    
    while (answer) {
        std::cout << "Width: ";
        std::cin >> width;
        
        Testbed::StrategyType type;
        if (answer == 1) {
            type = Testbed::StrategyType::Left;
        } else if (answer == 2) {
            type = Testbed::StrategyType::Center;
        } else if (answer == 3){
            type = Testbed::StrategyType::Right;
        }
        testbed.setStrategy(type,width);
        testbed.doIt();
        
        std::cout << "Exit(0) Left(1) Center(2) Right(3)" << std::endl;
        std::cin >> answer;
    }
    std::cout << "ByeBye!!" << std::endl;
};
