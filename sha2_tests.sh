#!/bin/bash

if [ `uname -m` == "x86_64" ]; then
  OPT="-msha -msse4.1"
fi

rm -f ./sha2_tests.txt
for CC in gcc clang; do
 for CFLAGS in -Os -O2 -O3; do
  make CC=$CC CFLAGS="$CFLAGS $OPT" clean all
  echo -e "\nCC=$CC CFLAGS=$CFLAGS" >> ./sha2_tests.txt
  ./sha2_tests -f || exit 111
  ./sha2_tests -b >> ./sha2_tests.txt
 done
done
