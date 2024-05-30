#pragma once


#ifndef DYNAMIC_ARRAY_HEADER
#define DYNAMIC_ARRAY_HEADER
#include <cstddef>
#include <corecrt_malloc.h>


void InitArray(struct DynamicArray& dArray, int arrSize);
void SetData(struct DynamicArray& dArray, int index, int data);
int GetData(struct DynamicArray& dArray, int index);
void DeleteArray(struct DynamicArray& dArray);
void ResizeArray(struct DynamicArray& dArray, int newSize);

struct DynamicArray
{
    int* data = NULL;
    int size = 0;

    void (*FuncInitArray)(DynamicArray&, int) = InitArray;
    void (*FuncSetData)(DynamicArray&, int, int) = SetData;
    int (*FuncGetData)(DynamicArray&, int) = GetData;
    void (*FuncDeleteArray)(DynamicArray&) = DeleteArray;
    void (*FuncResizeArray)(DynamicArray&, int) = ResizeArray;
};

void InitArray(struct DynamicArray& dArray, int arrSize)
{

    if (dArray.data != NULL)
    {
        return;
    }

    int* tmpArrPtr = (int*)malloc(sizeof(int) * arrSize);
    dArray.data = tmpArrPtr;
    dArray.size = arrSize;

    if (tmpArrPtr == NULL || arrSize < 0)
    {
        return;
    }

    for (int i = 0; i < arrSize; i++)
    {
        *tmpArrPtr = 0;
        tmpArrPtr++;
    }
}

void DeleteArray(struct DynamicArray& dArray)
{
    if (dArray.data == NULL)
    {
        return;
    }

    free(dArray.data);
    dArray.data = NULL;
    dArray.size = 0;
}


void SetData(struct DynamicArray& dArray, int index, int data)
{
    if (index >= dArray.size || dArray.data == NULL || index < 0)
    {
        return;
    }

    int* tmpArrPtr = dArray.data;
    tmpArrPtr += index;
    *tmpArrPtr = data;

}

int GetData(struct DynamicArray& dArray, int index)
{
    if (index >= dArray.size || dArray.data == NULL || index < 0)
    {
        return -1;
    }

    int* tmpArrPtr = dArray.data;
    tmpArrPtr += index;
    return *tmpArrPtr;
}

void ResizeArray(struct DynamicArray& dArray, int newSize)
{
    if (dArray.data == NULL)
    {
        return;
    }


    int* tmpNewArrPtr = (int*)malloc(sizeof(int) * newSize);
    if (tmpNewArrPtr == NULL)
    {
        return;
    }
    int* tmpNewArrMovablePtr = tmpNewArrPtr;
    int* tmpOldArrPtr = dArray.data;
    int* tmpOldArrPtrMovable = tmpOldArrPtr;

    for (int i = 0; i < newSize; i++)
    {
        *tmpNewArrMovablePtr = dArray.size > i ? *tmpOldArrPtrMovable : 0;
        tmpNewArrMovablePtr++;
        tmpOldArrPtrMovable += dArray.size > i ? 1 : 0;
    }

    free(tmpOldArrPtr);

    dArray.size = newSize;
    dArray.data = tmpNewArrPtr;
}
#endif // !DYNAMIC_ARRAY_HEADER
