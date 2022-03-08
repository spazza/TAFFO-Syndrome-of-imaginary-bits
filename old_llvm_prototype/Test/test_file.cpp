#include <iostream>

int main(){
    double a __attribute((annotate("strange-float 8 0.00001 0.004")));
    double b __attribute((annotate("strange-float 5 0.0000002 0.0001")));
    double c;

    a = 1.05;
    b = 4.18;
    c = a + b;

    //std::cout << a << ", " << b << ", " << c << ", " << d << "\n";
}
