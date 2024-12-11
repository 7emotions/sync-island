cmake_minimum_required(VERSION 3.10)

# 项目名称和版本
project(sync-island VERSION 1.0)

# 设置 C++20 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 生成 compile_commands.json 文件
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置头文件路径
include_directories(sync-island)

# 定义安装路径
set(INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include)

# 添加头文件到安装路径
install(DIRECTORY sync-island/ DESTINATION ${INSTALL_INCLUDE_DIR})

# 查找所有测试文件
file(GLOB TEST_SOURCES "test/*.cpp")

# 添加每个测试文件为一个可执行文件
foreach(TEST_SRC ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)  # 获取文件名不带扩展名
    add_executable(${TEST_NAME} ${TEST_SRC})  # 为每个源文件生成一个可执行文件
    # install(TARGETS ${TEST_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)  # 安装可执行文件
endforeach()

# 启用测试
enable_testing()

# 你可以选择使用 CTest 来运行所有的测试
add_custom_target(run_tests COMMAND ${CMAKE_CTEST_COMMAND})
# 其他可能需要的设置
# ...
