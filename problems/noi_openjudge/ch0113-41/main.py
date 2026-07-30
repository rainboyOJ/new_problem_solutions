from collections import deque

start, target = map(int, input().split(","))
reachable = {start}
queue = deque([start])

while queue:
    value = queue.popleft()
    for next_value in (2 * value + 1, 3 * value + 1):
        if next_value <= target and next_value not in reachable:
            reachable.add(next_value)
            queue.append(next_value)

print("YES" if target in reachable else "NO")
