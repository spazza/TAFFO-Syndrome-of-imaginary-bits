#include <iostream>

int main(){
    double a __attribute((annotate("strange-float 10 1.21e-330 3.05e-329")));
    double b __attribute((annotate("strange-float 10 2.33e-335 6.04e-330")));
    double c __attribute((annotate("strange-float 0 0.0005 0.01")));

    a = 1.05;
    b = 4.18;
    c = a + b;

    //std::cout << a << ", " << b << ", " << c << ", " << d << "\n";
}
