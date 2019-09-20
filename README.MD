Implementation of Kaleidoscope Language. See LLVM tutorial <https://llvm.org/docs/tutorial>.

# Note

## Theory of Compiling
### The Process of Compiling

## C++
### nullptr

### Prototype for a function

### Function Arguments

### Const + Function

### auto

### utility.std::move
a = std::move(b)：
### memory.std::unique_ptr

## LLVM
### LLVM IR
IR（immediately representation）

# Troubleshoot
## error LNK2001
F:\projects\Cpp\LLVM_tutorial>call clang++ build/kaleidoscope_main.o -o bin/kaleidoscope_main.exe -L lib   && (goto link_succed )  || goto link_failed

kaleidoscope_main.o : error LNK2001: 无法解析的外部符号 "public: virtual class llvm::Value * __cdecl VariableExprAST::codegen(void)" (?codegen@VariableExprAST@@UEAAPEAVValue@llvm@@XZ)

kaleidoscope_main.o : error LNK2001: 无法解析的外部符号 "public: virtual class llvm::Value * __cdecl CallExprAST::codegen(void)" (?codegen@CallExprAST@@UEAAPEAVValue@llvm@@XZ)

kaleidoscope_main.o : error LNK2001: 无法解析的外部符号 "public: virtual class llvm::Value * __cdecl NumberExprAST::codegen(void)" (?codegen@NumberExprAST@@UEAAPEAVValue@llvm@@XZ)

kaleidoscope_main.o : error LNK2001: 无法解析的外部符号 "public: virtual class llvm::Value * __cdecl BinaryExprAST::codegen(void)" (?codegen@BinaryExprAST@@UEAAPEAVValue@llvm@@XZ)

bin/kaleidoscope_main.exe : fatal error LNK1120: 4 个无法解析的外部命令

### solving LNK2001
1. Add linking option "`llvm-config --cxxflags --ldflags --system-libs --libs core`" in build files, then it comes the problem "Link error: Cannot find -Ltinfo...".

2. In Ubuntu 16.04 terminal, use command "sudo apt-get install libtinfo-dev" to install ltinfo. See <https://www.e-learn.cn/content/wangluowenzhang/819973>