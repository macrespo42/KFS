#!/bin/bash

COMMAND=""

if command -v pacman &> /dev/null; then
  echo "Arch based system"
  COMMAND="sudo pacman -S --noconfirm"
else
  echo "apt install based system"
  COMMAND="sudo apt install -y"
fi

function update_pkgs () {
  if command -v pacman &> /dev/null; then
    yes | sudo pacman -Suy
  else
    sudo apt update
    sudo apt upgrade -y
  fi
}

function install_cross_compiler_deps() {
  echo "Installing wget"
  $COMMAND wget
  echo "Installing mtools"
  $COMMAND mtools
  echo "Installing gcc compiler and make..."
  $COMMAND build-essential
  echo "Installing bison..."
  $COMMAND bison
  echo "Installing flex..."
  $COMMAND flex
  echo "Installing libgmp3-dev..."
  $COMMAND libgmp3-dev
  echo "Installing libmpc-dev..."
  $COMMAND libmpc-dev
  echo "Installing libmpfr-dev..."
  $COMMAND libmpfr-dev
  echo "Installing texinfo..."
  $COMMAND texinfo
  echo "Installing libisl-dev..."
  $COMMAND libisl-dev
  echo "Installing xorriso"
  $COMMAND xorriso
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
