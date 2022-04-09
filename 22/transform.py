#! /usr/bin/env python3

traceFile = open('./ls-trace.txt', 'r')
transformFile = open('./transform.txt', 'w')

for line in traceFile:
    if (not line.startswith('=')):
        vpnFile.write(str((int("0x" + line[3:11], 16) & 0xfffff000) >> 12) + "\n")

traceFile.close()
transformFile.close()