#include <iostream>
#include "fixed_point.hpp"
#include "extended_fixed_point.hpp"

void test1(void);

using namespace std;

int main(){
    test1();    
}
/*  
    First test using extended fixed point
*/
void test1(){
    extended_fixed_point_t<9,9> n1(139.103);
    extended_fixed_point_t<9,9> n2(79.118);

    fixed_point_t<9,9> nn1(139.103);
    fixed_point_t<9,9> nn2(79.118);

    n1 = n1+n2;
    nn1 = nn1+nn2;

    cout << "Normal-fp value example: " << nn1 << endl;
    cout << "Extended-fp value example: " << n1 << endl;

    extended_fixed_point_t<-3,15> e1(0.0014);
    extended_fixed_point_t<-3,15> e2(0.0011);
    e1 = e1+e2;

    cout << "Neg ext-fp value example: " << e1 << endl; //sembra funzionare, pappare



}

