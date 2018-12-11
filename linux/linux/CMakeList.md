## CMakeLists.txt 编写

#### CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

#### 项目信息
project (Demo1)

#### 添加头文件目录
include_directories

#### 添加链接库
link_directories(dir1, dir2)

#### 指定生成目标
add_executable(Demo main.cc)


#### 单目录源文件
  Demo2
	|  
	+--- main.cc  
	|  
	+--- MathFunctions.cc  
	|  
	+--- MathFunctions.h  
	
aux_source_directory(\<dir> \<variable>)  
查找指定目录下的所有源文件，然后将结果存进指定变量名  

#### 多目录源文件
 ./Demo3  
	|  
	+--- main.cc  
	|  
	+--- math/  
		 |  
		 +--- MathFunctions.cc  
		 |  
		 +--- MathFunctions.h  
		 
add_subdirectory(\<dir>)  
指明本项目包含一个子目录，子目录下的CMakeLists.txt 文件和源代码也会被处理  

target_link_libraries(Demo, linkLib)  
表明可执行文件需要连接一个名为linkLib的链接库  

生成链接库  
```c++
add_library (linkLib ${DIR_LIB_SRCS})
```
将目录中的源文件编译为静态链接库        


#### 安装
通过产生Makefile后使用 make install 和 make test来执行。  

首先先在 math/CMakeLists.txt文件里指定 MathFunctions库的安装路径  
```c++
install （TARGETS MathFunctions DESTINATION bin)
install (FILES MathFunctions.h DESTINATION include)
```

指明 MathFunctions 库的安装路径。之后同样修改根目录的 CMakeLists 文件，在末尾添加下面几行：  

```c++
install (TARGETS Demo DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include)
```

通过上面的定制，生成的 Demo 文件和 MathFunctions 函数库 libMathFunctions.o    
文件将会被复制到 /usr/local/bin 中，而 MathFunctions.h 和生成的 config.h    
文件则会被复制到 /usr/local/include 中。我们可以验证一下    
顺带一提的是，这里的 /usr/local/ 是默认安装到的根目录，可以通过修改     
CMAKE_INSTALL_PREFIX 变量的值来指定这些文件应该拷贝到哪个根目录  

### 其他问题
一般情况下，我们项目各个子目录都在一个总的项目根目录下，但有的时候，我们需要外部文件夹。  
add_subdirectory 参数binary_dir用来指定source_dir在输出文件夹的位置，如果没有指定，就用source_dir的值。如果想要添加外部文件夹，binary_dir就必须指定，这样，就可以将sorce_dir的输出放在子目录dir.out下了。  
```c++
	add(<dir>, <dir.out>)
```

### 一个例子
```c++
cmake_minimum_required (VERSION 2.6)

INCLUDE_DIRECTORIES(../../thirdparty/comm)

FIND_LIBRARY(COMM_LIB comm ../../thirdparty/comm/lib NO_DEFAULT_PATH)
FIND_LIBRARY(RUNTIME_LIB rt /usr/lib  /usr/local/lib NO_DEFAULT_PATH)

link_libraries(${COMM_LIB} ${RUNTIME_LIB})

ADD_DEFINITIONS(
-O3 -g -W -Wall
 -Wunused-variable -Wunused-parameter -Wunused-function -Wunused
 -Wno-deprecated -Woverloaded-virtual -Wwrite-strings
 -D__WUR= -D_REENTRANT -D_FILE_OFFSET_BITS=64 -DTIXML_USE_STL
)


add_library(lib_demo
        cmd.cpp
        global.cpp
        md5.cpp
)

link_libraries(lib_demo)
add_executable(demo
        main.cpp
)

# link library in static mode
target_link_libraries(demo libuuid.a)
```

## CMakelist.txt 基础

### 自定义变量
SET(HELLO_SRC main.c)
### 变量引用方式
${} 在IF等语句中，直接使用变量名而不通过${}  

### 常用变量
- CMAKE_BINARY_DIR  
- PROJECT_BINARY_DIR  
- <projectname> _BINARY_DIR  
这三个变量指代的内容是一致的，如果是in-source编译，指得就是工程顶层目录；如果是out-of-source编译，指的是工程编译发生的目录。PROJECT_BINARY_DIR跟其它指令稍有区别，目前可以认为它们是一致的。  

- CMAKE_SOURCE_DIR  
- PROJECT_SOURCE_DIR
- <projectname> _SOURCE_DIR
这三个变量指代的内容是一致的，不论采用何种编译方式，都是工程顶层目录。也就是在in-source编译时,他跟CMAKE_BINARY_DIR等变量一致。PROJECT_SOURCE_DIR跟其它指令稍有区别,目前可以认为它们是一致的。   

- CMAKE_CURRENT_SOURCE_DIR
当前处理的CMakeLists.txt所在的路径  

- CMAKE_CURRENT_BINARY_DIR
如果是in-sorce编译，它跟CMAKE_CURRENT_SOURCE_DIR一致；如果是out-of-source编译，指的是target编译目录。使用ADD_SOBDIRECTORY(src bin)可以更改这个变量的值。  

- CMAKE_CURRENT_LIST_FILE
输出调用这个变量的CMakeLists.txt的完整路径  

- CMAKE_MODULE_PATH
这个变量用来定义自己的cmake模块所在的路径。如果工程比较复杂，有可能会自己编写一些cmake模块，这些cmake模块是随工程发布的。 为了让cmake在处理CMakeLists.txt时找到这些模块，你需要通过SET指令将cmake模块路径设置一下。比如SET(CMAKE_MODULE_PATH,${PROJECT_SOURCE_DIR}/cmake)   
这时候就可以通过INCLUDE指令来调用自己的模块了。  

- EXECUTABLE_OUTPUT_PATH
新定义最终结果的存放目录  

- LIBRARY_OUTPUT_PATH
新定义最终结果的存放目录  

- PROJECT_NAME
返回通过PROJECT指令定义的项目名称  

### cmake调用环境变量方式
使用$ENV{HOME}指令就可以调用系统的环境变量了。比如MESSAGE(STATUS "HOME dir:$ENV{HOME})设置环境变量的方式是SET(ENV{变量名}值)  
