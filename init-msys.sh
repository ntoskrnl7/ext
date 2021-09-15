#!/usr/bash

pacman -Syu
pacman -Su
pacman -S --needed base-devel git

case "${MSYSTEM}" in
    "MINGW32") pacman -S --needed mingw-w64-i686-toolchain mingw-w64-i686-cmake;;
    "MINGW64") pacman -S --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake;;
    "CLANG32")
        sed -i '1s|^|[staging]\nServer = https://repo.msys2.org/staging/\nSigLevel = Never\n[clang32]\nInclude = /etc/pacman.d/mirrorlist.clang32\n|' /etc/pacman.conf
        pacman -Syu
        pacman -S --needed mingw-w64-clang-i686-toolchain mingw-w64-clang-i686-cmake;;
    "CLANG64") pacman -S --needed mingw-w64-clang-x86_64-toolchain mingw-w64-clang-x86_64-cmake;;
    "CLANGARM64") pacman -S --needed mingw-w64-clang-aarch64-toolchain mingw-w64-clang-aarch64-cmake;;
    "UCRT64") pacman -S --needed mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-cmake;;
    # "MSYS") pacman -S --needed gcc cmake;;
    *) pacman -S --needed gcc cmake;;
esac
