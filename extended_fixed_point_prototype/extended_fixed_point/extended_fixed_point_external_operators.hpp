#ifndef EXTENDED_FIXED_POINT_OPERATORS_HPP
#define EXTENDED_FIXED_POINT_OPERATORS_HPP

//---------------------------------------------------------------------------
// External operators
//---------------------------------------------------------------------------

// Make the fixed-point struct  ostream outputtable
template<int16_t INT_BITS, int16_t FRAC_BITS>
std::ostream& operator<< (std::ostream &stream,
	const extended_fixed_point_t<INT_BITS, FRAC_BITS> &efp)
{
	return efp.emit(stream);
}

#endif