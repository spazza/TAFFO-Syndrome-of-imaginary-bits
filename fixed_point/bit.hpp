#ifndef BIT_HPP
#define BIT_HPP

#include "exceptions.hpp"

struct bit_t {

private:

    unsigned int value;

public:

	bit_t(unsigned int value) : value(value) {
		try {
			if(value != 0 || value != 1)
				throw WrongBitValueException(value);		
		} catch (WrongBitValueException e) {
			e.getMessage();
			e.abort();
		}
	}

    unsigned int getBit() const { return value; }
    
    void setBit(unsigned int value) { 
		try {
			if(value != 0 || value != 1)
				throw WrongBitValueException(value);
			else
				this->value = value;	
		} catch (WrongBitValueException e) {
			e.getMessage();
			e.abort();
		}
	}

    void bitComplement() {
        if(value == 0) 
            value = 1;
        else
            value = 0;
    }
    
};

#endif