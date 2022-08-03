#!/bin/sh
export LD_LIBRARY_PATH=.
export LD_PRELOAD="libft_malloc.so"
# export LD_FORCE_FLAT_NAMESPACE=1

echo "\t\033[1;34m***********\033[0m"
echo "\t\033[1;34m** TESTS **\033[0m"
echo "\t\033[1;34m***********\033[0m"
$@
rm -Rf $@ 2> /dev/null
