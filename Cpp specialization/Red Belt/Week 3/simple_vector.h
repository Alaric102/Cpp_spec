#pragma once

#include <cstdlib>
#include <string>
#include <math.h>

template <typename T>
class SimpleVector {
public:
    SimpleVector(){
        begin_ = nullptr; end_ = nullptr;
        capacity_ = 0;
    }

    explicit SimpleVector(size_t size){
        if (size == 0){
            begin_ = nullptr; end_ = nullptr;
            capacity_ = 0;
        } else {
            capacity_ = (int)std::pow(2, size - 1);
            begin_ = new T[capacity_];
            end_ = begin_ + size;
        }
    }

    ~SimpleVector(){
        if (capacity_) 
            delete[] begin_;
    };

    T& operator[](size_t index) { return begin_[index]; };

    T* begin(){ return begin_; }
    T* end() { return end_; };
    
    const T* begin() const { return begin_; };
    const T* end() const { return end_; };

    size_t Size() const { return end_ - begin_; };
    size_t Capacity() const { return capacity_; };

    void PushBack(const T& value){
        auto size = Size();
        if (size == 0){
            capacity_ = 1;
            begin_ = new T[capacity_];
            begin_[0] = value;
            end_ = begin_ + 1;
        } else if (size == capacity_) {
            capacity_ *= 2;
            T* new_begin = new T[capacity_];
            for (int i = 0; i < size; ++i)
                new_begin[i] = begin_[i];
            delete[] begin_;
            begin_ = new_begin;
            begin_[size] = value;
            end_ = begin_ + size + 1;
        } else {
            begin_[size] = value;
            ++end_;
        }

    };

private:
    T* begin_;
    T* end_;
    size_t capacity_ = 0;
    // size_t size_ = 0;
};