/*
 * Yves Roggeman - November 2016 - List.hpp
 *
 */
#ifndef _LIST_HPP
#define _LIST_HPP

#include <cstddef>   // NULL, ptrdiff_t, size_t
#include <stdexcept> // exception types

template <typename T>
class List {
public:
  class Place;
  class const_Place;
private:
  struct _Item {
    T      info;
    _Item* next;
    _Item () {}
    _Item (const T& x, _Item* s): info(x), next(s) {}
  };
  _Item*  _first;   // Pointer to first item
  _Item** _last;    // Pointer to next field of last item
  std::size_t _size;

public:
  // Getters
  Place begin () {return Place(this, &_first);}
  Place end ()   {return Place(this, _last);}
  const_Place begin () const {return const_Place(this, &_first);}
  const_Place end ()   const {return const_Place(this, _last);}
  std::size_t size ()  const {return _size;}
  bool empty () const  {return _size == 0;}
  // Constructors
  List (): _first(nullptr), _last(&_first), _size(0) {}
  List (const T& t): _first(nullptr), _last(&_first), _size(0)
    {insert(end(), t);}
  List (const List& L): _first(nullptr), _last(&_first), _size(0)
    {insert(end(), L.begin(), L.end());}
  List (List&& L): _first(L._first), _last(L._size ? L._last : &_first),
                   _size(L._size)
    {L._first = nullptr; L._last= &L._first; L._size = 0;}


  ~List () {clear();}

  // Updates
  virtual Place insert (Place, const T&);
  virtual Place insert (Place, const_Place, const_Place);
  virtual Place erase  (Place);
  void clear ();

private:
};

// Methods
template <typename T>
typename List<T>::Place List<T>::insert (Place p, const T& t) {
  // Insert "at p", i.e. before p (connect to *_current)
  if (p._list != this)
    throw std::invalid_argument("List::insert: invalid iterator");
  *p._current = new _Item(t, *p._current);
  ++_size;
  if (p._current == _last) _last = &(*p._current)->next;
  return p;
}

template <typename T>
typename List<T>::Place List<T>::insert (Place p, const_Place p1, const_Place p2) {
  // Copy from p1 to p2 before p
  if (p._list != this)
    throw std::invalid_argument("List::insert: invalid iterator");
  _Item** q = p._current;
  for (; p1 != p2; ++p1) {
    *q = new _Item(*p1, *q);
    q = &(*q)->next;
    ++_size;
  }
  if (p._current == _last) _last = q;
  return p;
}

template <typename T>
typename List<T>::Place List<T>::erase (Place p) {
  // Erase "at p", i.e. **_current
  if (p._list != this)
    throw std::invalid_argument("List::erase: invalid iterator");
  if (p._current != _last) { // don't erase end()
    _Item* q = *p._current;
    *p._current = (*p._current)->next;
    delete q;
    if (!*p._current) _last = p._current;
    --_size;
  }
  return p;
}

template <typename T>
void List<T>::clear () {
  while (_first) {
    _Item* q = _first;
    _first = _first->next;
    delete q;
  }
  _last = &_first;
  _size = 0;
}

// Iterators
template <typename T>
class List<T>::Place {
  friend class List;
  friend class const_Place;
  List*   _list;
  _Item** _current;
  Place (List* L, _Item** p): _list(L), _current(p) {}
public:
  Place (): _list(nullptr), _current(nullptr) {}          // Singular value
  inline T& operator* () const;
  inline T* operator-> () const;
  inline Place& operator++ ();
  inline Place operator++ (int);              // Postfix
  inline friend bool operator== (const Place& p1, const Place& p2)
    {return p1._current == p2._current;}
  inline friend bool operator!= (const Place& p1, const Place& p2)
    {return p1._current != p2._current;}
};

template <typename T>
class List<T>::const_Place {
  friend class List;
  const List*        _list;
  const _Item*const* _current;
  const_Place (const List* L, const _Item*const* p): _list(L), _current(p) {}
public:
  const_Place (): _list(nullptr), _current(nullptr) {}    // Singular value
  const_Place (const Place& p): _list(p._list), _current(p._current) {} // conv
  inline const T& operator* () const;

  inline const_Place& operator++ ();
  inline const_Place operator++ (int);       // Postfix

};

// Iterators methods
template <typename T>
inline T& List<T>::Place::operator* () const {
  if (! _current)
    throw std::invalid_argument("List::Place::operator*: singular value");
  if (! *_current)
    throw std::invalid_argument("List::Place::operator*: end() value");
  return (*_current)->info;
}


template <typename T>
inline typename List<T>::Place& List<T>::Place::operator++ () {
  if (! _current)
    throw std::invalid_argument("List::Place::operator++: singular value");
  if (! *_current)
    throw std::invalid_argument("List::Place::operator++: end() value");
  _current = &(*_current)->next;
  return *this;
}

template <typename T>
inline typename List<T>::Place List<T>::Place::operator++ (int) {
  if (! _current)
    throw std::invalid_argument("List::Place::operator++: singular value");
  if (! *_current)
    throw std::invalid_argument("List::Place::operator++: end() value");
  Place p(*this);
  _current = &(*_current)->next;
  return p;
}

template <typename T>
inline const T& List<T>::const_Place::operator* () const {
  if (! _current)
    throw std::invalid_argument("List::const_Place::operator*: singular value");
  if (! *_current)
    throw std::invalid_argument("List::const_Place::operator*: end() value");
  return (*_current)->info;
}


template <typename T>
inline typename List<T>::const_Place& List<T>::const_Place::operator++ () {
  if (! _current)
    throw std::invalid_argument("List::const_Place::operator++: singular value");
  if (! *_current)
    throw std::invalid_argument("List::const_Place::operator++: end() value");
  _current = &(*_current)->next;
  return *this;
}

template <typename T>
inline typename List<T>::const_Place List<T>::const_Place::operator++ (int) {
  if (! _current)
    throw std::invalid_argument("List::const_Place::operator++: singular value");
  if (! *_current)
    throw std::invalid_argument("List::const_Place::operator++: end() value");
  const_Place p(*this);
  _current = &(*_current)->next;
  return p;
}

#endif  /* _LIST_HPP */