#include<iostream>
#include <stdio.h>

#define FFTRACE(fmt, ...) { printf("[%s %d] "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__);}

#if 0

int something(int a, int b) {
    return a+b;
}

int something(int a, int b) {
    return a * b;
}

int main() {
    //std::cout << "Hello World!!" << std::endl;
    int val=0;
    val = something(2, 3);
    printf("return: %d \r\n", val);
    return 0;
}
#endif

#if 1
namespace sum {
    int something(int a, int b) {
        return a + b;
    }
}

int something(int a, int b) {
    return a * b;
}



int main() {
    int val=0;
    val = something(2, 3);
    //printf("return: %d \r\n", val);
    std::cout << "return: " << val << std::endl;

    val = sum::something(2, 3);
    std::cout << "return: " << val << std::endl;

    FFTRACE("Hello... world \n");
    printf("asdfasdf\n");
    
    std::cout << "[" << __FUNCTION__ << " " << __LINE__ << "] " << "log....." << std::endl;
    return 0;
}
#endif
