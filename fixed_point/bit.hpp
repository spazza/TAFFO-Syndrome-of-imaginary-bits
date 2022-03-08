#ifndef BIT_HPP
#define BIT_HPP

struct bit_t {

private:

    unsigned int value;

public:

    unsigned int getBit() const { return value; }
    
    void setBit(unsigned int value) { this->value = value; }

    void bitComplement() {
        if(value == 0) 
            value = 1;
        else
            value == 0;
    }
    
};

#endif