//
//  builder.cpp
//  design-pattern
//
//  Created by nelson lin on 8/20/18.
//  Copyright © 2018 nelson lin. All rights reserved.
//
//  The origins adopt different OSs to examplify the builder pattern.
//  However, I think it is too complex to understand the concept
//  For example, Unix v.s. VMS. How many people do know the difference between
//  those two OSs, such as their file system. I try to reconstruct the UML sample-Reader and Converter in C++ sample. Hopefully, you can feel more readable. Also, I still point out the author idea, if you really want to know.

//  VMS : OpenVMS is a closed-source, proprietary computer operating system for use in general-purpose computing. It is the successor to the VMS Operating System (VAX-11/VMS, VAX/VMS). VAX is a sort of ancestor of BSD.
//  ISAM, Indexed Sequential Access Method
//  Pathway, LWP versus Thread as follows

//  在many-to-many或two-level module 的multithread環境下，
//  大多會採用一個data structure 把他放置在user thread 和 kernel thread之間，
//
//示意圖大概長這樣:
//︴ user thread
//     ︳
//     ︳
//    LWP
//     ︳
//     ︳
//○ kernal thread
//
//而這個LWP叫做lightweught process，沒有錯，和洪兔說的thread的別稱一樣，
//為什麼我也不太懂@@?
//而它的用途，我自己的解讀，主要像是在當一個虛擬的processor來控制user thread，
//當然LWP自己本身是受kernel thread控制的，所以一旦kernel thread被block，
//那LWP也會block。
//
//而如果現在有一個event發生，這時候kernel就會對LWP發出Upcall，LWP裡面存在著
//Upcall handler，會偵測需要block的user thread將其block，進而暫時放掉整個LWP。
//而kernel再重新創造一個LWP繼續讓其他的user thread繼續運作，等到event結束，
//kernel再發出Upcall，像上面說的一樣，讓原來被放掉的的LWP重新運作。
// From Operating System Concepts, but not yet translate

#include "builder.hpp"
enum DataType {
  TABLE, LIST, PARAGRAPH
};

struct DataAttribute {
    DataType type;
    char value[30];
};

class Document {
public:
    Document(char*);
    void setLine(char*, char*);
    void setParagraph(char*, char*);
    void setTable(char*, char*);
    const char* getDesc();
private:
    char _desc[200], _tmp[80];
};

Document::Document(char *type) {
    sprintf(_desc, "Document for:%s", type);
};

void Document::setLine(char *l, char*v) {
    sprintf(_tmp,"\n Line(%s): %s", l, v);
    strcat(_desc, _tmp);
};
void Document::setParagraph(char *p, char *v) {
    sprintf(_tmp,"\n Paragraph(%s): %s", p, v);
    strcat(_desc, _tmp);
};
void Document::setTable(char *t, char *v) {
    sprintf(_tmp,"\n Table(%s): %s", t, v);
    strcat(_desc, _tmp);
};

const char* Document::getDesc() {
    return _desc;
};
class AbstractConvert {
public:
    virtual void makeLine(char *) =0;
    virtual void makeParagraph(char *) =0;
    virtual void makeTable(char *)=0;
    Document *getDocument() {
        return _result;
    }
protected:
    Document *_result;
};

class PDFConverter:public AbstractConvert {
public:
    PDFConverter();
    ~PDFConverter();
    void makeLine(char *);
    void makeParagraph(char *);
    void makeTable(char *);
};

PDFConverter::PDFConverter(){
    _result = new Document("PDF");
};

PDFConverter::~PDFConverter(){
    delete _result;
}

void PDFConverter::makeLine(char *name) {
    _result->setLine("PDF", name);
};

void PDFConverter::makeParagraph(char *name) {
    _result->setParagraph("PDF", name);
};

void PDFConverter::makeTable(char *name) {
    _result->setTable("PDF",name);
};

class ASCIIConverter: public AbstractConvert {
public:
    ASCIIConverter();
    ~ASCIIConverter();
    void makeLine(char *);
    void makeParagraph(char *);
    void makeTable(char *);
};


ASCIIConverter::ASCIIConverter(){
    _result = new Document("ASCII");
};

ASCIIConverter::~ASCIIConverter(){
    delete _result;
}

void ASCIIConverter::makeLine(char *name) {
    _result->setLine("ASCII", name);
};

void ASCIIConverter::makeParagraph(char *name) {
    _result->setParagraph("ASCII", name);
};

void ASCIIConverter::makeTable(char *name) {
    _result->setTable("ASCII",name);
};


class Reader {
public:
    Reader(AbstractConvert *converter) {
        _converter = converter;
    };
    void parseInput(DataAttribute*, int);
private:
    AbstractConvert *_converter;
};

void Reader::parseInput(DataAttribute list[], int num) {
    for (size_t i=0; i < num; i++) {
        switch(list[i].type) {
            case PARAGRAPH:
                _converter->makeParagraph(list[i].value);
                break;
            case LIST:
                _converter->makeLine(list[i].value);
                break;
            case TABLE:
                _converter->makeTable(list[i].value);
                break;
        }
        
    }
    std::cout << _converter->getDocument()->getDesc() << std::endl;
};

// concrete classes : PDF and ASCII converter

TEST(Creational,Builder) {
    const int num_entries = 6;
    DataAttribute data[num_entries] = {
        {LIST,"abc_list"},
        {LIST,"efg_list"},
        {PARAGRAPH, "ABC_PARAGRAPH"},
        {PARAGRAPH, "efg_PARAGRAPH"},
        {TABLE, "zzz_table"},
        {TABLE, "yyy_table"}
    };
    
    ASCIIConverter asciibuilder;
    PDFConverter   pdfbuilder;
    
    Reader reader(&asciibuilder);
    reader.parseInput(data, num_entries);
    
    reader = Reader(&pdfbuilder);
    reader.parseInput(data, num_entries);
};
