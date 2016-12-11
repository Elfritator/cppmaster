//
// Created by Gilles Bonkain on 11/12/16.
//



#ifndef CPPMASTER_CONST_PLACE_H
#define CPPMASTER_CONST_PLACE_H

#include "List.h"

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



#endif //CPPMASTER_CONST_PLACE_H
