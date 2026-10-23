#!/usr/bin/env python3
"""随机生成 P4606 的输入：连通无向图（允许重边）+ 若干询问点集。

用法：
    python3 gen.py                 # 默认规模，适合对拍
    python3 gen.py 8               # 指定最大点数
    python3 gen.py 100000 200000   # 大实例
"""
import random
import sys


def build_case(max_n, max_q):
    n = random.randint(2, max_n)
    # 先造一棵随机树保证连通，再随机补边（补的边可能是重边，符合题面）
    edges = []
    for v in range(2, n + 1):
        u = random.randint(1, v - 1)
        edges.append((u, v))
    extra = random.randint(0, max(0, n // 2))
    for _ in range(extra):
        u = random.randint(1, n)
        v = random.randint(1, n)
        if u == v:
            continue
        if u > v:
            u, v = v, u
        edges.append((u, v))
    random.shuffle(edges)

    lines = ["%d %d" % (n, len(edges))]
    for u, v in edges:
        lines.append("%d %d" % (u, v))

    q = random.randint(1, max_q)
    lines.append(str(q))
    for _ in range(q):
        k = random.randint(2, n)
        s = random.sample(range(1, n + 1), k)
        s.sort()
        lines.append(" ".join([str(k)] + [str(x) for x in s]))
    return lines


def main():
    if len(sys.argv) >= 3:
        max_n = int(sys.argv[1])
        max_q = int(sys.argv[2])
        cases = 1
    else:
        max_n = int(sys.argv[1]) if len(sys.argv) == 2 else 8
        max_q = 6
        cases = random.randint(1, 2)

    out = [str(cases)]
    for _ in range(cases):
        out.extend(build_case(max_n, max_q))
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
