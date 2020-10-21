opt -load /home/user/LLVM_STUFF/TAFFO-Syndrome-of-imaginary-bits/build/Initialization/InitializationPass/InitializationPass.so -Initialization -S -o "out.1.magiclangtmp.ll" < /home/user/LLVM_STUFF/TAFFO-Syndrome-of-imaginary-bits/test/test_file.bc > /dev/null -debug

# opt -load /home/user/LLVM_STUFF/TAFFO-Syndrome-of-imaginary-bits/build/RangeAnalysis/VRA/VRA.so -VRA -S -o "out.2.magiclangtmp.ll" </home/user/LLVM_STUFF/TAFFO-Syndrome-of-imaginary-bits/out.1.magiclangtmp.ll> /dev/null -debug



