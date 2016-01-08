#!/bin/bash

# build/install libc++ under travis-ci

# wget https://cmake.org/files/v3.4/cmake-3.4.1-Linux-x86_64.tar.gz --no-check-certificate
# tar xf cmake-*.tar.gz
# sudo cp -r cmake-*/* /usr/local/.

svn --quiet co http://llvm.org/svn/llvm-project/libcxx/trunk libcxx
mkdir -p libcxx/build
(cd libcxx/build && cmake .. -DLIBCXX_CXX_ABI=libstdc++ -DLIBCXX_CXX_ABI_INCLUDE_PATHS="/usr/include/c++/4.6;/usr/include/c++/4.6/x86_64-linux-gnu")
make -C libcxx/build cxx -j2
sudo cp libcxx/build/lib/libc++.so.1.0 /usr/lib/
sudo cp -r libcxx/build/include/c++/v1 /usr/include/c++/v1/
sudo ln -sf /usr/lib/libc++.so.1.0 /usr/lib/libc++.so
sudo ln -sf /usr/lib/libc++.so.1.0 /usr/lib/libc++.so.1

svn --quiet co http://llvm.org/svn/llvm-project/libcxxabi/trunk libcxxabi
cd libcxxabi/lib
./buildit
sudo cp libc++abi.so.1.0 /usr/lib
sudo ln -s /usr/lib/libc++abi.so.1.0 /usr/lib/libc++abi.so.1
sudo ln -s /usr/lib/libc++abi.so.1 /usr/lib/libc++abi.so
