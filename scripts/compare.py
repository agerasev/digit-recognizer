#!python

import sys

if len(sys.argv) < 3:
	raise Exception('too few args. use "python compare.py file1"')

files = [open(sys.argv[1]), open(sys.argv[2])]

set = []
for f in files:
	lines = []
	set.append(lines)
	for l in f:
		nums = l.strip().split()
		array = []
		lines.append(array)
		for n in nums:
			array.append(float(n))

costs = []
for j in range(len(set[0])):
	cost = 0.0
	for i in range(len(set[0][j])):
		cost += (set[0][j][i] - set[1][j][i])**2
	costs.append(cost)

print(costs)
