#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <iostream>
#include <exception>

using namespace std;

struct WrongBitValueException : public exception {
	
private:

	unsigned int value;
	
public:

	WrongBitValueException(unsigned int value) : value(value) {}

	void getMessage() {
		cout << "Bit initialized with an invalid value : " << value << endl;
	}
	
	void abort() {
		exit(EXIT_FAILURE);
	}
}

#endif
