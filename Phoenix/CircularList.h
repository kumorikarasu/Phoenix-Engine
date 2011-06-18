/*
(c) Sean Stacey, Feb 16 2011
Templated Circular Linked List

Used with the garbage collector in the PhoenixEngine

Under LGPL 

Note :: NOT THREAD SAFE ::
*/

#ifndef _CIRCULARLIST_H_
#define _CIRCULARLIST_H_

#ifndef NULL
#define NULL 0
#endif

template <class _Ty>
class CircularNode
{
private:
  CircularNode* next;
  CircularNode* prev;
  _Ty* Data;
  bool Modified;

  template<typename _Ty> friend class CircularList;
  template<typename _Ty> friend class Iterator;

  CircularNode(_Ty* Data)
  {
    this->Data = Data;
    next = NULL;
    prev = NULL;
  }
};


template <class _Ty>
class Iterator
{
private:
  CircularNode<_Ty>* node;

  template<typename _Ty> friend class CircularList;

public:
  Iterator operator++ (int)
  {
    node = node->next;
    return (*this);
  }

  Iterator operator++ ()
  {
    node = node->next;
    return (*this);
  }

  Iterator operator-- (int)
  {
    node = node->prev;
    return (*this);
  }

  Iterator operator-- ()
  {
    node = node->prev;
    return (*this);
  }

  _Ty* operator* ()
  {
    if (node != NULL)
      return node->Data;
    else
      return NULL;
  }

  _Ty* operator-> ()
  {
    if (node != NULL)
      return node->Data;
    else
      return NULL;
  }

  bool Modified()
  {
    return node->Modified;
  }

};

template<typename _Ty>
class CircularList
{
private:
  CircularNode<_Ty>* List;
  int objCount;

public:
  typedef Iterator<_Ty> iterator;

  CircularList()
  {
    List = NULL;
    objCount = 0;
  }

  iterator GetIterator()
  {
    iterator it;
    it.node = List;
    return it;
  }

  int Add(_Ty* Data)
  {
    if (Data == NULL)
      return -1;

    if (List == NULL){
      List = new CircularNode<_Ty>(Data);
      List->next = List;
      List->prev = List;
    }else{
      CircularNode<_Ty>* it = new CircularNode<_Ty>(Data);
      it->prev = List->prev;
      List->prev->next = it;
      it->next = List;
      List->prev = it;
    }
    List->Modified = true;

    return ++objCount;
  }

  void Destroy()
  {
    while (List != NULL){
      iterator it = GetIterator();
      this->Remove(it);
    }
    objCount = 0;
  }

  Iterator<_Ty>& Remove(Iterator<_Ty>& it)
  {
    if (!List->Modified)
      return it;
    List->Modified = true;

    if (it.node->Data == NULL)
      return it;

    CircularNode<_Ty>* node = it.node;
    CircularNode<_Ty>* i = node;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node = node->next;
    if (node == node->next){
      it.node = NULL;
      List = NULL;
    }

    delete i;

    --objCount;
    return it;
  }

  int Empty()
  {
    return objCount;
  }
};

#endif