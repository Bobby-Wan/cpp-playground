#include <iostream>
#include <vector>
#include "data_structures/vector.hpp"

class NeuralNode{
    double state;
    NeuralNode* parents;
    NeuralNode* children;

};

template<typename T> size_t argmax(const std::vector<T> elements){
    int max = elements[0];
    size_t index_max = 0;

    for(auto it = elements.begin();it != elements.end(); ++it){
        if(max < *it){
            max = *it;
            index_max = it - elements.begin();
        }
    }

    return index_max;
}

template <class T>
void merge_sort(ds::vector<T> vec){
    //TODO
    auto size = vec.get_size();
    auto middle = size/2;
    
}

int main(){
    std::vector<int> elems{10,20,30};
    std::cout<<argmax(elems)<<std::endl;

    return 0;
}