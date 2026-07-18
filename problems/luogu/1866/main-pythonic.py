import sys
from math import prod

MOD = 1_000_000_007

data = list(map(int, sys.stdin.buffer.read().split()))
limits = sorted(data[1:])
print(prod(max(0, limit - used) for used, limit in enumerate(limits)) % MOD)
