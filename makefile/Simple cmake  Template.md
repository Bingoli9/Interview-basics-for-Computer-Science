## Simple cmake  Template

![886382-20170508204351894-2908588](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/886382-20170508204351894-2908588.png?raw=true)

### Steps

1. automatically build directory

   - bin

   - lib

   - inc 

   - build

2. root directory

   put the main.cpp file into root directory

### CMakeLists.txt

```C++
#设置工程名称
PROJECT(CMAKEDemo)
#自己定制
SET(MY_TARGET demo)
SET(MY_LINK test1 test2)


#设置CMAKE最小版本
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#设置构建类型，及相应的编译选项
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

#设置执行文件输出目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#设置库输出路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

MESSAGE("++++++++++++++Start Build+++++++++++++++++")

#当前目录的文件
AUX_SOURCE_DIRECTORY(. SRC_LIST)
#添加子目录
ADD_SUBDIRECTORY(src)

#头文件搜索目录
INCLUDE_DIRECTORIES(inc)
#链接库搜索路径
LINK_DIRECTORIES(lib)
#设置链接库
#SET(EXTRA_LIBS ${EXTRA_LIBS} test1 test2)
SET(EXTRA_LIBS ${EXTRA_LIBS} ${MY_LINK})

#生成可执行文件
ADD_EXECUTABLE(${MY_TARGET} ${SRC_LIST})
#执行文件链接属性
TARGET_LINK_LIBRARIES(${MY_TARGET} ${EXTRA_LIBS})
```

### build.sh

```C++
#!/bin/bash  

set -e  

PROJ_ROOT=$PWD  
BUILD_ROOT=$PROJ_ROOT  
echo -e "\033[31m Current Build Root: $BUILD_ROOT \033[0m"  



BIN_PATH=$BUILD_ROOT/bin

if [ -d $BIN_PATH ];then
    cd $BIN_PATH
    rm -rf *
    cd ..
else
    mkdir -p $BIN_PATH  
fi

INC_PATH=$BUILD_ROOT/inc

if [ -d $INC_PATH ];then
    cd $INC_PATH
    rm -rf *
    cd ..
else
    mkdir -p $INC_PATH  
fi

#cp without path
#find ./src/ -name "*.h" |xargs -i cp {} ./inc/
DEST_PATH="./inc/"

headers=`find . -name *.h`
#echo $headers

for file in $headers
do
#echo $file
    temp=${file#*/}
    temp=${temp#*/}
    dstfile=$DEST_PATH$temp
    dstpath=${dstfile%/*}
    #echo $dstpath
    [ -d $dstpath ] || mkdir -p  $dstpath

    cp -R $file $dstfile

done

LIB_PATH=$BUILD_ROOT/lib

if [ -d $LIB_PATH ];then
    cd $LIB_PATH
    rm -rf *
    cd ..
else
    mkdir -p $LIB_PATH  
fi

BUILD_PATH=$BUILD_ROOT/build

if [ -d $BUILD_PATH ];then
    cd $BUILD_PATH
    rm -rf *
else
    mkdir -p $BUILD_PATH  
    cd $BUILD_PATH
fi

cmake  $PROJ_ROOT  
make -j4
```

### test1/CMakeLists.txt

```C++
#所有的路径变量都不允许重名
AUX_SOURCE_DIRECTORY(. T1_SRC_LIST)
#设置成静态库
ADD_LIBRARY(test1 ${T1_SRC_LIST})
```

test1/CMakeLists.txt



### test2/CMakeLists.txt、

```C++
AUX_SOURCE_DIRECTORY(. T2_SRC_LIST)
ADD_LIBRARY(test2 ${T2_SRC_LIST})
```

