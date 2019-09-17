LLVM教学跟练代码

#笔记
##之前没见过的C++用法
### utility标准库
1.move\\
std::move（移动）：\\
	a = std::move(b)：将b指向的值赋给a，同时释放b的内存
### memory标准库
1. unique_ptr\\
std::unique_ptr（唯一指针）：指针在创建时必须指定指向的对象，并且不同的指针不能指向同一个对象
