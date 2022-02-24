//
// Created by Skvortsoff on 2/9/2022.
//

#include <iostream>
#include <windows.h>
#include <list>
#include "D:\GitHub\OS_SysDev\Lab10\OS10_01\headers\CRUD.h"
#include "D:\GitHub\OS_SysDev\Lab10\OS10_01\headers\HANDLE.h"
#define SIZE_TEMP 128
#define METHOD_OPEN_FILE

int main(int argc, char *argv[]) {
    const CHAR *fileName = "test2.th";
    HT::HTHANDLE * hthandle = nullptr;
    BOOL test;
    char name[] = "test";
    char temp[SIZE_TEMP];

    try {
#ifdef METHOD_OPEN_FILE
        /// create file mapping *****************************
        hthandle = HT::Create(48, 3, 10, 10, fileName);

        if(hthandle == nullptr)
            throw std::runtime_error("Error create mapping");
        else
            std::cout << "Create success" << std::endl;
        /// *************************************************
#endif
#ifndef METHOD_OPEN_FILE
        /// open file mapping ******************************
        hthandle = HT::Open( fileName);

        if(hthandle == nullptr)
            throw std::runtime_error("Error open mapping");
        else
            std::cout << "Open success" << std::endl;
        /// *************************************************
#endif
        /// insert Element **********************************
        for (int i = 1; i < 12; i++) {
            memset(temp, 0, SIZE_TEMP);
            strcat(temp, name);
            strcat(temp, std::to_string(i).c_str());

            test = HT::Insert(hthandle, new HT::Element(
                    std::to_string(i).c_str(),
                    (int)strlen(std::to_string(i).c_str()),
                    temp,
                    (int) strlen(temp)
            ));

            if(test == false)
                throw std::runtime_error("Error");
            else
                std::cout << "Element inserted" << std::endl;
        }
        /// *************************************************

        /// get Element *************************************
        auto element = HT::Get(hthandle, new HT::Element("1", 1));

        if(element == nullptr)
            std::cout << "Element not found" << std::endl;
        else {
            std::cout << "Element found" << std::endl;
            Print(element);
        }

        element = HT::Get(hthandle, new HT::Element("a", 1));

        if(element == nullptr)
            std::cout << "Element not found" << std::endl;
        else {
            std::cout << "Element found" << std::endl;
            Print(element);
        }
        /// *************************************************

        /// update Element **********************************
        test = HT::Update(hthandle, new HT::Element("2", 1, "TEST_1234", 9));

        if(test == FALSE)
            throw std::runtime_error("Element not updated");
        else {
            std::cout << "Element updated" << std::endl;
        }

        HT::PrintAll(hthandle);

        /// close file mapping *****************************
        test = HT::Close(hthandle);
        if(test == FALSE)
            throw std::runtime_error("Error close mapping");
        else
            std::cout << "Close success" << std::endl;
        /// ************************************************


    }
    catch(std::runtime_error &error)
    {
        std::cerr << "runtime_error: " << error.what() << std::endl;
        std::cerr << HT::GetLastError(hthandle) << std::endl;
        if(test == FALSE)
            throw std::runtime_error("Error close mapping");
        else
            std::cout << "Close success" << std::endl;
    }
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
