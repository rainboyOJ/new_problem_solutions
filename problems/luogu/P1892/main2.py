import sys


def main():
    data = sys.stdin.buffer.read().split()
    n, m = int(data[0]), int(data[1])

    # 并查集建「朋友关系图」：同一连通分量 = 必须在同一团伙
    parent = list(range(n + 1))
    size = [1] * (n + 1)

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    def union(a, b):
        a, b = find(a), find(b)
        if a == b:
            return
        if size[a] < size[b]:
            a, b = b, a
        parent[b] = a
        size[a] += size[b]

    # 先记下每个人的敌人列表；朋友直接连边
    enemies = [[] for _ in range(n + 1)]
    pos = 2
    for _ in range(m):
        relation = data[pos]
        a, b = int(data[pos + 1]), int(data[pos + 2])
        pos += 3
        if relation == b"F":
            union(a, b)  # 朋友：图中连一条边
        else:
            enemies[a].append(b)
            enemies[b].append(a)

    # 敌人的敌人是朋友：同一个人的所有敌人两两连边
    for person in range(1, n + 1):
        es = enemies[person]
        if len(es) < 2:
            continue
        first = es[0]
        for other in es[1:]:
            union(first, other)

    # 连通分量个数 = 最多团伙数
    print(len({find(i) for i in range(1, n + 1)}))


if __name__ == "__main__":
    main()
