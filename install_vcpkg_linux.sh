#!/usr/bin/env bash

sudo pacman -S vcpkg
git clone https://github.com/microsoft/vcpkg $HOME/.local/share/vcpkg

export VCPKG_ROOT="$HOME/.local/share/vcpkg"


