# define source file, from parameter 1
SRC=$1

# define binary file
BIN="main.out"

# define compiler
CC="clang++"

# define ir file
IR="main.ir"

# define bc file
BC="main.bc"

# define s file
S="main.s"

# define others
DIS="llvm-dis"
LLC="llc"
GCC="g++"

# building LLVM bitcode
$CC $SRC -c -emit-llvm -o $BC
if [ $? -eq 0 ]; then
    # generating LLVM IR, disasembling
    $DIS $BC -o $IR
    if [ $? -eq 0 ]; then
        # building asm file
        $LLC $IR -o $S
        if [ $? -eq 0 ]; then
            # building executable file (on Ubuntu)
            $GCC $S -o $BIN
        fi
    fi
fi