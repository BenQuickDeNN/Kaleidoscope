# define source file, from parameter 1
SRC=$1

# define binary file
BIN="main"

# define others
GCC="g++"

# building LLVM bitcode
$GCC $SRC -o $BIN