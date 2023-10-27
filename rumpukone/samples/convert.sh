#!/bin/bash
for a in 00 01 02 03 04 05 06 07
do
  sox $a.wav -b 16 -c 1 -r 40000 -e unsigned-integer $a.raw
  i=$(xxd -c 2 -p ${a}.raw | awk '{ printf "0x%s, ", $1 }'|sed 's/, $//')
  echo "const unsigned int s_${a}[] = { ${i} };" >${a}.h
  len=$(grep -o "0x" ${a}.h |wc -l)
  echo "int s_${a}_len=${len};" >>${a}.h
done
