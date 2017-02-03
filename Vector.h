#ifndef MATHEMATICAL_VECTOR_VECTOR_H
#define MATHEMATICAL_VECTOR_VECTOR_H

#include "Iterator.h"
#include <cmath>

template<typename T>
class Vector{
private:
    T * storage;
    int _size;
public:
    Vector();
    explicit Vector(int size);
    Vector(int size, T value);
    Vector(const std::initializer_list<T> & v);

    Vector(const Vector<T> & v);
    Vector(Vector<T> && v);

    Vector & operator=(const Vector<T> & v);
    Vector & operator=(Vector<T> && v);

    virtual ~Vector();

    void swap(Vector<T> & other) noexcept;

    Vector operator+(const Vector<T> & v) const;
    Vector operator+(T v) const;
    Vector<T> operator+() const;

    Vector & operator+=(const Vector<T> & v);
    Vector & operator+=(T v);

    Vector operator-(const Vector<T> & v) const;
    Vector operator-(T v) const;
    Vector<T> operator-() const;

    Vector & operator-=(const Vector<T> & v);
    Vector & operator-=(T v);

    T operator*(const Vector<T> & v) const;
    Vector operator*(T v) const;

    Vector & operator *=(T t);

    Vector operator/(T v) const;

    Vector & operator/=(T v);

    bool operator==(const Vector<T> & v) const;
    bool operator!=(const Vector<T> & v) const;

    bool operator>(const Vector<T> & v) const;
    bool operator>=(const Vector<T> & v) const;
    bool operator<(const Vector<T> & v) const;
    bool operator<=(const Vector<T> & v) const;

    auto length() const;
    int size() const;

    T min() const;
    T max() const;

    T & operator[](int pos);
    const T &  operator[](int pos) const;

    Vector abs();

    friend class Iterator<T>;
    Iterator<T> end();
    Iterator<T> begin();
};

template<typename T>
Vector<T>::Vector() : storage(nullptr), _size(0) {}

template<typename T>
Vector<T>::Vector(int size) : storage(new T[size]), _size(size) {}

template<typename T>
Vector<T>::Vector(int size, T value) : storage(new T[size]), _size(size) {
    for (T & x : storage)
        x = value;
}

template<typename T>
Vector<T>::Vector(const std::initializer_list<T> & v) : storage(new T[v.size()]), _size(v.size()) {
    for (int i = 0; i < v.size(); i++)
        storage[i] = *(v.begin() + i);
}

template<typename T>
Vector<T>::Vector(const Vector<T> & v) : _size(v._size),
                                         storage(!v._size ? nullptr :  new T[v._size]) {
    std::copy(v.storage, v.storage + _size, storage);
}

template<typename T>
Vector<T>::Vector(Vector<T> && v) : Vector(){
    this->swap(v);
}

template<typename T>
Vector<T> & Vector<T>::operator=(const Vector<T> & v){
    Vector<T> copy(v);
    copy.swap(*this);
    return *this;
}

template<typename T>
Vector<T> & Vector<T>::operator=(Vector<T> && v){
    v.swap(*this);
    return *this;
}

template<typename T>
Vector<T>::~Vector() {
    delete [] storage;
}

template<typename T>
void Vector<T>::swap(Vector<T> & other) noexcept {
    std::swap(storage, other.storage);
    std::swap(_size, other._size);
}

template<typename T>
Vector<T> Vector<T>::operator+(const Vector<T> & v) const{
    Vector<T> temp(_size);
    for (int i = 0; i < _size; i++)
        temp.storage[i] = storage[i] + v.storage[i];

    return temp;
}

template<typename T>
Vector<T> Vector<T>::operator+(T v) const{
    Vector<T> temp(_size);
    for (int i = 0; i < _size; i++)
        temp.storage[i] = storage[i] + v;

    return temp;
}

template<typename T>
Vector<T> Vector<T>::operator+() const{
    Vector temp(*this);
    return temp;
}

template<typename T>
Vector<T> & Vector<T>::operator+=(const Vector<T> & v){
    for (int i = 0; i < _size; i++)
        storage[i] += v.storage[i];

    return *this;
}

template<typename T>
Vector<T> & Vector<T>::operator+=(T v){
    for (int i = 0; i < _size; i++)
        storage[i] += v;

    return *this;
}

template<typename T>
Vector<T> Vector<T>::operator-(const Vector<T> & v) const{
    Vector<T> temp(_size);
    for (int i = 0; i < _size; i++)
        temp.storage[i] = storage[i] - v.storage[i];

    return temp;
}

