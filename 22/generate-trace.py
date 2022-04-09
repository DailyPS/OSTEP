#! /usr/bin/env python
import random
from operator import itemgetter

random.seed(0)
numaddrs = 10
count = {}
addrList = []

while(True):
  for i in range(numaddrs):
    a = int(maxpage * random.random())
    addrList.append(a)

    if a in count:
      count[a] += 1

    else:
      count[a] = 1

  count = sorted(count.items(), key=itemgetter(1), reverse = True)
  count_sum = 0

  for i in range(2):
    count_sum += count[i][1]

  if count_sum / numaddrs >= 0.7:
    break

  else:
    count = {}
    addrList = []

print(addrList)