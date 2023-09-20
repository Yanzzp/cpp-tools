# CMake generated Testfile for 
# Source directory: D:/zpy/cpp-tools
# Build directory: D:/zpy/cpp-tools/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[jieba/test/test.run]=] "jieba/test/test.run")
set_tests_properties([=[jieba/test/test.run]=] PROPERTIES  _BACKTRACE_TRIPLES "D:/zpy/cpp-tools/CMakeLists.txt;25;ADD_TEST;D:/zpy/cpp-tools/CMakeLists.txt;0;")
add_test([=[./load_test]=] "./load_test")
set_tests_properties([=[./load_test]=] PROPERTIES  _BACKTRACE_TRIPLES "D:/zpy/cpp-tools/CMakeLists.txt;26;ADD_TEST;D:/zpy/cpp-tools/CMakeLists.txt;0;")
add_test([=[./demo]=] "./demo")
set_tests_properties([=[./demo]=] PROPERTIES  _BACKTRACE_TRIPLES "D:/zpy/cpp-tools/CMakeLists.txt;27;ADD_TEST;D:/zpy/cpp-tools/CMakeLists.txt;0;")
subdirs("jieba/deps")
