import sys

data = list(map(int, sys.stdin.buffer.read().split()))
D, G = data[0], data[1]
garbages = []
idx = 2
for _ in range(G):
    t, f, h = data[idx], data[idx + 1], data[idx + 2]
    idx += 3
    garbages.append((t, f, h))

garbages.sort()

best_escape = 10**9
max_life = 10

def dfs(i, health, height, cur_time):
    global best_escape, max_life
    if height >= D:
        best_escape = min(best_escape, cur_time)
        return
    if i == G:
        max_life = max(max_life, health)
        return
    t, f, h = garbages[i]
    if health < t:
        max_life = max(max_life, health)
        return
    dead_line = health
    dfs(i + 1, health + f, height, t)
    dfs(i + 1, health, height + h, t)

dfs(0, 10, 0, 0)

if best_escape != 10**9:
    print(best_escape)
else:
    print(max_life)
