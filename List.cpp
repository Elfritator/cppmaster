#include "List.h"
#include "Place.h"

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