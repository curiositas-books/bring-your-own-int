cmake_minimum_required(VERSION 3.23)

# Project name and a few useful settings. Other commands can pick up the results
project(CuriositasBiguint
        VERSION 1.0.0
        LANGUAGES CXX)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  # Ensure that no vendor specific extensions are enabled.
  set(CMAKE_CXX_EXTENSIONS OFF)
  # Enable folder support for IDEs.
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  # Enable testing support in main CMakeLists.
  include(CTest)
endif()

add_library(CuriositasBiguint)
target_sources(CuriositasBiguint PUBLIC
               FILE_SET HEADERS
               BASE_DIRS include
               FILES 
               include/curiositas/container/BitVector.hpp
               include/curiositas/math/BigUInt.hpp
               include/curiositas/math/SieveEratosthenes.hpp
               include/curiositas/Types.hpp
              )
target_sources(CuriositasBiguint PRIVATE
               lib/container/BitVector.cpp
               lib/math/BigUInt.cpp
               lib/math/SieveEratosthenes.cpp
              )
target_compile_features(CuriositasBiguint PUBLIC cxx_std_20)

add_executable(sieve_eratosthenes bin/sieve_eratosthenes.cpp)
target_link_libraries(sieve_eratosthenes PRIVATE CuriositasBiguint)

add_executable(collatz_chain bin/collatz_chain.cpp)
target_link_libraries(collatz_chain PRIVATE CuriositasBiguint)

# Enable testing only, if this is the main project. If it is included in a different
# CMake project, it is disabled.
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
  message(STATUS "Setup Testing")
  find_package(Catch2 2 REQUIRED)

  add_executable(container_tests
                 lib/container/Tests.cpp
                 lib/container/BitVector.Tests.cpp)
  target_link_libraries(container_tests PRIVATE Catch2::Catch2 CuriositasBiguint)
  add_test(container_tests container_tests)

  add_executable(math_tests
                 lib/math/Tests.cpp
                 lib/math/BigUInt.Benchmarks.cpp
                 lib/math/BigUInt.Tests.cpp
                 lib/math/SieveEratosthenes.Tests.cpp)
  target_link_libraries(math_tests PRIVATE Catch2::Catch2 CuriositasBiguint)
  add_test(NAME math_tests
           COMMAND math_tests "[test]")
endif()

add_library(Curiositas::Biguint ALIAS CuriositasBiguint)
install(TARGETS CuriositasBiguint sieve_eratosthenes collatz_chain
        EXPORT CuriositasBiguintTargets
        FILE_SET HEADERS DESTINATION include
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)
install(EXPORT CuriositasBiguintTargets
        NAMESPACE Curiositas::
        DESTINATION lib/cmake/curiositas)

include(CMakePackageConfigHelpers)
configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in"
                              "${CMAKE_CURRENT_BINARY_DIR}/CuriositasBiguintConfig.cmake"
                              INSTALL_DESTINATION "lib/cmake/curiositas")
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/CuriositasBiguintVersion.cmake"
                                 COMPATIBILITY SameMajorVersion)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/CuriositasBiguintConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/CuriositasBiguintVersion.cmake"
        DESTINATION "lib/cmake/curiositas")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/CuriositasBiguint.pc.in"
               "${CMAKE_CURRENT_BINARY_DIR}/CuriositasBiguint.pc"
               @ONLY)
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/CuriositasBiguint.pc"
        DESTINATION lib/pkgconfig)
