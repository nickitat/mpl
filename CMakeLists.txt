cmake_minimum_required(VERSION 3.2)

set(nickitat_mpl_headers
    ${CMAKE_CURRENT_SOURCE_DIR}/constructible_from/constructible_from.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/safe_types/safe_integer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/safe_types/safe_ptr.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/safe_types/safe_ref.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/type_traits/type_traits.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/type_traits/type_utilities.hpp)

add_library(nickitat_mpl INTERFACE)
target_sources(nickitat_mpl INTERFACE
               "$<BUILD_INTERFACE:${nickitat_mpl_headers}>")
target_include_directories(nickitat_mpl INTERFACE
               $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>)
target_include_directories(nickitat_mpl SYSTEM INTERFACE
               $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include/mpl>)
target_include_directories(nickitat_mpl INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/constructible_from/
        DESTINATION include/mpl/constructible_from
        FILES_MATCHING
        PATTERN "*.hpp"
        PATTERN "*tests.hpp" EXCLUDE)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/safe_types/
        DESTINATION include/mpl/safe_types
        FILES_MATCHING
        PATTERN "*.hpp"
        PATTERN "*tests.hpp" EXCLUDE)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/type_traits/
        DESTINATION include/mpl/type_traits
        FILES_MATCHING
        PATTERN "*.hpp"
        PATTERN "*tests.hpp" EXCLUDE)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/nickitat_mpl-config.cmake
        DESTINATION include/mpl)

if(NICKITAT_MPL_WITH_TESTS)
  add_executable(nickitat_mpl_tests tests/test.cpp)
  target_link_libraries(nickitat_mpl_tests nickitat_mpl)
  target_compile_options(nickitat_mpl_tests PRIVATE -std=c++17)
endif()

# I'm currently using the following script: cmake . -Bbuild
# -DCMAKE_CXX_COMPILER=clang++ -DNICKITAT_MPL_WITH_TESTS=1 && cmake --build
# build
