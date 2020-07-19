#!/bin/bash
d=$((0))
o=$((0))
p1=$((0))
p2=$((0))
for i in {1..300}; do
  echo ${i}
  ./a.out
  ret=$?
  if [ ${ret} = 0 ]; then
    d=$((${d} + 2))
  elif [ ${ret} = 1 ]; then
    p1=$((${p1} + 1))
    d=$((${d} + 1))
  elif [ ${ret} = 2 ]; then
    p2=$((${p2} + 1))
    d=$((${d} + 1))
  elif [ ${ret} = 10 ]; then
    p1=$((${p1} + 1))
    d=$((${d} + 1))
  elif [ ${ret} = 11 ]; then
    p1=$((${p1} + 2))
  elif [ ${ret} = 12 ]; then
    p1=$((${p1} + 1))
    p2=$((${p2} + 1))
  elif [ ${ret} = 20 ]; then
    p2=$((${p2} + 1))
    d=$((${d} + 1))
  elif [ ${ret} = 21 ]; then
    p1=$((${p1} + 1))
    p2=$((${p2} + 1))
  elif [ ${ret} = 22 ]; then
    p2=$((${p2} + 2))
  else
    o=$((${o} + 1))
  fi
  echo "${d} ${p1} ${p2} ${o}"
done
echo "a"
echo "${d} ${p1} ${p2} ${o}"
