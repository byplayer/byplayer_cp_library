# how to run unittest

## build gtest libraries

Please run the follow commands.

```bash
cd $PROJECt_ROOT
git submodule update --init
cd test/unittest/googletest
mkdir build
cd build
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_INSTALL_PREFIX=../../gtest ..
make
make install
```

## make and run test

Please run the follow commands.

```bash
cd test/unittest
make test
```
