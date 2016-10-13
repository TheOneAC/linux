#####   basic gdb
```
gcc -g hello.c -o hello
-g 		：在可执行文件中加入源代码信息，保证调试时gdb能找到源文件
-o 		：命名输出的编译文件
gdb hello ：进入gdb环境
list    ：show the source code only ten rows    l
回车     ：重复上一条命令
l   functionname 	 ：l+filename to show the source code
start   		 ：start to run the exe
n     	   	 	 ： 逐条执行下一行
step   			 ：下一步，若有子函数则进入子函数     简写s
backtrace 		 ：查看函数调用栈帧  bt简写
info  locals		 ：查看局部变量  简写i
frame n    		 ：选择栈帧
i locals   	 	 ： 查看选择帧的局部变量
print   local_varible    ：打印局部变量名
set var local——varible=n ：修改局部变量

display  变量名           ：每步执行显示该变量值
undisplay                 ：不再显示变量值
break n                   ：断电设置在第n行   b
countinue                 ：继续执行不是单步执行   c
i breakpoints             ： 显示所有断点
delete breakpoint n       ：删除编号n的断点
disable breakpoint n      ： 暂时禁用断点n
enable breakpoint n       ： 启用 断点n
breack n if .....         ： 当条件满足时启用断点 n
watch varible             :设置观察点
i watchpoints             ：显示观察点信息
x/nb   寄存器             : 显示寄存器中n个比特位的值，不区分变量
set follow-fork-mode child.parent   : 追踪子进程或者父进程
```











