#!/bin/bash

for CC in gcc clang; do
 for CFLAGS in -Os -O2 -O3; do
  make CC=$CC CFLAGS=$CFLAGS
  echo -e "\nCC=$CC CFLAGS=$CFLAGS" >> ./sha2_tests.txt
  ./sha2_tests >> ./sha2_tests.txt
 done
done
