#!/bin/bash
for a in 00 01 02 03 04 05 06 07
do
  sox $a.wav -b 16 -c 1 -r 40000 -e unsigned-integer $a.raw
  mv -vf ${a}.raw ${a}
#  i=$(xxd -c 2 -p ${a}.raw | awk '{ printf "0x%s, ", $1 }'|sed 's/, $//')
#  echo "const int s_${a}[] = { ${i} };" >${a}.h
  python3 bin2header.py -e -p 16 ${a}

  len=$(grep -o "0x" ${a}.h |tail -n+2|wc -l)
  echo "int _${a}_len=${len};" >>${a}.h
done
