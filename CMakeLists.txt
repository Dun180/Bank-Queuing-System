cmake_minimum_required(VERSION 3.0.0)
project(BankQueuingSystem VERSION 0.1.0)

include(CTest)
enable_testing()

# add_library(BankQueuingSystem BankQueuingSystem.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)#添加头文件的搜索路径

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
add_subdirectory( samples )