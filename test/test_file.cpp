#include <iostream>

int main(){
	std::cout << "Test File" << std::endl;
	float a __attribute((annotate("strange-float 10 1.105e-330 5.11e-325")));
	float b __attribute((annotate("strange-float 10 2.243e-335 3.09e-332")));
	float c __attribute((annotate("strange-float 10 1.092e-332 5.044e-331")));
	a = 2.1;
	b = 3.1;

	c = a + b;
	std::cout << "Result: " << c << std::endl;
	return 0;
}
