//
// Created by Skvortsoff on 2/14/2022.
//
#include "HANDLE.h"

namespace HT {
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
}