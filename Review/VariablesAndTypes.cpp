#include <iostream>

int main(){
    int i1 = 1;
    std::cout << "i1= " << i1 << std::endl;
    int i2 = 2;
    std::cout << "i2= " << i2 << std::endl;
    int i3(3);
    std::cout << "i3= " << i3 << std::endl;
    int i4{ 4 };
    std::cout << "i4= " << i4 << std::endl;

    double d1 = 2.2;
    double d2 = i1;
    int i5 = d1;//loss of data warning
    std::cout << "d1= " << d1 << std::endl;
    std::cout << "d2= " << d2 << std::endl;
    std::cout << "i5= " << i5 << std::endl;

    char c1 = 'a';
    //char c2 = "b"; char* c-style string not allowed
    std::cout << "c1= " << c1 << std::endl;
    //std::cout << "c2= " << c2 << std::endl;
    
    
    bool flag = false;
    std::cout << "flag= " << flag << std::endl;
    flag = i1;
    std::cout << "flag= " << flag << std::endl;
    flag = d1;
    std::cout << "flag= " << flag << std::endl;


    auto a1 = 1;//int
    auto a2 = 2.2;//double
    auto a3 = 'c';//char
    auto a4 = "s";//char* c-tyle string
    auto a5 = true;//bool
    auto a6 = 3L;//long
    auto a7 = 1'000'000'000'000;//long_long and seperators for easy reading
    auto a8 = 0xFF;//hex literal
    auto a9 = 0b1111;//binary literal

    a1 = a2;//loss of data warning

    unsigned char n1 = 128;
    char n2 = 128;//jumps to -128
    std::cout << "n1= " << n1 << std::endl;
    std::cout << "n2= " << n2 << std::endl;
    n1=254;
    n2=254;//jumps to -2
    std::cout << "n1= " << n1 << std::endl;
    std::cout << "n2= " << n2 << std::endl;
    n1=300;//jumps to 44
    n2=300;//jumps to 44
    std::cout << "n1= " << n1 << std::endl;
    std::cout << "n2= " << n2 << std::endl;



    //CASTING
    int i6 = static_cast<int>(d1);
    std::cout << "i6= " << i6 << std::endl;
    a1 = static_cast<int>(a2);
}