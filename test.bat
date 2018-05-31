mkdir build_test;
cd build_test && cmake .. -Dtest_build=TRUE -G"Unix Makefiles" && ctest -V;
pause;