/* C++ Memory Management
Code Based on YouTube Video and C++ Tutorial [https://www.youtube.com/watch?v=ZzaPdXTrSb8] |
[https://cplusplus.com/]*/
#include <iostream>
#include <vector>

int main(){
    //Allocation
    std:vector<int>* data = new std::vector<int>(10);
    for (int i = 0; i <data->size(); i++){
        (*data)[i] = i;
    }
    //Use the data.
    std::cout<< "Data size: "<< data->size()<<std::end;

    //Deallocating the data, freeing it.
    delete data;
    //Preventing dangling pointer
    data = nullptr;

    return 0;
}