#ifndef MATHEMATICAL_VECTOR_ITERATOR_H
#define MATHEMATICAL_VECTOR_ITERATOR_H


template<typename T>
class Iterator {
private:
    T * point;
public:
    typedef std::ptrdiff_t                    difference_type;
    typedef T                                 value_type;
    typedef T *                               pointer;
    typedef T &                               reference;
    typedef std::random_access_iterator_tag   iterator_category	;

    Iterator(): point(nullptr){};
    explicit Iterator(T * item) : point(item){}

    Iterator<T> & operator=(const Iterator<T> & iter) = default;
    ~Iterator() = default;

    Iterator operator+(int add);
    Iterator operator-(int sub);

    bool operator!=(const Iterator<T> & iter) const;
    bool operator==(const Iterator<T> & iter) const;
    bool operator<(const Iterator<T> & iter) const;
    bool operator<=(const Iterator<T> & iter) const;
    bool operator>(const Iterator<T> & iter) const;
    bool operator>=(const Iterator<T> & iter) const;

    Iterator & operator++();
    Iterator operator++(int);
    Iterator & operator--();
    Iterator operator--(int);

    T & operator[](int n);
    T & operator*();
};

template<typename T>
bool Iterator<T>::operator==(const Iterator<T> & iter) const {
    return point == iter.point;
}

template<typename T>
bool Iterator<T>::operator!=(const Iterator<T> & iter) const {
    return !(*this == iter);
}

template<typename T>
bool Iterator<T>::operator<(const Iterator<T> & iter) const{
    return point < iter.point;
}

template<typename T>
bool Iterator<T>::operator<=(const Iterator<T> & iter) const{
    return point <= iter.point;
}

template<typename T>
bool Iterator<T>::operator>(const Iterator<T> &iter) const {
    return !(*this <=  iter);
}

template<typename T>
bool Iterator<T>::operator>=(const Iterator<T> &iter) const {
    return !(*this < iter);
}

template<typename T>
T & Iterator<T>::operator[](int n) {
    return *(point + n);
}

template<typename T>
Iterator<T> Iterator<T>::operator+(int add) {
    Iterator<T> temp(point + add);
    return temp;
}

template<typename T>
Iterator<T> Iterator<T>::operator-(int sub){
    Iterator<T> temp(point - sub);
    return temp;
}

template<typename T>
Iterator<T> operator+(int add, const Iterator<T> & iter){
    return iter + add;
}

template<typename T>
Iterator<T> & Iterator<T>::operator++(){
    point++;
    return *this;
}

template<typename T>
Iterator<T> Iterator<T>::operator++(int){
    Iterator<T> temp = *this;
    point++;
    return temp;
}

template<typename T>
Iterator<T> & Iterator<T>::operator--(){
    point--;
    return *this;
}

template<typename T>
Iterator<T> Iterator<T>::operator--(int){
    Iterator<T> temp = *this;
    point--;
    return temp;
}

template<typename T>
T & Iterator<T>::operator*(){
    return *point;
}


#endif //MATHEMATICAL_VECTOR_ITERATOR_H
