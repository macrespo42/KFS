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

function main() {
  update_pkgs
  install_cross_compiler_deps
}

main
