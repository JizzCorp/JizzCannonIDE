#include"dynList.h"

static size_t getElementSize(const DynListTypes type) {
  
  size_t typeSize = 0;

  switch (type) {
    // case DL_INT:
      // typeSize = sizeof(int);
      // break;
//
    // case DL_FLOAT:
      // typeSize = sizeof(float);
      // break;

    case DL_WIDGET:
      typeSize = sizeof(BaseWidget);
      break;
  }

  return typeSize;

}

static void pushElement(DynList *list, void* value, size_t index) {

  switch (list->listType) {
    // case DL_INT:
      // ((int*)list->actualData)[index] = *(int*)value;
      // break;
//
    // case DL_FLOAT:
      // ((float*)list->actualData)[index] = *(float*)value;
      // break;

    case DL_WIDGET:
      ((BaseWidget*)list->actualData)[index] = *(BaseWidget*)value;
      break;

  }
}

static void swapElements(DynList *list, const size_t hostIndex, const size_t guestIndex) {
  
  switch (list->listType) {
    // case DL_INT:
      // int tmpValue = ((int*)list->actualData)[hostIndex];
      // ((int*)list->actualData)[hostIndex] = ((int*)list->actualData)[guestIndex];
      // ((int*)list->actualData)[guestIndex] = tmpValue;
      // break;
//
    // case DL_FLOAT:
          // break;

    case DL_WIDGET:
          BaseWidget tmpValue = ((BaseWidget*)list->actualData)[hostIndex];
          ((BaseWidget*)list->actualData)[hostIndex] = ((BaseWidget*)list->actualData)[guestIndex];
          ((BaseWidget*)list->actualData)[guestIndex] = tmpValue;
          break;

  }

}

void restoreListOrder(DynList *list, const size_t poppedIndex) {

  switch (list->listType) {
    // case DL_INT:
      // int tmpValue = ((int*)list->actualData)[poppedIndex];
      // for (size_t i = poppedIndex; i < list->usedSlots - 1; ++i) {
        // ((int*)list->actualData)[i] = ((int*)list->actualData)[i + 1];
      // }
      // ((int*)list->actualData)[list->usedSlots-1] = tmpValue;
      // break;
//
    // case DL_FLOAT:
      // break;
    
    case DL_WIDGET:
      BaseWidget tmpValue = ((BaseWidget*)list->actualData)[poppedIndex];
      for (size_t i = poppedIndex; i < list->usedSlots - 1; ++i) {
        ((BaseWidget*)list->actualData)[i] = ((BaseWidget*)list->actualData)[i+1];
      }
      ((BaseWidget*)list->actualData)[list->usedSlots-1] = tmpValue;
      break;
  }
  
}

DynList dynListInit(const DynListTypes listType, const size_t listSize) {
  
  size_t elementSize = getElementSize(listType);

  void *dataPtr = calloc(listSize, elementSize);
  
  if (dataPtr == NULL) {
    DynList errorList = {listType, elementSize, listSize, 0, NULL, 1};
    return errorList;
  }

  DynList newList = {listType, elementSize, listSize, 0, dataPtr, 0};

  return newList;
}

void dynListFree(DynList *list) {
  free(list->actualData);
}

size_t dynListLen(const DynList *list) {

  return list->usedSlots;

}

void dynListPush(DynList *list, void* value) {

  if (list->usedSlots < list->listSize) {
    pushElement(list, value, list->usedSlots);
    ++list->usedSlots;
    return;
  }
  
  size_t newMemSize = (list->usedSlots + 1) * list->elementSize;
  void* newMemPtr = realloc(list->actualData, newMemSize);

  if (newMemPtr == NULL) {
    list->errno = 2;
    return;
  }
  
  list->actualData = newMemPtr;
  pushElement(list, value, list->usedSlots);
  ++list->usedSlots;

  return;
}

void dynListPop(DynList *list, const size_t index) {
  if (index > list->usedSlots || index < 0) {
    list->errno = DL_INDEX_OUT_OF_BOUNDS;
  }
  
  if (list->usedSlots - 1 != index) {
    swapElements(list, index, list->usedSlots - 1);
  }

  --list->usedSlots;
  
  size_t newMemSize = list->usedSlots * list->elementSize;
  void *newMemPtr = realloc(list->actualData, newMemSize);
  
  if (newMemPtr == NULL) {
    list->errno = DL_REALLOC_FAILED_ON_POP;
    return;
  }
  
  list->actualData = newMemPtr;
  
  restoreListOrder(list, index);
}

char* dynListGetError(DynList *list, const short int errno) {
  
  list->errno = 0;

  switch (errno) {
    case DL_NO_ERROR:
      return "No Error";

    case DL_CALLOC_FAILED_ON_INIT:
      return "Calloc failed on init";
  
    case DL_REALLOC_FAILED_ON_PUSH:
      return "Realloc failed on push";

    case DL_INDEX_OUT_OF_BOUNDS:
      return "Specified index is out of bounds";

    default:
      return "Generic Error";
  }
  
}

void dynListPrint(const DynList *list) {
  
  switch (list->listType) {
    // case DL_INT:
      // for (size_t i = 0; i < list->usedSlots; ++i) {
        // printf("Cell value at %zu: %d\n", i, ((int*)list->actualData)[i]);
      // }
      // break;
//
    // case DL_FLOAT:
      // break;

    case DL_WIDGET:
      break;
  }

}
