from collections import Counter, deque


n = int(input())
children = [[] for _ in range(n + 1)]
parent = [0] * (n + 1)

for _ in range(n - 1):
    father, child = map(int, input().split())
    children[father].append(child)
    parent[child] = father

x, y = map(int, input().split())
depth = [0] * (n + 1)
depth[1] = 1
queue = deque([1])
while queue:
    node = queue.popleft()
    for child in children[node]:
        depth[child] = depth[node] + 1
        queue.append(child)

ancestors = set()
node = x
while node:
    ancestors.add(node)
    node = parent[node]

lca = y
while lca not in ancestors:
    lca = parent[lca]

level_count = Counter(depth[1:])
distance = 2 * (depth[x] - depth[lca]) + depth[y] - depth[lca]
print(max(depth), max(level_count.values()), distance, sep="\n")
