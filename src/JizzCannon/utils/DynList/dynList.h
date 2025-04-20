#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#include<stdio.h>
#include<stdlib.h>

#include"../../widgets/button.h"

typedef enum DynListErrors {
  DL_NO_ERROR,
  DL_CALLOC_FAILED_ON_INIT,
  DL_REALLOC_FAILED_ON_PUSH,
  DL_REALLOC_FAILED_ON_POP,
  DL_INDEX_OUT_OF_BOUNDS,
} DynListErrors;

typedef enum DynListTypes {
  // DL_INT,
  // DL_FLOAT,
  DL_WIDGET
} DynListTypes;

typedef struct DynList {
  
  DynListTypes listType;
  size_t elementSize;
  size_t listSize;
  size_t usedSlots;
  void* actualData;

  short int errno;
} DynList;

DynList dynListInit(DynListTypes listType, const size_t listSize);
void dynListFree(DynList *list);

size_t dynListLen(const DynList *list);

void dynListPush(DynList *list, void* value);
void dynListPop(DynList *list, const size_t index);

char* dynListGetError(DynList *list, const short int errno);

void dynListPrint(const DynList *list);
#endif
