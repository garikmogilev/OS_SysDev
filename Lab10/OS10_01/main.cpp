//
// Created by Skvortsoff on 2/9/2022.
//

#include <iostream>
#include <windows.h>
#include <list>
#include "headers/HANDLE.h"
#include "headers/CRUD.h"

int main(int argc, char *argv[]) {
    const CHAR *fileName = "../resources/test2.th";
    HT::HTHANDLE * hthandle;

    try {
        hthandle = HT::Create(48, 3, 10, 10, fileName);
        //hthandle = HT::Open( fileName);
    if(hthandle == nullptr)
        throw "Chto-to poshlo ne tak";

    HT::Insert(hthandle, new HT::Element("1123", 4, "TEST1", 5));
    HT::Insert(hthandle, new HT::Element("1232", 4, "TEST2", 5));
    HT::Insert(hthandle, new HT::Element("3sda", 4, "TEST3", 5));
    HT::Insert(hthandle, new HT::Element("4zxc", 4, "TEST4", 5));
    HT::Insert(hthandle, new HT::Element("5qe5", 4, "TEST5", 5));
    HT::Insert(hthandle, new HT::Element("6zxe", 4, "TEST6", 5));
    HT::Insert(hthandle, new HT::Element("7asd", 4, "TEST7", 5));
    HT::Insert(hthandle, new HT::Element("asd8", 4, "TEST8", 5));
    HT::Insert(hthandle, new HT::Element("9asd", 4, "TEST9", 5));
    HT::Insert(hthandle, new HT::Element("1bn0", 4, "TEST10", 6));
    HT::Insert(hthandle, new HT::Element("1vb1", 4, "TEST11", 6));
    HT::Insert(hthandle, new HT::Element("0909", 4, "TEST12", 6));
    HT::Insert(hthandle, new HT::Element("jjkk", 4, "TEST13", 6));
    HT::Insert(hthandle, new HT::Element("jjkk", 4, "TEST14", 6));



        auto element = HT::Get(hthandle, new HT::Element("jjkk", 4));
        if(element) std::cout << "!!!!!!!!!FOUND GET!!!!!!!!!!!!!!!!\n";
        else std::cout << "!!!!!!!!!NOT FOUND GET!!!!!!!!!!!!!!!!\n";

        if (element != nullptr) {
            std::cout << element->keyLength << std::endl;
            std::cout << element->payloadLength << std::endl;
            std::cout << (char *) element->key << std::endl;
            std::cout << (char *) element->payload << std::endl;
        }

        HT::Print(hthandle);
        //std::cout << HT::Snap(hthandle);
        Sleep(5000);
        //HT::Insert(hthandle, new HT::Element("nnnn", 4, "TEST16", 6));
        BOOL res = HT::Update(hthandle, new HT::Element("jjkk", 4, "TEST19", 6));

        if(res) std::cout << "!!!!!!!!!FOUND UPDATE!!!!!!!!!!!!!!!!\n";
        else std::cout << "!!!!!!!!!NOT FOUND UPDATE!!!!!!!!!!!!!!!!\n";
        HT::Print(hthandle);
        HT::Close(hthandle);


    }catch(const char * error)
    {
        std::cerr << error << std::endl;
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
