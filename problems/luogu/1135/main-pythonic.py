from collections import deque

n, start, target = map(int, input().split())
jumps = [0] + list(map(int, input().split()))
distance = [-1] * (n + 1)
distance[start] = 0
queue = deque([start])

while queue:
    floor = queue.popleft()
    for nxt in (floor - jumps[floor], floor + jumps[floor]):
        if 1 <= nxt <= n and distance[nxt] == -1:
            distance[nxt] = distance[floor] + 1
            queue.append(nxt)

print(distance[target])
