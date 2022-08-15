#!/bin/sh
echo "\t\033[1;34m***********\033[0m"
echo "\t\033[1;34m** TESTS **\033[0m"
echo "\t\033[1;34m***********\033[0m"

export LD_LIBRARY_PATH=.
export LD_PRELOAD=libft_malloc.so

$@
# sh