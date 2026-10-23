import sys

input = sys.stdin.buffer.readline
n, q = map(int, input().split())

parent = [0] * (n + 1)
for _ in range(n - 1):
    u, v = map(int, input().split())
    parent[v] = u

mark_cnt = [0] * (n + 1)
mark_cnt[1] = 1

ops = []
for _ in range(q):
    parts = input().split()
    op = parts[0].decode()
    u = int(parts[1])
    ops.append((op, u))
    if op == 'C':
        mark_cnt[u] += 1

dsu = [0] * (n + 1)
for i in range(1, n + 1):
    if mark_cnt[i] > 0:
        dsu[i] = i
    else:
        dsu[i] = parent[i]


def find(x):
    path = []
    while dsu[x] != x:
        path.append(x)
        x = dsu[x]
    for node in path:
        dsu[node] = x
    return x


ans = []
for op, u in reversed(ops):
    if op == 'Q':
        ans.append(find(u))
    else:
        mark_cnt[u] -= 1
        if mark_cnt[u] == 0:
            dsu[u] = parent[u]

ans.reverse()
sys.stdout.write('\n'.join(map(str, ans)) + '\n')
