//
// Created by Skvortsoff on 2/14/2022.
//
#pragma once
#include "windows.h"
#include "HANDLE.h"
#include "Element.h"

namespace HT{
    Element * Get(HTHANDLE *, Element *);
    BOOL Insert(HTHANDLE * hthandle, Element * element);
    BOOL Delete(HTHANDLE * hthandle, Element * element);
    BOOL Update(HTHANDLE * hthandle, Element * element);
    BOOL Snap(HTHANDLE * hthandle);
}