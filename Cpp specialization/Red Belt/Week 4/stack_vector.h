#pragma once

#include <stdexcept>
#include <array>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0) {
        if (a_size > N)
            throw invalid_argument("");
        _vector_size = a_size;
    };

    T& operator[](size_t index) {return _data[index]; } ;
    const T& operator[](size_t index) const {return _data[index]; } ;

    typename array<T, N>::iterator begin() { return _data.begin(); } ;
    typename array<T, N>::iterator end() { return _data.begin() + _vector_size; };
    typename array<T, N>::const_iterator begin() const { return _data.begin(); };
    typename array<T, N>::const_iterator end() const { return _data.begin() + _vector_size; };

    size_t Size() const { return _vector_size; };
    size_t Capacity() const { return _data.size(); };

    void PushBack(const T& value) {
        if (_vector_size >= _data.size())
            throw overflow_error("");
        _data[_vector_size++] = value;
    };
    T PopBack() {
        if (_vector_size <= 0)
            throw underflow_error("");
        return _data[--_vector_size];
    };

    private:
        size_t _vector_size;
        array<T, N> _data;
};
