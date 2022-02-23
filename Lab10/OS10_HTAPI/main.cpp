#include <iostream>
#include "library.h"
#define testName "test.th"

int main() {
    const char * fileName = testName;

    HT::HTHANDLE * hthandle;

    try {

        //hthandle = HT::Create(48, 3, 10, 10, fileName);
/*        if(hthandle == nullptr)
            throw std::runtime_error("sldfkjkldj");*/

        hthandle = HT::Open( fileName);


        HT::Insert(hthandle, new HT::Element("lkko", 4, "TEST16", 6));
        HT::Insert(hthandle, new HT::Element("10(0", 4, "TEST17", 6));
        HT::Insert(hthandle, new HT::Element("kKSk", 4, "TEST18", 6));
        HT::Insert(hthandle, new HT::Element("439d", 4, "TEST19", 6));
        HT::Insert(hthandle, new HT::Element("kdk0", 4, "TEST20", 6));
        HT::Insert(hthandle, new HT::Element("azxc", 4, "TEST21", 6));
        HT::Insert(hthandle, new HT::Element("kxjc", 4, "TEST22", 6));
        HT::Insert(hthandle, new HT::Element("oe0e", 4, "TEST23", 6));
        HT::Insert(hthandle, new HT::Element("ncxo", 4, "TEST24", 6));
        HT::Insert(hthandle, new HT::Element("ncjc", 4, "TEST25", 6));
        HT::Insert(hthandle, new HT::Element("nico", 4, "TEST26", 6));
        HT::Insert(hthandle, new HT::Element("okdp", 4, "TEST27", 6));
        HT::Insert(hthandle, new HT::Element("3939", 4, "TEST28", 6));
        HT::Insert(hthandle, new HT::Element("1211", 4, "TEST29", 6));



        HT::Element *element = HT::Get(hthandle, new HT::Element("1vb1", 2));

        if (element != nullptr) {
            std::cout << element->keyLength << std::endl;
            std::cout << element->payloadLength << std::endl;
            std::cout << (char *) element->key << std::endl;
            std::cout << (char *) element->payload << std::endl;
        }

        HT::Print(hthandle);
        //std::cout << HT::Snap(hthandle);
        Sleep(5000);
        HT::Insert(hthandle, new HT::Element("nnnn", 4, "TEST16", 6));
        HT::Print(hthandle);
        HT::Close(hthandle);


    }catch(const char * error)
    {
        std::cout << "error" << std::endl;
    }

/*
    std::cout << "DEL" << std::endl;
    hthandle->PrintCurrentSize();
    BOOL res ;
    res = HT::Delete(hthandle, new HT::Element("11", 2));
    res = HT::Delete(hthandle, new HT::Element("12", 2));
    hthandle->PrintCurrentSize();
    std::cout << "DEL" << std::endl;
*/

    //UnmapViewOfFile(hthandle->shared);
}
