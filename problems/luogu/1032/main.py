import sys
from collections import deque


lines = [line.split() for line in sys.stdin.read().splitlines() if line.strip()]
start, target = lines[0]
rules = lines[1:]
queue = deque([(start, 0)])
visited = {start}
answer = None

while queue:
    current, steps = queue.popleft()
    if current == target:
        answer = steps
        break
    if steps == 10:
        continue

    for old, new in rules:
        position = current.find(old)
        while position != -1:
            transformed = current[:position] + new + current[position + len(old):]
            if transformed not in visited:
                visited.add(transformed)
                queue.append((transformed, steps + 1))
            position = current.find(old, position + 1)

print(answer if answer is not None else "NO ANSWER!")
