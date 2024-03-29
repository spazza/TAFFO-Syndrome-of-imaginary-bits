# Fixed point extension prototype

Fixed-point prototype for C++. <br/>
Three possible representations are available:

- `Normal_fixed_point_t`, usual fixed point representation with integer and fractional bits.
- `High_fixed_point_t`, representation composed by integer bits and outside bits that represent the shifting of the dot out of the range (left).
- `Low_fixed_point_t`, representation composed by fractional bits and outside bits that represent the shifting of the dot out of the range (right).

The prototype is tested on the main logical operators (` =, <, <=, >, =>, ==, !=`) and on the 4 main operations (`+, -, *, /`) <br/>

Test can be performed with command: <br/>
`make exec`
<br/>

If it is necessary to carry out a single test: <br/>
`make exec_single TESTNAME=testname` <br/>
where testname is the name of the test to be executed.

## Requirements
- BOOST library version 1.77
- Make

## Project status
:green_square: Fixed point representation <br/> 
:green_square: Fixed point creation <br/>
:green_square: Assignment operator <br/>
:green_square: Logical operators <br/>
:green_square: Conversion <br/>
:green_square: Sum <br/>
:green_square: Difference <br/>
:green_square: Product <br/>
:green_square: Division <br/>
:green_square: Print <br/>
:green_square: Multiple operations test <br/>
