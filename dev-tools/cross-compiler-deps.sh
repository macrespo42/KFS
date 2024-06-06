#!/bin/bash

function update_pkgs () {
  sudo apt update
  sudo apt upgrade -y
}

function install_cross_compiler_deps() {
  echo "Installing gcc compiler and make..."
  sudo apt install -y build-essential
  echo "Installing bison..."
  sudo apt install -y bison
  echo "Installing flex..."
  sudo apt install -y flex
  echo "Installing libgmp3-dev..."
  sudo apt install -y libgmp3-dev
  echo "Installing libmpc-dev..."
  sudo apt install -y libmpc-dev
  echo "Installing libmpfr-dev..."
  sudo apt install -y libmpfr-dev
  echo "Installing texinfo..."
  sudo apt install -y texinfo
  echo "Installing libisl-dev..."
  sudo apt install -y libisl-dev
  echo "Installing xorriso"
  sudo apt install -y xorriso
}


function install_source_gcc(){
  wget https://ftp.gnu.org/gnu/gcc/gcc-13.3.0/gcc-13.3.0.tar.xz
  mkdir -p $HOME/src
  tar -C $HOME/src -xvf gcc-13.3.0.tar.xz
  rm gcc-13.3.0.tar.xz
  cd $HOME/src
  mkdir build-gcc
  cd build-gcc
  ../gcc-13.3.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
  make -j$(nproc) all-gcc
  make -j$(nproc) all-target-libgcc
  make install-gcc
  make install-target-libgcc
  
}
function install_source_binutils(){
  wget https://ftp.gnu.org/gnu/binutils/binutils-2.42.tar.xz
  mkdir -p $HOME/src
  tar -C $HOME/src -xvf binutils-2.42.tar.xz
  rm binutils-2.42.tar.xz
  cd $HOME/src
  mkdir build-binutils
  cd build-binutils
  ../binutils-2.42/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
  make
  make install
  cd $HOME

}
function main() {
  update_pkgs
 install_cross_compiler_deps
  install_source_binutils
  install_source_gcc
  
}

main
