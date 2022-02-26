//
// Created by Skvortsoff on 2/14/2022.
//
#pragma once
#include "windows.h"
#include "HANDLE.h"
#include "Element.h"

namespace HT{

    EXPORT_DLL
    Element * Get(HTHANDLE *, Element *);

    EXPORT_DLL
    BOOL Insert(HTHANDLE * hthandle, Element * element);

    EXPORT_DLL
    BOOL Delete(HTHANDLE * hthandle, Element * element);

    EXPORT_DLL
    BOOL Update(HTHANDLE * hthandle, Element * element);

    EXPORT_DLL
    BOOL Snap(HTHANDLE * hthandle);
}