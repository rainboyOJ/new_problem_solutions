import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
answers = []

for _ in range(next(data)):
    constraints = [(next(data), next(data), next(data)) for _ in range(next(data))]
    parent = {x: x for constraint in constraints for x in constraint[:2]}
    size = dict.fromkeys(parent, 1)

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    def union(x, y):
        x, y = find(x), find(y)
        if x == y:
            return
        if size[x] < size[y]:
            x, y = y, x
        parent[y] = x
        size[x] += size[y]

    for x, y, equal in constraints:
        if equal:
            union(x, y)

    answers.append("YES" if all(
        equal or find(x) != find(y) for x, y, equal in constraints
    ) else "NO")

print("\n".join(answers))
