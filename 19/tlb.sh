#!/bin/sh

t=1
a=1
while [ $t -lt 14 ]
do
  ./tlb $a 1000
  t=`expr $t + 1`
  a=`expr $a \* 2`
done