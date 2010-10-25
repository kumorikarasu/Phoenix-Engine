//MUST WRITE CLASS FACTORY SYSTEM THAT USES CACHING, ONLY THEN WILL I BE PRO

#pragma once
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

/*	- Linked Lists -


    - Functions -

    Constructor - creates the first node for the system
    Destructor - Clears the list (deleting everything inside), then deletes itself
    first (void) - returns the first node* in the list
    add (object) - Adds a new object to the end of the list.
    remove (node) - deletes the object at the specified node and moves the list back, returns the previous node, or the first node in list
    clear (void) - deletes everything inside of the list

    - usage syntax -
    Node = list->first();
    while(Node!=NULL){
    object = Node->object;
    object -> step(); //the objects reoccuring event
    if (object->isDead) //deadflag set?
    delete object;
    Node = list->remove(Node);
    Node = Node -> next;
    }
    */

template <class _Ty>
class Node
{

  private:
    template <class _Ty> friend class LinkedList; //allows the list to access private variables
    Node* pNext;
    Node* pPrev;
    _Ty* pObject;

  public:

    Node<_Ty>()
    {
      pNext=NULL;
      pPrev=NULL;
      pObject=NULL;
    }

    _Ty* getObject(){return pObject;}
    Node* getNext(){return pNext;}
    Node* getPrev(){return pPrev;}

    //TODO overload ++ operator to goto next element

};

template <class _Ty>
class LinkedList
{
  private:
    Node<_Ty>* pHead;
    Node<_Ty>* pTail;
    int m_nSize;
  public:

    LinkedList()
    {
      Init();
    }

    ~LinkedList()
    {
      clear();
    }

    void Init()
    {
      pHead = new Node<_Ty>();
      pTail = pHead;
      m_nSize=0;
    }
    //Returns First Node
    Node<_Ty>* first()
    {
      return pHead;
    } 

    //Adds a new element to the end of the list
    void add(_Ty* _pObject)
    {
      if (_pObject!=NULL){
        if (pTail -> pObject != NULL){
          pTail->pNext = new Node<_Ty>();
          pTail->pNext->pPrev = pTail;
          pTail = pTail->pNext;
          pTail -> pNext = NULL;
          pTail -> pObject = _pObject;
        }else{
          pTail -> pObject = _pObject;
        }
        m_nSize++;
      }
    }

    //returns the number of elements in the list
    int getSize()
    {
      return m_nSize;
    }

    //Parses the node to be deleted
    Node<_Ty>* remove(Node<_Ty>* _node)
    {
      if (_node == pTail){
        if (_node == pHead){
          delete pTail;
          pHead = new Node<_Ty>;
          pTail = pHead;
          --m_nSize;
          return pHead;
          pHead->pNext=NULL;
          pHead->pPrev=NULL;
        }else{
          pTail = pTail ->pPrev;
          delete pTail ->pNext;
          pTail ->pNext = NULL;
          --m_nSize;
          return pTail;
        }
      }else if (_node == pHead){
        if (pHead->pNext!=NULL){
          pHead = pHead ->pNext;
          delete pHead ->pPrev;
          pHead ->pPrev = NULL;
          --m_nSize;
          return pHead;
        }else{
          --m_nSize;
          delete pHead;
          pHead = new Node<_Ty>();
        }
      }else{
        Node<_Ty>* returnnode = _node ->pPrev;
        returnnode ->pNext = _node ->pNext;
        returnnode ->pNext->pPrev = returnnode;
        delete _node;
        --m_nSize;
        return returnnode;
      }
      return NULL;
    }

    //permantly deletes everything inside the list
    void clear()
    {
      Node<_Ty>* clear = pHead;
      while(clear!=NULL){
        Node<_Ty>* remove = clear;
        clear = clear->pNext;
        delete remove;
      }
      pHead = NULL;
      pTail = NULL;
      clear = NULL;
      m_nSize=0;
    }
};



#endif

