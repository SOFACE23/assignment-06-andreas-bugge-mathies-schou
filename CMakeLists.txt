cmake_minimum_required(VERSION 3.10)
project(template)
include(CTest)

set(CMAKE_CXX_STANDARD 14)

# static checks
# if(MSVC)
#   add_compile_options(/W4 /WX)
# else()
#   add_compile_options(-Wall -Wextra -pedantic -Werror)
# endif()

# set(CMAKE_CXX_CLANG_TIDY
#   clang-tidy;
#   -checks=*;
# )

# set(CMAKE_CXX_CPPCHECK
#   cppcheck;
#   --error-exitcode=1;
# )


find_package(Boost REQUIRED COMPONENTS thread system)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(daytime_server src/daytime_server.cpp)
add_executable(daytime_client src/daytime_client.cpp)
add_executable(image_server src/image_server.cpp)
add_executable(image_client src/image_client.cpp)



target_link_libraries(daytime_server ${BOOST_LIBRARIES} pthread)
target_link_libraries(daytime_client ${BOOST_LIBRARIES} pthread)
target_link_libraries(image_server ${BOOST_LIBRARIES} pthread)
target_link_libraries(image_client ${BOOST_LIBRARIES} pthread)

include_directories(include)
add_executable(main src/main.cpp)
