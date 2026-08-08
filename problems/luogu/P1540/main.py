import sys
from collections import deque


data = list(map(int, sys.stdin.buffer.read().split()))
capacity, word_count = data[:2]
words = data[2:2 + word_count]
memory = set()
order = deque()
lookups = 0

for word in words:
    if word in memory:
        continue
    lookups += 1
    if len(order) == capacity:
        memory.remove(order.popleft())
    order.append(word)
    memory.add(word)

print(lookups)
