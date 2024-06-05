#pragma once

#ifndef StackHeader
#define StackHeader


template<class T>
class Stack
{
private:
	long _count = -1;
	long _nowMaxCount = 0;
	T defaultValue{};
	const long _maxCount = 1000000001;
	const int _increaseNum = 2;
	bool _IsEmpty = true;
	bool _AutoResizeOption = false;
	T* _internalArray = nullptr;


	void IncreaseStack()
	{
		if (_nowMaxCount*_increaseNum <= _maxCount)
		{
			_nowMaxCount*= _increaseNum;
			ResizeStack(_nowMaxCount);
		}
		else if (_nowMaxCount + (_nowMaxCount/2) <= _maxCount)
		{
			_nowMaxCount += (_nowMaxCount / 2);
			ResizeStack(_nowMaxCount);
		}
		else if (_nowMaxCount + _increaseNum <= _maxCount)
		{
			_nowMaxCount += _increaseNum;	
		}
		else
		{
			puts("stack is full");
			return;
		}
	}

public:
	Stack(long baseSize, bool AutoResizeOption)
	{

		if (baseSize > _maxCount )
		{
			puts("base size is too big");
			return;
		}
		
		if (baseSize <= 0)
		{
			puts("new size is smaller than minimum size");
			return;
		}

		_nowMaxCount = baseSize;
		_internalArray = new T[_nowMaxCount];

		_AutoResizeOption = AutoResizeOption;
	}

	~Stack()
	{
		delete[] _internalArray;
	}

	void Clear()
	{
		_count = -1;
	}

	void Push(T item)
	{
		if (_count >= _nowMaxCount - 1)
		{
			if (_AutoResizeOption)
			{
				IncreaseStack();
			}
			else
			{
				puts("stack is full");
				return;
			}
		}

		_IsEmpty = false;

		_count++;
		_internalArray[_count] = item;
	}

	void ResizeStack(long newSize)
	{
		T* newArray = new T[newSize];
		
		if (newSize < 0)
		{
			puts("new size is smaller than minimum size");
			return;
		}

		if (_count >= newSize)
		{
			_count = newSize - 1;
		}

		for (long i = 0; i < newSize; i++)
		{
			if (i < _nowMaxCount)
			{
				newArray[i] = _internalArray[i];
			}
			else
			{
				newArray[i] = defaultValue;
			}
		}

		if (newSize == 0)
		{
			_IsEmpty = false;
		}

		_nowMaxCount = newSize;

		delete[] _internalArray;
		_internalArray = nullptr;
		_internalArray = newArray;
	}

	T Pop()
	{

		if (_IsEmpty)
		{
			puts("stack is empty");
			return defaultValue;
		}

		T tmp = _internalArray[_count];

		_count--;

		if (_count < 0)
		{
			_IsEmpty = true;
		}

		return tmp;

	}

	T Peek()
	{
		if (_IsEmpty)
		{
			puts("stack is empty");
			return defaultValue;
		}

		return _internalArray[_count];
	}

	bool IsStackEmpty()
	{
		return _IsEmpty;
	}

	long GetCount()
	{
		return _count + 1;
	}

	bool IsItContains(T item)
	{
		if (_IsEmpty)
		{
			puts("stack is empty");
			return false;
		}

		for (long i = 0; i <= _count; i++)
		{
			if (_internalArray[i] == item)
			{
				return true;
			}
		}

		return false;
	}

};



#endif // !StackHeader
