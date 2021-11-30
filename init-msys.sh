#!/usr/bin/bash
#
# ./init-msys2.sh package...
#
# example
#   ./init-msys2.sh gcc cmake
#

pacman -Syu --noconfirm
pacman -Su --noconfirm
pacman -S --noconfirm --needed base-devel git

case "${MSYSTEM}" in
    "MINGW32") TARGET=mingw-w64-i686;;
    "MINGW64") TARGET=mingw-w64-x86_64;;
    "CLANG32")
        sed -i '1s|^|[staging]\nServer = https://repo.msys2.org/staging/\nSigLevel = Never\n[clang32]\nInclude = /etc/pacman.d/mirrorlist.clang32\n|' /etc/pacman.conf
        pacman -Syu
        TARGET=mingw-w64-clang-i686;;
    "CLANG64") TARGET=mingw-w64-clang-x86_64;;
    "CLANGARM64") TARGET=mingw-w64-clang-aarch64;;
    "UCRT64") TARGET=mingw-w64-ucrt-x86_64;;
    *) unset TARGET;;
esac

if [ -n "$TARGET" ]; then
    echo pacman -S --noconfirm --needed $TARGET-toolchain
    pacman -S --noconfirm --needed $TARGET-toolchain
    TARGET=$TARGET-
fi

for pkg in "$@"; do
    echo pacman -S --noconfirm --needed "$TARGET$pkg"
    pacman -S --noconfirm --needed "$TARGET$pkg"
done