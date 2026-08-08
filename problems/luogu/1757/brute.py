import sys

data = sys.stdin.buffer.read().split()
m = int(data[0])
n = int(data[1])

items_by_group = {}
idx = 2
for _ in range(n):
    w = int(data[idx]); idx += 1
    v = int(data[idx]); idx += 1
    g = int(data[idx]); idx += 1
    items_by_group.setdefault(g, []).append((w, v))

groups = list(items_by_group.values())
k = len(groups)

ans = 0

def dfs(g_idx, cur_w, cur_v):
    global ans
    if cur_w > m:
        return
    if cur_v > ans:
        ans = cur_v
    if g_idx == k:
        return
    dfs(g_idx + 1, cur_w, cur_v)
    for w, v in groups[g_idx]:
        dfs(g_idx + 1, cur_w + w, cur_v + v)

dfs(0, 0, 0)
print(ans)
