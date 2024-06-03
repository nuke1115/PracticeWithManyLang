#pragma once

#ifndef QueueHeader
#define QueueHeader
#include "LinkedList.h"
#include <limits>
using namespace std;

template<class T>
class Queue
{
private:
	long long _count = 0;
	long long _maxCount = numeric_limits<long long>::max();
	SinglyLinkedList<T> _internalList = SinglyLinkedList<T>();
	bool _isEmpty = true;
public:
	Queue()
	{}
	~Queue()
	{

	}

	void Enqueue(T item)
	{
		if (_count == _maxCount)
		{
			puts("Queue is FULL!");
			return;
		}
		_internalList.AddLast(item);
		_count++;
		_isEmpty = false;
	}

	T Dequeue()
	{
		T tmp{};
		if (_isEmpty || _count == 0)
		{
			puts("Queue is EMPTY!");
			_isEmpty = true;
			return tmp;
		}
		_count--;
		return _internalList.GetAndDeleteFirst();
	}

	T Peek()
	{
		T tmp{};
		if (_isEmpty || _count == 0)
		{
			puts("Queue is EMPTY!");
			_isEmpty = true;
			return tmp;
		}
		return _internalList.GetFirst();
	}

	void Clear()
	{
		_internalList.ClearList();
		_count = 0;
		_isEmpty = true;
	}

	long long GetCount()
	{
		return _count;
	}

	bool IsEmpty()
	{
		return _isEmpty;
	}

	bool IsItContains(T item)
	{
		if (_isEmpty)
		{
			puts("Queue is EMPTY");
			return false;
		}
	
		return _internalList.IsItContains(item);
	}


};


#endif // !QueueHeader
/*
todo:
add find function (also LinkedList.h too)
*/
