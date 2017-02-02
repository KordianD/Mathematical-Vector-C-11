#ifndef MATHEMATICAL_VECTOR_VECTOR_H
#define MATHEMATICAL_VECTOR_VECTOR_H


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

    Vector(const Vector<DT> & v);
    Vector(Vector<DT> && v);

    Vector & operator=(const Vector<T> & v);
    Vector & operator=(Vector<T> && v);

    virtual ~Vector();

    void swap(Vector<T> & other) noexcept;

    Vector operator+(const Vector<T> & v) const;
    //Vector operator+(T & v) const;
    //Vector<T> operator+() const;

    //Vector & operator+=(const Vector<T> & v);
    //Vector & operator+=(T & v);

    //Vector operator-(const Vector<T> & v) const;
    //Vector operator-(T & v) const;
    //Vector<T> operator-() const

    //Vector & operator-=(const Vector<T> & v);
    //Vector & operator-=(T & v);

    //auto operator*(const Vector<T> & v) const -> decltype(x)
    //Vector operator*(T & v);


    //Vector & operator =*(T & t);

    //Vector operator/(T & v);

    //Vector & operator/=(T & v);

    //bool operator!=(const Vector<T> & v) const;
    //bool operator==(const Iterator<T> & v) const;

    //bool operator>(const Vector<T> & v) const;
    //bool operator>=(const Vector<T> & v) const;
    //bool operator<(const Vector<T> & v) const;
    //bool operator<=(const Vector<T> & v) const;

    //auto length(const Vector<T> & c) -> decltype(x)

    //int size() const;

    // T min() const;
    // T max() const;

    //T   operator[]( std::size_t pos ) const;
    //const T &    operator[]( std::size_t pos ) const;
   // T &     operator[]( std::size_t pos );



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
                                         storage(!v._size ? nullptr :  new T[v.size]) {
    std::copy(v.storage, v.storage + _size, storage);
}

template<typename T>
Vector<T>::Vector(Vector<T> && v) : Vector(){
    swap(*this, v);
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
    std::swap(storage, other.m);
    std::swap(_size, other.s);
}




#endif //MATHEMATICAL_VECTOR_VECTOR_H