template<typename T>
Vector<T> Vector<T>::operator-(T v) const{
    Vector<T> temp(_size);
    for (int i = 0; i < _size; i++)
        temp.storage[i] = storage[i] - v;

    return temp;
}

template<typename T>
Vector<T> Vector<T>::operator-() const{
    Vector<T> temp(_size);
    for(int i = 0; i < _size; i++)
        temp.storage[i] = -storage[i];

    return temp;
}

template<typename T>
Vector<T> & Vector<T>::operator-=(const Vector<T> & v){
    for(int i = 0; i < _size; i++)
        storage[i] -= v.storage[i];

    return *this;
}

template<typename T>
Vector<T> & Vector<T>::operator-=(T v){
    for (int i = 0; i < _size; i++)
        storage[i] -= v;

    return *this;
}

template<typename T>
T Vector<T>::operator*(const Vector<T> & v) const{
    T result = 0;
    for (int i = 0; i < _size; i++)
        result += storage[i] * v.storage[i];

    return result;
}
template<typename T>
Vector<T> Vector<T>::operator*(T v) const {
    Vector<T> temp(_size);
    for(int i = 0; i < _size; i++)
        temp.storage[i] = storage[i] * v;

    return temp;
}

template<typename T>
Vector<T> & Vector<T>::operator*=(T t){
    for(int i = 0; i < _size; i++)
        storage[i] *= t;

    return *this;
}

template<typename T>
Vector<T> Vector<T>::operator/(T v) const{
    Vector<T> temp(_size);
    for (int i = 0; i < _size; i++)
        temp.storage[i] = storage[i] / v;

    return temp;
}

template<typename T>
Vector<T> & Vector<T>::operator/=(T v){
    for (int i = 0; i < _size; i++)
        storage[i] /= v;

    return *this;
}

template<typename T>
bool Vector<T>::operator==(const Vector<T> & v) const{
    if (_size != v._size)
        return false;

    for (int i = 0; i < _size; i++)
        if(storage[i] != v.storage[i])
            return false;

    return true;
}

template<typename T>
bool Vector<T>::operator!=(const Vector<T> & v) const{
    return !(*this == v);
}


template<typename T>
bool Vector<T>::operator>(const Vector<T> & v) const{
    return this->length() > v.length();
}

template<typename T>
bool Vector<T>::operator>=(const Vector<T> & v) const{
    return this->length() >= v.length();
}

template<typename T>
bool Vector<T>::operator<(const Vector<T> & v) const{
        return *this >= v;
}

template<typename T>
bool Vector<T>::operator<=(const Vector<T> & v) const{
        return !(*this > v);
}

template<typename T>
auto Vector<T>::length() const{
    auto temp = 0;
    for (int i = 0; i < _size; i++)
        temp += storage[i] * storage[i];

    auto result = sqrt(temp);
    return  result;
}

template<typename T>
int Vector<T>::size() const{
    return _size;
}

template<typename T>
T Vector<T>::min() const{
    T temp = storage[0];
    for (int i = 1; i < _size; i++)
        if (storage[i] < temp)
            temp = storage[i];

    return temp;
}

template<typename T>
T Vector<T>::max() const{
    T temp = storage[0];
    for (int i = 1; i < _size; i++)
        if (storage[i] > temp)
            temp = storage[i];

    return temp;
}

template<typename T>
const T &  Vector<T>::operator[](int pos) const{
    return storage[pos];
}

template<typename T>
T & Vector<T>::operator[](int pos){
    return storage[pos];
}

template<typename T>
Vector<T> Vector<T>::abs(){
    Vector<T> temp(_size);
    for (int i = 0; i < _size; i++)
        temp.storage[i] = ::abs(storage[i]);

    return temp;
}

template<typename T>
Iterator<T> Vector<T>::end(){
    Iterator<T> temp(storage + _size);
    return temp;
}

template<typename T>
Iterator<T> Vector<T>::begin(){
    Iterator<T> temp(storage);
    return temp;
}

template<typename T>
Vector<T> operator+(T t, const Vector<T> & v ){
    return v + t;
}

template<typename T>
Vector<T> operator-(T t, const Vector<T> & v){
    return -(v - t);
}

template<typename T>
Vector<T> operator*(T t, const Vector<T> & v){
    return v * t;
}

#endif //MATHEMATICAL_VECTOR_VECTOR_H
