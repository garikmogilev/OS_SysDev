//
// Created by Skvortsoff on 2/7/2022.
//
#pragma once
#include "windows.h"
#define MAX_SIZE_ERROR 512
#define EXPORT_DLL __declspec(dllexport)

namespace HT {

    struct Thread {
        DWORD ID {};
        HANDLE handle {};
    };

    struct BetweenProcessMemory{                    // between memory process for second or more
        int currentCapacity{};                      // current capacity
        int sizeElement{};                          // size ELEMENT
        int capacity{};                             // capacity
        int maxKeyLength{};                         // max length key
        int maxPayLoadLength{};                     // max length value
        int secSnapshotInterval{};                  // period save to disk
        int sizeMap{};
        BetweenProcessMemory();                     // default constructor
        BetweenProcessMemory(int sizeElement, int capacity, int maxKeyLength, int maxPayLoadLength);
    };

    struct HTHANDLE {
        const char * fileName{};
        HANDLE file{};
        HANDLE fileMapping{};
        LPVOID address{};
        BetweenProcessMemory * shared;
        volatile  bool exit = false;
        volatile  bool fixed = true;
        Thread threadSnap;
        HANDLE mutex{};
        HTHANDLE();
        char lastErrorMessage[MAX_SIZE_ERROR]{};

        EXPORT_DLL
        HTHANDLE
        (
                int capacity,
                int secSnapshotInterval,
                int maxKeyLength,
                int maxPayLoadLength,
                const char fileName[512]
        );

        static int AlignmentMemory(int sizeElement, int maxKeyLength, int maxPayLoadLength) ;

        LPVOID Offset(unsigned int index) const;

        EXPORT_DLL
        void PrintCurrentSize() const;

    };

    EXPORT_DLL
    HTHANDLE * Create(
            int capacity,
            int secSnapshotInterval,
            int maxKeyLength,
            int maxPayLoadLength,
            const char fileName[512]
    );

    EXPORT_DLL
    HTHANDLE * Open(const char fileName[512]);

    unsigned int Hash(HTHANDLE *,const char *);
    unsigned int HashNext(unsigned int hash,unsigned int size,unsigned int i);

    EXPORT_DLL
    void PrintAll(HTHANDLE *);

    EXPORT_DLL
    void Print(void *);

    EXPORT_DLL
    BOOL Close(HTHANDLE *);

    EXPORT_DLL
    const char *  GetLastError(HTHANDLE *);

    EXPORT_DLL
    DWORD WINAPI SnapThread(HTHANDLE *);
}
