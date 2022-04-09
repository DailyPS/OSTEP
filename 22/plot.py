#! /usr/bin/env python3
# import os

# import subprocess
import matplotlib.pyplot as plt
import numpy as np

cacheSizes = np.arange(1, 5)
policies = ["FIFO", "LRU", "OPT", "UNOPT", "RAND", "CLOCK"]
hitRates = [
  [56.95, 85.35, 92.04, 96.10],
  [56.95, 89.39, 93.44, 97.17],
  [56.95, 89.67, 95.63, 97.82],
  [56.95, 56.98, 56.99, 57.01],
  [56.95, 84.77, 92.19, 95.41],
  [56.95, 86.04, 92.92, 96.00]
]

for i in range(len(policies)):
  plt.plot(cacheSizes, hitRates[i])

plt.legend(['FIFO', 'LRU', 'OPT', 'UNOPT', 'RAND', 'CLOCK'])
plt.margins(0)
plt.xticks(cacheSizes, cacheSizes)
plt.xlabel('Cache Size')
plt.ylabel('Hit rate')
plt.savefig('ls_policy.png', dpi=227)