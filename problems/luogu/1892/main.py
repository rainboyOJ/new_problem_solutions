import sys


def main():
    data = sys.stdin.buffer.read().split()
    n, m = int(data[0]), int(data[1])
    # x: 人物 x；x+n: 与 x 对立的一侧
    parent = list(range(2 * n + 1))
    size = [1] * (2 * n + 1)

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

    pos = 2
    for _ in range(m):
        relation = data[pos]
        a, b = int(data[pos + 1]), int(data[pos + 2])
        pos += 3
        if relation == b"F":
            # 朋友：只合并真人，不要合并对立侧
            union(a, b)
        else:
            # 敌人：a 与 b 的对立侧同组，b 与 a 的对立侧同组
            # 从而「有共同敌人」的人会落到同一集合
            union(a, b + n)
            union(b, a + n)

    print(len({find(person) for person in range(1, n + 1)}))


if __name__ == "__main__":
    main()
