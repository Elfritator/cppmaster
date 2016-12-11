
#include "const_Place.h"

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