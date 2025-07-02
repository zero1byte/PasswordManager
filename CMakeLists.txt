cmake_minimum_required(VERSION 3.10)
project(RSAKeyGen)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main OpenSSL::Crypto)
