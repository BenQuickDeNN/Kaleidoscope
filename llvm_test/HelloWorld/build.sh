# building llvm helloworld
CC="clang++"
DIS="llvm-dis"
LLC="llc"
GCC="gcc"
llvm_bc="HelloWorld.bc"
llvm_ir="HelloWorld.ir"
asm="HelloWorld.s"
src="HelloWorld.cpp"
bin="HelloWorld"

# optimization option
OPT="-O3"

# building LLVM bitcode
$CC $src -c -emit-llvm -o $llvm_bc $OPT

# generating LLVM IR, disasembling
$DIS $llvm_bc -o $llvm_ir

# building asm file
$LLC $llvm_ir -o $asm

# building executable file (on Ubuntu)
$GCC $asm -o $bin