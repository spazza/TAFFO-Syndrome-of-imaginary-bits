cd build
cmake ..
make -j2
cd ..
clang++ -emit-llvm /home/user/LLVM_STUFF/TAFFO-Syndrome-of-imaginary-bits/Test/test_file.cpp -c -o /home/user/LLVM_STUFF/TAFFO-Syndrome-of-imaginary-bits/Test/test_file.bc
opt -load /home/user/LLVM_STUFF/TAFFO-Syndrome-of-imaginary-bits/build/StrangeBitsPrototype/StrangeBitsPrototypePass/StrangeBitsPrototypePass.so -StrangeBitsPrototype -S -o Test/init_out.ll < /home/user/LLVM_STUFF/TAFFO-Syndrome-of-imaginary-bits/Test/test_file.bc > /dev/null -debug