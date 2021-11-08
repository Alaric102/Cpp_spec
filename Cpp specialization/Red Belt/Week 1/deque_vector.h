#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class Deque{
public:
    Deque(){

    };

    bool Empty() const { return direct.empty() && inverse.empty(); };

    size_t Size() const { return direct.size() + inverse.size(); };

    T& operator[](size_t val){
        if (val >= inverse.size() ){
            val -= inverse.size();
            return direct[val];
        } else {
            return inverse[inverse.size() - 1 - val];
        }
    };
    
    const T& operator[](size_t val) const{ 
        if (val >= inverse.size() ){
            val -= inverse.size();
            return direct[val];
        } else {
            return inverse[inverse.size() - 1 - val];
        }
    };

    T& At(int val){
        if (val >= Size()){
            throw out_of_range("");
        } else {
            return this->operator[](val);
        }
    };
    
    const T& At(int val) const {
        if (val >= Size()){
            throw out_of_range("");
        } else {
            return this->operator[](val);
        }
    };

    T& Front(){ 
        if (inverse.empty()){
            return direct.front();
        }
        return inverse.back(); 
    };
    
    const T& Front() const { 
        if (inverse.empty()){
            return direct.front();
        }
        return inverse.back(); 
    };

    T& Back(){ 
        if (direct.empty()){
            return inverse.front();
        }
        return direct.back(); 
    };
    
    const T& Back() const { 
        if (inverse.empty()){
            return direct.front();
        }
        return direct.back(); 
    };

    void PushFront(const T& value){ inverse.push_back(value); };

    void PushBack(const T& value){ direct.push_back(value); };

private:
    vector<T> direct;
    vector<T> inverse;
};
