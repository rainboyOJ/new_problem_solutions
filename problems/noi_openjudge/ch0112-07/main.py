from collections import deque

capacity, word_count = map(int, input().split())
words = map(int, input().split())
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
