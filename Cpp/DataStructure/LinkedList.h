#pragma once

#ifndef LinkedListHeader
#define LinkedListHeader



#include <stdio.h>


template<class T>
class LinkedList//전체적으로 코드 최적화하기
{
private:

    struct Node
    {
        T data;
        Node* next = nullptr;
    };

    Node* _head = nullptr;
    Node* _nodePointer = nullptr;
    Node* _prevNodePointer = nullptr;
    long long _count = 0;
    bool _isEmpty = true;
public:
    LinkedList()
    {
    }

    ~LinkedList()
    {
        ClearList();
    }

    void ClearList()
    {
        _nodePointer = _head;

        while (_nodePointer != nullptr)
        {
            _prevNodePointer = _nodePointer;
            _nodePointer = _nodePointer->next;
            delete _prevNodePointer;
        }

        _head = nullptr;
        _nodePointer = nullptr;
        _prevNodePointer = nullptr;
        _count = 0;
        _isEmpty = true;
    }

    void AddFirst(T item)
    {
        if (_head == nullptr && _isEmpty)
        {
            _head = new Node;
            _isEmpty = false;
            _head->data = item;
        }
        else
        {
            Node* newHead = new Node;
            newHead->next = _head;
            _head = nullptr;
            _head = newHead;
            _head->data = item;
        }
        _count++;
    }

    void AddLast(T item)
    {

        if (_head == nullptr && _isEmpty)
        {
            _head = new Node;
            _isEmpty = false;
            _nodePointer = _head;
        }
        else
        {
            _nodePointer = _head;
            while (_nodePointer->next != nullptr)
            {
                _nodePointer = _nodePointer->next;
            }
            _nodePointer->next = new Node;
            _nodePointer = _nodePointer->next;
        }

        _nodePointer->data = item;
        _nodePointer = nullptr;
        _count++;
    }

    void AddAfter(T item, long long index)
    {
        if (index >= _count)
        {
            puts("index is greater than List's length");
            return;
        }

        _nodePointer = _head;
        for (int cnt = 0; cnt <= index; cnt++)
        {
            _prevNodePointer = _nodePointer;
            _nodePointer = _nodePointer->next;
        }

        Node* newNode = new Node;
        newNode->next = _nodePointer;
        _prevNodePointer->next = newNode;
        newNode->data = item;

        _nodePointer = nullptr;
        _prevNodePointer = nullptr;
        _count++;
    }

    T GetAndDeleteFirst()
    {
        T tmp{};

        tmp = GetFirst();
        DeleteFirst();

        return tmp;
    }

    T GetFirst()
    {
        T tmp{};
        _nodePointer = _head;
        if (_head == nullptr && _isEmpty)
        {
            puts("List is EMPTY!");
        }
        else
        {
            tmp = _head->data;
        }

        return tmp;
    }

    void DeleteFirst()
    {
        if (_head != nullptr && !_isEmpty)
        {
            _nodePointer = _head->next;
            delete _head;
            _head = nullptr;
            _head = _nodePointer;
            _nodePointer = nullptr;
            _count--;
        }
        else
        {
            puts("List is EMPTY!");
        }
    }

    T GetAndDeleteAt(long long index)
    {
        T tmp{};

        tmp = GetAt(index);
        DeleteAt(index);

        return tmp;
    }

    void DeleteAt(long long index)
    {
        if (index >= _count)
        {
            puts("List is EMPTY or index is greater than List's length");
            return;
        }

        _nodePointer = _head;

        for (int cnt = 0; cnt < index; cnt++)
        {
            _prevNodePointer = _nodePointer;
            _nodePointer = _nodePointer->next;
        }

        if (_head->next == nullptr)
        {
            _head = nullptr;
            _isEmpty = true;
        }
        else
        {
            _prevNodePointer->next = _nodePointer != nullptr ? _nodePointer->next : nullptr;
        }

        delete _nodePointer;
        _nodePointer = nullptr;
        _prevNodePointer = nullptr;
        _count--;
    }

    T GetAt(long long index)
    {
        T tmp{};
        if (index >= _count)
        {
            puts("List is EMPTY or index is greater than List's length");
            return tmp;
        }

        _nodePointer = _head;

        for (int cnt = 0; cnt < index; cnt++)
        {
            _nodePointer = _nodePointer->next;
        }

        tmp = _nodePointer->data;

        _nodePointer = nullptr;
        return tmp;
    }

    T GetAndDeleteLast()
    {
        T tmp{};
        tmp = GetLast();
        DeleteLast();

        return tmp;
    }

    T GetLast()
    {

        T tmp{};
        if (_head != nullptr)
        {
            _nodePointer = _head;
            while (_nodePointer->next != nullptr)
            {
                _nodePointer = _nodePointer->next;
            }
            tmp = _nodePointer->data;
        }
        else
        {
            puts("List Is Empty");
        }
        return tmp;
    }

    void DeleteLast()
    {

        if (_head != nullptr && !_isEmpty)
        {
            _nodePointer = _head;
            while (_nodePointer->next != nullptr)
            {
                _prevNodePointer = _nodePointer;
                _nodePointer = _nodePointer->next;
            }

            if (_nodePointer == _head)
            {
                _head = nullptr;
                _isEmpty = true;
            }

            if (_prevNodePointer != nullptr)
            {
                _prevNodePointer->next = nullptr;
            }

            delete _nodePointer;
            _nodePointer = nullptr;
            _count--;
        }
        else
        {
            puts("List Is Empty");
        }

    }

    bool IsEmpty()
    {
        return _isEmpty;
    }

    long long GetCount()
    {
        return _count;
    }
};

#endif // !LinkedList

/*

문제 발생 및 해결 기록:

1:GetAndDeleteLast함수를 두번 이상 실행했을떄, 포인터가 null pointer 오류를 일으키는 현상
원인:Node를 삭제하는 과정에서, 삭제되는 노드를 가르키고있던 이전 노드의 _next포인터를 nullptr로 설정하지 않았고, 그것이 반복문에서 _nodePointer에 삭제된 노드의 주소값이 남아있었다

해결:
_prevNodePointer를 추가해서, 노드 삭제 작업시에, _prevNodePointer에 저장된 노드에 접근해서 _next 포인터를 nullptr로 초기화했다

2:
addfirst 를 시행했을때, Node의 값이 정상적으로 출력되지 않음
이유:AddLast함수에서 리스트가 비어있는지 확인하고 할당하는 부분에서
조건문이 하나가 실행되면 다른것이 실행되지 않는 구조가 아닌, 두개 다 실행되는 구조로 작성되있었고,
만약, 비어있다가 참이어서 비어있을떄 작동되는 조건문이 작동하고나서, 그 조건문에서 비어있다가 거짓이 되어서, 그 이후에 있던 비어있다가 거짓일때 실행되는 조건문이 중복으로 작동되어서
할당이 이중으로 됬었다

해결: if - if로 따로 되있었던 조건문을, if-else형태로 수정함

*/
//TODO : 메모리 누수 체크
