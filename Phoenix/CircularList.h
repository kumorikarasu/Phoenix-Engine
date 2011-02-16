/*

Note :: NOT THREAD SAFE



*/
template<typename _Ty>
class Iterator
{
private:
  Iterator* next;
  Iterator* prev;
  _Ty* Data;
  template<typename _Ty> friend class CircularList;
  Iterator(_Ty* Data)
  {
    this->Data = Data;
    next = NULL;
    prev = NULL;
  }

public:
  Iterator operator++ (int)
  {
    return next;
  }
  Iterator operator++ ()
  {
    return next;
  }
  Iterator operator-- (int)
  {
    return prev;
  }
  Iterator operator-- ()
  {
    return prev;
  }
  Iterator operator*()
  {
    return Data;
  }
};

template<typename _Ty>
class CircularList
{
private:
  Iterator* List;

public:

  Iterator* GetIterator()
  {
    return List;
  }

  int AddToList(_Ty* Data)
  {
    if (Data == NULL)
      return -1;

    if (List == NULL){
      List = new Iterator<_Ty>(Data);
      List->next = List;
      List->prev = List;
    }else{
      Iterator<_Ty>* it = new Iterator<_Ty>(Data);
      List->prev->next = it;
      it->next = List;
      List->prev = it;
    }
  }

  void DeleteList()
  {
    while (List != NULL){
      this->RemoveFromList(List);
    }
  }

  int RemoveFromList(Iterator* it)
  {
    if ((*it) == NULL)
      return 1;

    Iterator<_Ty> i = it;
    it->prev->next = it->next;
    it = it->next;
    if (it == it->next)
      it == NULL;
    delete i;

    return it;
  }
};
