#include "windows.h"
#define MAX_SIZE_ERROR 512
#include <iostream>
#include <stdexcept>
#include <string_view>

namespace HT{
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

        HTHANDLE
                (
                        int capacity,
                        int secSnapshotInterval,
                        int maxKeyLength,
                        int maxPayLoadLength,
                        const char fileName[512]
                );

        [[nodiscard]] static int AlignmentMemory(int sizeElement, int maxKeyLength, int maxPayLoadLength) ;
        [[nodiscard]] LPVOID Offset(unsigned int index) const;
        void PrintCurrentSize() const;

    };

    [[nodiscard]]
    HTHANDLE * Create(
            int capacity,
            int secSnapshotInterval,
            int maxKeyLength,
            int maxPayLoadLength,
            const char fileName[512]
    );
    HTHANDLE * Open(const char fileName[512]);

    [[nodiscard]]
    unsigned int Hash(HTHANDLE *,const char *);
    [[nodiscard]]
    unsigned int HashNext(unsigned int hash,unsigned int size,unsigned int i);

    void Print(HTHANDLE *);
    [[nodiscard]]
    BOOL Close(HTHANDLE *);
    void GetLastError(HTHANDLE *);
    [[nodiscard]]
    DWORD WINAPI SnapThread(HTHANDLE *);

    struct Element {
        int keyLength;          // size key
        int payloadLength;      // size data
        const void * key;        // value key
        const void * payload;    // data

        Element();

        Element(const void *key, int keyLength);

        Element(const void *key, int keyLength, const void *payload, int payloadLength);

        Element(Element *oldElement, const void *payload, int payloadLength);

        void RecordToMap(HTHANDLE *ht, Element *element);

        void PointerCorrecting(int maxKeyLength);

    };

    Element * Get(HTHANDLE *, Element *);
    BOOL Insert(HTHANDLE * hthandle, Element * element);
    BOOL Delete(HTHANDLE * hthandle, Element * element);
    BOOL Update(HTHANDLE * hthandle, Element * element);
    BOOL Snap(HTHANDLE * hthandle);

}
