#!/bin/bash
b=$((0))
w=$((0))
d=$((0))
o=$((0))
for i in {1..3000}; do
  echo ${i}
  ./b.out
  ret=$?
  if [ ${ret} = 0 ] ; then
    d=$((${d}+1))
  elif [ ${ret} = 1 ] ; then
    b=$((${b}+1))
  elif [ ${ret} = 2 ] ; then
    w=$((${w}+1))
  else
    o=$((${o}+1))
  fi
  echo "${d} ${b} ${w} ${o}"
done
  echo "b"
  echo "${d} ${b} ${w} ${o}"
