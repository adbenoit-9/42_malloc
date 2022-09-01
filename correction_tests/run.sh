#!/bin/sh
path=".."
export LD_LIBRARY_PATH=$path
export LD_PRELOAD=$path/libft_malloc.so
$@
