//
// Created by Skvortsoff on 2/9/2022.
//
#include <iostream>
#include <stdexcept>
#include"../headers/HANDLE.h"
#include "../headers/Element.h"
#include <string_view>
#define EXTENSION_FILES ".th"
#define PATH_BACKUPS "../backups/"
#define DEFAULT_SNAP_TIME 3

namespace HT {

    HTHANDLE::HTHANDLE() {
        this->shared = new BetweenProcessMemory();
        this->shared->secSnapshotInterval = DEFAULT_SNAP_TIME;
    };

    HTHANDLE::HTHANDLE(int capacity, int secSnapshotInterval, int maxKeyLength, int maxPayLoadLength,const char fileName[512]) {
        this->shared = new BetweenProcessMemory
                (AlignmentMemory(
                         sizeof(Element),
                         maxKeyLength + 1,
                         maxPayLoadLength + 1
                 ),
                 capacity,
                 maxPayLoadLength + 1,
                 maxKeyLength + 1
                );
        this->shared->secSnapshotInterval = secSnapshotInterval;
        this->fileName = fileName;
    }

    BetweenProcessMemory::BetweenProcessMemory(int sizeElement, int capacity, int maxKeyLength, int maxPayLoadLength) {
        this->currentCapacity = 0;
        this->sizeElement = sizeElement;
        this->capacity = capacity;
        this->maxKeyLength = maxKeyLength;
        this->maxPayLoadLength = maxPayLoadLength;
        this->secSnapshotInterval = DEFAULT_SNAP_TIME;
    }

    BetweenProcessMemory::BetweenProcessMemory(){
        this->secSnapshotInterval = DEFAULT_SNAP_TIME;
    }

    LPVOID HTHANDLE::Offset(unsigned int index) const {
        return (void *) ((char *) this->address + (this->shared->sizeElement * index));
    }

    void HTHANDLE::PrintCurrentSize() const {
        std::cout << "----------------------------------" << std::endl;
        std::cout << "Size: " << this->shared->capacity << "/" << this->shared->currentCapacity << std::endl;
        std::cout << "----------------------------------" << std::endl;
    }

    int HTHANDLE::AlignmentMemory(int sizeElement, int maxKeyLength, int maxPayLoadLength) {
        int size = sizeElement + maxKeyLength + maxPayLoadLength;
        if (size % 4 == 0)
            return size;
        else {
            return size + abs((long) size % 4 - 4);
        }
    }

    HTHANDLE * Create(int capacity, int secSnapshotInterval, int maxKeyLength, int maxPayLoadLength, const char *fileName) {
        HTHANDLE * hthandle;
        int sizeMap =
                (HT::HTHANDLE::AlignmentMemory(sizeof(Element), maxKeyLength, maxPayLoadLength)) * capacity +
                sizeof(BetweenProcessMemory);
        std::cout << "Map size: " << sizeMap << std::endl;

        try {
            HANDLE file = CreateFile(
                    fileName,
                    GENERIC_WRITE | GENERIC_READ,
                    0,
                    nullptr,
                    OPEN_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL,
                    nullptr
            );
            if (file == INVALID_HANDLE_VALUE)
                throw std::runtime_error("Can't create or open the file");

            HANDLE fileMapping = CreateFileMapping(
                    file,
                    nullptr,
                    PAGE_READWRITE,
                    0,
                    sizeMap,
                    fileName
            );
            if (fileMapping == nullptr)
                throw std::runtime_error("Mapping created failed");

            auto map = MapViewOfFile(
                    fileMapping,
                    FILE_MAP_ALL_ACCESS,
                    0,
                    0,
                    0
            );

            if (map == nullptr)
                throw std::runtime_error("Mapping create failed");

            auto * shared = (BetweenProcessMemory*)map;
            hthandle = new HTHANDLE(capacity, secSnapshotInterval, maxKeyLength, maxPayLoadLength, fileName);
            * shared = * hthandle->shared;
            hthandle->shared = shared;
            hthandle->shared->sizeMap = sizeMap;
            hthandle->file = file;
            hthandle->fileMapping = fileMapping;
            hthandle->address = (char*)map + sizeof(BetweenProcessMemory);
            hthandle->mutex = CreateMutex(nullptr, FALSE, "OS10");

        } catch (const std::runtime_error & err) {
            std::cerr << "Error: " << err.what() << std::endl;
            return nullptr;
        }
        return hthandle;
    }

