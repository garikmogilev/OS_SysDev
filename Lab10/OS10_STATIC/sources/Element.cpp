//
// Created by Skvortsoff on 2/14/2022.
//
#include "../headers/Element.h"

namespace HT{

    __attribute__((unused))
    Element::Element(const void *key, int keyLength) {
        this->key = key;
        this->keyLength = keyLength;
        this->payload = nullptr;
        this->payloadLength = 0;
    }

    __attribute__((unused))
    Element::Element(const void *key, int keyLength, const void *payload, int payloadLength) {
        this->key = key;
        this->keyLength = keyLength;
        this->payload = payload;
        this->payloadLength = payloadLength ;
    }

    __attribute__((unused))
    Element::Element(Element *oldElement, const void *payload, int payloadLength) {
        this->key = oldElement->key;
        this->keyLength = oldElement->keyLength;
        this->payload = payload;
        this->payloadLength = payloadLength;
    }

    __attribute__((unused))
    Element::Element(){
        this->keyLength = 0;
        this->key = nullptr;
        this->payloadLength = 0;
        this->payload = nullptr;
    }

    void Element::RecordToMap(HTHANDLE * ht, Element * element) {
        this->keyLength = element->keyLength;
        this->payloadLength = element->payloadLength;
        PointerCorrecting(ht->shared->maxKeyLength);
        strcpy_s((char*)this->key, this->keyLength + 1, (const char*)element->key);
        strcpy_s((char*)this->payload, this->payloadLength + 1, (const char*)element->payload);
    };

    void Element::PointerCorrecting(int maxKeyLength){
        this->key = (char*)this + sizeof(Element);
        this->payload = (char*)this + sizeof(Element) + maxKeyLength;
    }
}
