import sys
from collections import Counter

data = list(map(int, sys.stdin.buffer.read().split()))
n, difference = data[:2]
counts = Counter(data[2:2 + n])

print(sum(count * counts[value + difference] for value, count in counts.items()))