    HTHANDLE *Open(const char fileName[512]) {
        auto * hthandle = new HTHANDLE();
        BetweenProcessMemory * shared{};
        HANDLE fileMapping{};
        LPVOID map{};

        try{
            HANDLE file = CreateFile(
                    fileName,
                    GENERIC_WRITE | GENERIC_READ,
                    0,
                    nullptr,
                    OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL,
                    nullptr
            );

            if (file == INVALID_HANDLE_VALUE) {
                std::cerr << "Can't create or open the file, try CreateFileMapping" << std::endl;

                fileMapping = CreateFileMapping(
                        INVALID_HANDLE_VALUE,
                        nullptr,
                        PAGE_READWRITE,
                        0,
                        sizeof(BetweenProcessMemory),
                        fileName
                );

                if (!fileMapping)
                    throw std::runtime_error("Open -> CreateFileMapping -> error");

                map = MapViewOfFile(
                        fileMapping,
                        FILE_MAP_ALL_ACCESS,
                        0,
                        0,
                        0
                );

                if (!map)
                    throw std::runtime_error("Open -> MapViewOfFile -> error");

                shared = (BetweenProcessMemory *) map;
                if(shared->capacity == 0)
                    throw std::runtime_error("Open -> Capacity is 0");

                hthandle->shared = shared;
            }

            fileMapping = CreateFileMapping(
                    file,
                    nullptr,
                    PAGE_READWRITE,
                    0,
                    hthandle->shared->sizeMap,
                    fileName
            );

            if (!fileMapping)
                throw std::runtime_error("Open -> CreateFileMapping -> error");

            map = MapViewOfFile(
                    fileMapping,
                    FILE_MAP_ALL_ACCESS,
                    0,
                    0,
                    0
            );

            if (!map)
                throw std::runtime_error("Open -> MapViewOfFile -> error");

            shared = (BetweenProcessMemory *) map;
            if(shared->capacity == 0)
                throw std::runtime_error("Open -> Capacity is 0");

            hthandle->shared = shared;
            hthandle->address = (char *) map + sizeof(BetweenProcessMemory);
            hthandle->mutex = CreateMutex(nullptr, FALSE, "OS10");
            hthandle->threadSnap.handle = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) SnapThread, hthandle, 0,
                                                       &hthandle->threadSnap.ID);
            hthandle->PrintCurrentSize();
        } catch (std::runtime_error &err) {
            std::cerr << "Error: " << err.what() << std::endl;
            return nullptr;
        }
        return hthandle;
    }

    BOOL Close(HTHANDLE * hthandle){
        hthandle->exit = true;  // variable for exit thread for snap
        hthandle->fixed = true;  // don't need to do snapshot, to fix the file
        if (!FlushViewOfFile(hthandle->shared, hthandle->shared->sizeMap))
        {
            throw std::runtime_error("Close -> FlushViewOfFile -> error");
            strcpy(hthandle->lastErrorMessage, (char *) "Element not found");
            return FALSE;
        }


        hthandle->exit = true;  // variable for exit thread for snap
        WaitForSingleObject( hthandle->threadSnap.handle, INFINITE);

        if(!CloseHandle( hthandle->file)){
            strcpy(hthandle->lastErrorMessage, (char *)  "Error close handle file");
            return FALSE;
        }
        if(!CloseHandle( hthandle->fileMapping)){
            strcpy(hthandle->lastErrorMessage, (char *)  "Error close handle mapping");
            return FALSE;
        }
        if(!CloseHandle( hthandle->threadSnap.handle)){
            strcpy(hthandle->lastErrorMessage, (char *)  "Error close handle thread");
            return FALSE;
        }

        if(!CloseHandle(hthandle->mutex)) {
            strcpy(hthandle->lastErrorMessage, (char *) "Error close handle mutex");
            return FALSE;
        }

        delete hthandle;
        return TRUE;
    }

    unsigned int Hash(HTHANDLE *hthandle, const char *key) {
        std::string_view temp{key};
        std::hash< std::string_view> hashing;
        return hashing(temp) % hthandle->shared->capacity;
    }

    unsigned int HashNext(unsigned int hash, unsigned int size, unsigned int i) {
        return (hash + 5 * i + 3 * i * i) % size;
    }

    void Print(HTHANDLE *hthandle) {

        std::cout.setf(std::ios::left);
        std::cout.width(hthandle->shared->maxKeyLength);
        std::cout << "KEY";
        std::cout.setf(std::ios::left);
        std::cout.width(hthandle->shared->maxPayLoadLength);
        std::cout << "VALUE" << std::endl;

        for (int i = 0; i < hthandle->shared->capacity; i++) {
            auto offset = hthandle->Offset(i);
            auto *element = (Element *) hthandle->Offset(i);

            if (((Element *) (offset))->key != nullptr) {
                element->PointerCorrecting(hthandle->shared->maxKeyLength);
                std::cout.setf(std::ios::left);
                std::cout.width(hthandle->shared->maxKeyLength);
                std::cout << (char *) element->key;
                std::cout.width(hthandle->shared->maxPayLoadLength);
                std::cout << (char *) element->payload << std::endl;
            }
        }
    }

    void GetLastError(HTHANDLE * hthandle) {
        std::cerr << hthandle->lastErrorMessage << std::endl;
    }

    BOOL Snap(HTHANDLE * hthandle) {
        std::string name;
        time_t t1;
        tm ttm{};
        DWORD bytesWritten;

        t1 = time(&t1);
        localtime_s(&ttm, &t1);

        name += PATH_BACKUPS;
        name += std::to_string(ttm.tm_mday) + "." + std::to_string(ttm.tm_mon) + "." +
                std::to_string(1900 + ttm.tm_year) + "_";
        name += std::to_string(ttm.tm_hour) + "." + std::to_string(ttm.tm_min) + "." + std::to_string(ttm.tm_sec) +
                EXTENSION_FILES;

        WaitForSingleObject(hthandle->mutex, INFINITE);

        HANDLE file = CreateFile((LPCSTR) name.c_str(),
                                 GENERIC_WRITE,
                                 0,
                                 nullptr,
                                 CREATE_NEW,
                                 0,
                                 nullptr);

        if (file == INVALID_HANDLE_VALUE) {
            strcpy(hthandle->lastErrorMessage, (char*)"Error opening source ");
        }

        bool writeFile = WriteFile(
                file,
                hthandle->address,
                (hthandle->shared->capacity * hthandle->shared->sizeElement),
                &bytesWritten,
                nullptr
        );
        ReleaseMutex(hthandle->mutex);

        if (writeFile) {
            std::cout << "Length: " << bytesWritten << " Name snap: " << name << std::endl;
            return TRUE;
        } else {
            strcpy(hthandle->lastErrorMessage, (char*)"Error opening source ");
            return FALSE;
        }
    }

    DWORD WINAPI SnapThread(HTHANDLE *hthandle) {
        HANDLE mutex = CreateMutex(nullptr, FALSE, "SNAP");

        while (!hthandle->exit) {
            WaitForSingleObject(mutex, INFINITE);
            Sleep(hthandle->shared->secSnapshotInterval * 1000);
            if(!hthandle->fixed) {
                Snap(hthandle);
                hthandle->fixed = true;
            }
            ReleaseMutex(mutex);
        }
        return 0;
    }
}
