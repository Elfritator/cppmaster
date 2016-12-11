//
// Created by Gilles Bonkain on 11/12/16.
//

#ifndef CPPMASTER_PLACE_H
#define CPPMASTER_PLACE_H

#include "List.h"

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


#endif //CPPMASTER_PLACE_H
