#pragma once

#ifndef LinkedListHeader
#define LinkedListHeader



#include <stdio.h>

struct Node
{
    int data;
    Node* next = nullptr;
};

class LinkedList//��ü������ �ڵ� ����ȭ�ϱ�
{
private:

    Node* _head = nullptr;
    Node* _nodePointer = nullptr;
    Node* _prevNodePointer = nullptr;
    size_t _count = 0;
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

    void AddFirst(int item)
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

    void AddLast(int item)
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

    void AddAfter(int item, size_t index)
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

    int GetAndDeleteFirst()
    {
        int tmp = -1;

        tmp = GetFirst();
        DeleteFirst();

        return tmp;
    }

    int GetFirst()
    {
        int tmp = -1;
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

    int GetAndDeleteAt(size_t index)
    {
        int tmp = -1;

        tmp = GetAt(index);
        DeleteAt(index);

        return tmp;
    }

    void DeleteAt(size_t index)
    {
        if (index >= _count)
        {
            puts("List is EMPTY or index is greater than List's length");
            return;
        }

        _nodePointer = _head;

        for (int cnt = 0; cnt <= index; cnt++)
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

    int GetAt(size_t index)
    {
        int tmp = -1;
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

    int GetAndDeleteLast()
    {
        int tmp = -1;
        tmp = GetLast();
        DeleteLast();

        return tmp;
    }

    int GetLast()
    {

        int tmp = -1;
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

    size_t GetCount()
    {
        return _count;
    }
};

#endif // !LinkedList

/*

���� �߻� �� �ذ� ���:

1:GetAndDeleteLast�Լ��� �ι� �̻� ����������, �����Ͱ� null pointer ������ ����Ű�� ����
����:Node�� �����ϴ� ��������, �����Ǵ� ��带 ����Ű���ִ� ���� ����� _next�����͸� nullptr�� �������� �ʾҰ�, �װ��� �ݺ������� _nodePointer�� ������ ����� �ּҰ��� �����־���

�ذ�:
_prevNodePointer�� �߰��ؼ�, ��� ���� �۾��ÿ�, _prevNodePointer�� ����� ��忡 �����ؼ� _next �����͸� nullptr�� �ʱ�ȭ�ߴ�

2:
addfirst �� ����������, Node�� ���� ���������� ��µ��� ����
����:AddLast�Լ����� ����Ʈ�� ����ִ��� Ȯ���ϰ� �Ҵ��ϴ� �κп���
���ǹ��� �ϳ��� ����Ǹ� �ٸ����� ������� �ʴ� ������ �ƴ�, �ΰ� �� ����Ǵ� ������ �ۼ����־���,
����, ����ִٰ� ���̾ ��������� �۵��Ǵ� ���ǹ��� �۵��ϰ���, �� ���ǹ����� ����ִٰ� ������ �Ǿ, �� ���Ŀ� �ִ� ����ִٰ� �����϶� ����Ǵ� ���ǹ��� �ߺ����� �۵��Ǿ
�Ҵ��� �������� �����

�ذ�: if - if�� ���� ���־��� ���ǹ���, if-else���·� ������

*/
//TODO : �޸� ���� üũ
