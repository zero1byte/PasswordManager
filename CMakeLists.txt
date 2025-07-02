cmake_minimum_required(VERSION 3.10)
project(PasswordManager)

set(CMAKE_CXX_STANDARD 17)

# Add Crypto++ source files (avoid test and benchmark files)
file(GLOB CRYPTOPP_SOURCES
    cryptopp/*.cpp
)

# Remove test.cpp if it exists (optional)
list(REMOVE_ITEM CRYPTOPP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/test.cpp)

# Build your app
add_executable(passwordmanager crypto/index.cpp ${CRYPTOPP_SOURCES})

# Include Crypto++ headers
target_include_directories(passwordmanager PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cryptopp)

