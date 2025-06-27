#!/usr/bin/env bash

set -e

cc main.c -o gen_tiny_bin
./gen_tiny_bin
rm ./gen_tiny_bin

set -x

./tiny_bin
