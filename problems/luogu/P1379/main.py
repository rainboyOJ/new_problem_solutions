import sys
from collections import deque


start = b"".join(sys.stdin.buffer.read().split())
target = b"123804765"
neighbors = [tuple(nr * 3 + nc for dr, dc in ((1, 0), (-1, 0), (0, 1), (0, -1))
                   if 0 <= (nr := i // 3 + dr) < 3 and 0 <= (nc := i % 3 + dc) < 3)
             for i in range(9)]
queue = deque([start])
distance = {start: 0}

while queue:
    state = queue.popleft()
    if state == target:
        print(distance[state])
        break
    blank = state.index(48)
    for other in neighbors[blank]:
        next_state = bytearray(state)
        next_state[blank], next_state[other] = next_state[other], next_state[blank]
        next_state = bytes(next_state)
        if next_state not in distance:
            distance[next_state] = distance[state] + 1
            queue.append(next_state)
