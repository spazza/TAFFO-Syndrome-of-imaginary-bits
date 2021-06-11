#ifndef EXTENDED_FIXED_POINT_CONVERSION_HPP
#define EXTENDED_FIXED_POINT_CONVERSION_HPP

template<typename T>
class Converter {
protected:
	uint16_t old_bits_amount;
	uint16_t new_bits_amount;
	Converter(uint16_t old_bits_amount, uint16_t new_bits_amount) : old_bits_amount(old_bits_amount), new_bits_amount(new_bits_amount) {}
public:
	virtual T convert(T value) = 0;
};

template<typename T>
class ConverterPPPP : public Converter<T> {
public:
	ConverterPPPP(uint16_t old_bits_amount, uint16_t new_bits_amount) : Converter<T>(old_bits_amount, new_bits_amount) {}
	T convert(T raw) override {
		bool sh_dir_right = this -> old_bits_amount > this -> new_bits_amount; 

		if(sh_dir_right) 
			raw >>= this -> old_bits_amount - this -> new_bits_amount;
		else
			raw <<= this -> new_bits_amount - this -> old_bits_amount;
		return raw;	
	}
};

template<typename T>
class ConverterPPPN : public Converter<T> {
public:
	ConverterPPPN(uint16_t old_bits_amount, uint16_t new_bits_amount) : Converter<T>(old_bits_amount, new_bits_amount) {}
	T convert(T raw) override {
		raw >>= this -> old_bits_amount + this -> new_bits_amount;
		return raw;
	}
};

template<typename T>
class ConverterPPNP : public Converter<T> {
public:
	ConverterPPNP(uint16_t old_bits_amount, uint16_t new_bits_amount) : Converter<T>(old_bits_amount, new_bits_amount) {}
	T convert(T raw) override {
		bool sh_dir_right = this -> old_bits_amount > this -> new_bits_amount; 

		if(sh_dir_right) 
			raw >>= this -> old_bits_amount - this -> new_bits_amount;
		else
			raw <<= this -> new_bits_amount - this -> old_bits_amount;
		return raw;
	}
};

template<typename T>
class ConverterPNPP : public Converter<T> {
public:
	ConverterPNPP(uint16_t old_bits_amount, uint16_t new_bits_amount) : Converter<T>(old_bits_amount, new_bits_amount) {}
	T convert(T raw) override {
		raw <<= this -> old_bits_amount + this -> new_bits_amount;
		return raw;
	}
};

template<typename T>
class ConverterPNPN : public Converter<T> {
public:
	ConverterPNPN(uint16_t old_bits_amount, uint16_t new_bits_amount) : Converter<T>(old_bits_amount, new_bits_amount) {}
	T convert(T raw) override {
		bool sh_dir_right = this -> old_bits_amount > this -> new_bits_amount;

		if(sh_dir_right) 
			raw >>= this -> old_bits_amount - this -> new_bits_amount;
		else
			raw <<= this -> new_bits_amount - this -> old_bits_amount;
		return raw;
	}
};

template<typename T>
class ConverterNPPP : public Converter<T> {
public:
	ConverterNPPP(uint16_t old_bits_amount, uint16_t new_bits_amount) : Converter<T>(old_bits_amount, new_bits_amount) {}
	T convert(T raw) override {
		bool sh_dir_right = this -> old_bits_amount < this -> new_bits_amount;

		if(sh_dir_right)
			raw >>= this -> new_bits_amount - this -> old_bits_amount;
		else
			raw <<= this -> old_bits_amount - this -> new_bits_amount;
		return raw;
	}
};

template<typename T>
class ConverterNPNP : public Converter<T> {
public:
	ConverterNPNP(uint16_t old_bits_amount, uint16_t new_bits_amount) : Converter<T>(old_bits_amount, new_bits_amount) {}
	T convert(T raw) override {
		bool sh_dir_right = this -> old_bits_amount > this -> new_bits_amount;

		if(sh_dir_right)
			raw >>= this -> old_bits_amount - this -> new_bits_amount;
		else
			raw <<= this -> new_bits_amount - this -> old_bits_amount;
		return raw;
	}
};

#endif