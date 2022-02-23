//
// Created by Skvortsoff on 2/14/2022.
//
#include <iostream>
#include "windows.h"
#include "HANDLE.h"
#include "Element.h"

namespace HT{

    BOOL Insert(HTHANDLE * hthandle, Element * element) {

        try {
            if (hthandle->shared->currentCapacity >= hthandle->shared->capacity)
                throw std::runtime_error("Map is full");

            WaitForSingleObject(hthandle->mutex, INFINITE);
            auto hash = Hash(hthandle, (const char *) element->key);

            for (auto i = 0; i != hthandle->shared->capacity; i++) {
                auto temp = (Element*)hthandle->Offset(hash);

                if (temp->key == nullptr) {
                    hthandle->shared->currentCapacity++;
                    temp->RecordToMap(hthandle, element);
                    hthandle->PrintCurrentSize();
                    hthandle->fixed = false;
                    break;
                } else {
                    temp->PointerCorrecting(hthandle->shared->maxKeyLength);
                    if (strcmp((char *) element->key, (char*)temp->key) == 0) {
                        throw std::runtime_error("Element is exist");
                    }
                }
                hash = HashNext(hash, hthandle->shared->capacity, i);
            }

        } catch (std::runtime_error & error) {
            ReleaseMutex(hthandle->mutex);
            strcpy(hthandle->lastErrorMessage, error.what());
            return FALSE;
        }
        ReleaseMutex(hthandle->mutex);
        return TRUE;
    }

    Element * Get(HTHANDLE * hthandle, Element * element){
        auto hash = Hash(hthandle, (const char*)element->key);
        Element * temp;

        WaitForSingleObject(hthandle->mutex, INFINITE);

        try {
            for (auto i = 0; i != hthandle->shared->capacity; i++) {
                temp = (Element *) hthandle->Offset(hash);

                if (temp->key != nullptr) {
                    temp->PointerCorrecting(hthandle->shared->maxKeyLength);
                    if (strcmp((char *) temp->key, (char *) element->key) == 0) {
                        ReleaseMutex(hthandle->mutex);
                        return temp;
                    }
                }
                hash = HashNext(hash, hthandle->shared->capacity, i);
            }
            throw std::runtime_error("Element not found");

        } catch (std::runtime_error & error) {
            ReleaseMutex(hthandle->mutex);
            strcpy(hthandle->lastErrorMessage, error.what());
            return nullptr;
        }
    }

    BOOL Update(HTHANDLE * hthandle, Element * element){
        auto * elem = Get(hthandle, element);

        try {
            if(elem == nullptr)
                throw std::runtime_error("Element not found");

            WaitForSingleObject(hthandle->mutex, INFINITE);
            elem->payloadLength = element->payloadLength;
            strcpy_s((char *) elem->payload, element->payloadLength + 1, (char *) element->payload);
            hthandle->fixed = false;
            return TRUE;
        } catch (std::runtime_error & error) {
            ReleaseMutex(hthandle->mutex);
            strcpy(hthandle->lastErrorMessage, error.what());
            return FALSE;
        }
    }

    BOOL Delete(HTHANDLE * hthandle, Element * element){
        auto * elem = Get(hthandle, element);

        try {
            if(elem == nullptr)
                throw std::runtime_error("Element not found");

            WaitForSingleObject(hthandle->mutex, INFINITE);

            elem->key = nullptr;
            hthandle->shared->currentCapacity--;
            hthandle->fixed = false;
            ReleaseMutex(hthandle->mutex);
            return TRUE;
        } catch (std::runtime_error & error) {
            ReleaseMutex(hthandle->mutex);
            strcpy(hthandle->lastErrorMessage, error.what());
            return FALSE;
        }

    }

}