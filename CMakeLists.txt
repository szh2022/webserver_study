# 设置cmake最低版本要求
cmake_minimum_required(VERSION 3.1)
# 项目名称为WevServer ，使用C/C++语言编写
project(WebServer C CXX)

# 设置编译标准为c++11 和 c99
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

# 设置静态库输出位置为当前位置下的lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)

# 添加源文件
add_executable(webserver http_conn.cpp main.cpp)

# 添加pthread链接库
target_link_libraries(webserver pthread)

# 寻找子目录下CMakeLists.txt
add_subdirectory(src) # 进入后所有子目录下的变量都是局部的，父目录看不到


