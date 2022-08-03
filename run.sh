#!/bin/sh
export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES="libft_malloc.so"
export DYLD_FORCE_FLAT_NAMESPACE=1

echo "\t\033[1;34m-- TESTS --\033[0m"
$@
rm -Rf $@ 2> /dev/null
