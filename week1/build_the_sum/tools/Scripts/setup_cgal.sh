# This script sets up CGAL, enabling some nice features:
# - verification with valgrind
# - nice debugging with gbd (because of debug mode and optimization level O0)
# - all features from helpers.mk

# cleanup
rm -rf CMake* cmake* main Makefile
# create cmake script
cgal_create_cmake_script
# enable c++11 features
echo 'set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")' >> CMakeLists.txt
# disable rounding math check: otherwise valgrind does not work
echo 'set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCGAL_DISABLE_ROUNDING_MATH_CHECK")' >> CMakeLists.txt
# disable optimizations
echo 'set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")' >> CMakeLists.txt
# cmake with debugging enabled
cmake .
cmake -DCMAKE_BUILD_TYPE=Debug .
# append utils to Makefile
echo "include helpers.mk" >> Makefile
