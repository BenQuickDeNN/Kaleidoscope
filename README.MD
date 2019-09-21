LLVM教学跟练代码，实现Kaleidoscope语言. LLVM tutorial <https://llvm.org/docs/tutorial>.

# Directories Description
## src
Main source code to implement Kaleidoscope.
## include
Dependence headers, including llvm/llvm-c headers.
## llvm_test
Some scattered small projects to validate the application of LLVM.

# 笔记

## 编译原理
### 编译过程
预处理阶段：将主文件（编译对象）与引用的文件整合（超级长的C++代码），"#include"在这个阶段发挥作用。

编译阶段：将C++代码转换为汇编代码，"-g"选项在这个阶段发挥作用，将符号表嵌入汇编代码中。

汇编阶段：将多个目标文件（包括编译阶段生成的用户目标文件，和编译器库自带的静态目标文件）合并为一个可执行文件。

加载阶段（执行阶段）：这一步执行可执行文件，在执行过程中加载需要的动态目标文件，"DllImport"在这一阶段发挥作用。

### Constant Folding
Folded constant:
```
ready> def test(x) 1+2+x;
Read function definition:
define double @test(double %x) {
entry:
    %addtmp = fadd double 3.000000e+00, %x
    ret double %addtmp
}
```
Unfolded constant:
```
ready> def test(x) 1+2+x;
Read function definition:
define double @test(double %x) {
entry:
    %addtmp = fadd double 2.000000e+00, 1.000000e+00
    %addtmp1 = fadd double %addtmp, %x
    ret double %addtmp1
}
```
Constant folding, as seen above, in particular, is a very common and very important optimization. It help reduce the number of instructions.

## C++用法
### nullptr
空指针
### Prototype for a function（函数原型）
C++中的函数原型就是函数声明，将函数的名字、类型、个数和顺序通知给编译系统，以便调用函数时对照检查
### 函数参数传值与传地址
传值需要额外开辟空间来存储临时变量，开销较大，且参数只能作为输入参数。
传地址不需要额外开辟空间，效率较高，参数可作为输出参数。
### const妙用
一个函数如果其输入参数采用“指针传递”，那么加const修饰可防止意外地改动该指针。
特别注意参数加const后不能当输出参数用。

如果函数的返回值为指针形式，用const修饰返回值可使函数返回的值（指针）不能被修改。
### auto
相当于一个“万能类型”。auto a = b; a的类型取决于b。有点像CSharp中的var类型。
### utility.std::move（移动）
a = std::move(b)：将b指向的值赋给a，同时释放b的内存
### memory.std::unique_ptr（唯一指针）
指针在创建时必须指定指向的对象，并且不同的指针不能指向同一个对象
### override
C++ 11 standard, indicating that a virtual function must be rewritten.

## LLVM
### LLVM IR
IR（immediately representation）是LLVM的一种中间代码

# Troubleshoot
## error LNK2001
F:\projects\Cpp\LLVM_tutorial>call clang++ build/kaleidoscope_main.o -o bin/kaleidoscope_main.exe -L lib   && (goto link_succed )  || goto link_failed

kaleidoscope_main.o : error LNK2001: 无法解析的外部符号 "public: virtual class llvm::Value * __cdecl VariableExprAST::codegen(void)" (?codegen@VariableExprAST@@UEAAPEAVValue@llvm@@XZ)

kaleidoscope_main.o : error LNK2001: 无法解析的外部符号 "public: virtual class llvm::Value * __cdecl CallExprAST::codegen(void)" (?codegen@CallExprAST@@UEAAPEAVValue@llvm@@XZ)

kaleidoscope_main.o : error LNK2001: 无法解析的外部符号 "public: virtual class llvm::Value * __cdecl NumberExprAST::codegen(void)" (?codegen@NumberExprAST@@UEAAPEAVValue@llvm@@XZ)

kaleidoscope_main.o : error LNK2001: 无法解析的外部符号 "public: virtual class llvm::Value * __cdecl BinaryExprAST::codegen(void)" (?codegen@BinaryExprAST@@UEAAPEAVValue@llvm@@XZ)

bin/kaleidoscope_main.exe : fatal error LNK1120: 4 个无法解析的外部命令

### solving LNK2001
1. Add linking option "`llvm-config --cxxflags --ldflags --system-libs --libs core`" in build files, then it comes the error "Link error: Cannot find -Ltinfo...".

2. In Ubuntu 16.04 terminal, use command "sudo apt-get install libtinfo-dev" to install ltinfo. See <https://www.e-learn.cn/content/wangluowenzhang/819973>