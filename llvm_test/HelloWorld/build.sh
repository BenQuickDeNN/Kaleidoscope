# building llvm helloworld
CC="clang++"
DIS="llvm-dis"
LLC="llc"
GCC="g++"
llvm_bc="HelloWorld.bc"
llvm_ir="HelloWorld.ir"
asm="HelloWorld.s"
src="HelloWorld.cpp"
bin="HelloWorld"

# optimization option
OPT="-O3"

# building LLVM bitcode
$CC $src -c -emit-llvm -o $llvm_bc $OPT
if [ $? -eq 0 ]; then
    # generating LLVM IR, disasembling
    $DIS $llvm_bc -o $llvm_ir
    if [ $? -eq 0 ]; then
        # building asm file
        $LLC $llvm_ir -o $asm
        if [ $? -eq 0 ]; then
            # building executable file (on Ubuntu)
            $GCC $asm -o $bin
        fi
    fi
fi