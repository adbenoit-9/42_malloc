#!/bin/sh
echo "\t\033[1;34m***********\033[0m"
echo "\t\033[1;34m** TESTS **\033[0m"
echo "\t\033[1;34m***********\033[0m"

path="../.."
cd tests/minishell 
make re > /dev/null
export LD_LIBRARY_PATH=$path
export LD_PRELOAD=$path/libft_malloc.so
./minishell
# export LD_LIBRARY_PATH=.
# export LD_PRELOAD=libft_malloc.so
# $@
# sh
