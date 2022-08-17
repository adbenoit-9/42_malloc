#!/bin/sh
echo "\t\033[1;34m***********\033[0m"
echo "\t\033[1;34m** TESTS **\033[0m"
echo "\t\033[1;34m***********\033[0m"

path="."
export LD_LIBRARY_PATH=$path
export LD_PRELOAD=$path/libft_malloc.so
# export DYLD_LIBRARY_PATH=$PWD
# export DYLD_INSERT_LIBRARIES=$PWD/libft_malloc.so
# export DYLD_FORCE_FLAT_NAMESPACE=1
$@
