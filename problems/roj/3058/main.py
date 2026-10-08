# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 10:05
# update_at: 2026-10-08 10:25

import sys
from collections import deque

type Graph = list[list[int]]  # 邻接表，下标 1..n


def solve_one(n: int, p: list[int]) -> str:
    """求一个排列的双栈排序字典序最小操作序列；不可排序返回 "0"。

    p 用 1 起始下标（p[0] 为占位），返回值形如 "a b a c"。
    """
    # 后缀最小值
    min_val = [10**18] * (n + 2)
    for i in range(n, 0, -1):
        min_val[i] = min(min_val[i + 1], p[i])

    # 冲突图：i < j、P_i < P_j、且 j 之后还有比 P_i 小的 ⟹ 两者不能同栈
    adj: Graph = [[] for _ in range(n + 1)]
    for i in range(1, n + 1):
        pi = p[i]
        for j in range(i + 1, n + 1):
            if pi < p[j] and min_val[j + 1] < pi:
                adj[i].append(j)
                adj[j].append(i)

    # 二分染色：每个连通块里下标最小的点染 1（S1），让 'a' 尽量靠前
    color = [0] * (n + 1)
    for s in range(1, n + 1):
        if color[s]:
            continue
        color[s] = 1
        queue = deque([s])
        while queue:
            u = queue.popleft()
            for v in adj[u]:
                if color[v]:
                    if color[v] == color[u]:
                        return "0"
                else:
                    color[v] = 3 - color[u]
                    queue.append(v)

    # 贪心模拟：按 a < b < c < d 尝试；压栈要保持栈内自底向上递减
    s1: list[int] = []
    s2: list[int] = []
    ptr = 1
    want = 1
    ops: list[str] = []
    while want <= n:
        next_value = p[ptr] if ptr <= n else None
        if next_value is not None and color[ptr] == 1 and (not s1 or s1[-1] > next_value):
            s1.append(next_value)
            ops.append("a")
            ptr += 1
        elif s1 and s1[-1] == want:
            s1.pop()
            ops.append("b")
            want += 1
        elif next_value is not None and color[ptr] == 2 and (not s2 or s2[-1] > next_value):
            s2.append(next_value)
            ops.append("c")
            ptr += 1
        elif s2 and s2[-1] == want:
            s2.pop()
            ops.append("d")
            want += 1
        else:
            return "0"  # 理论上不可达
    return " ".join(ops)


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    it = iter(data)
    t = int(next(it))
    out: list[str] = []
    for _ in range(t):
        n = int(next(it))
        p = [0] + [int(next(it)) for _ in range(n)]
        out.append(solve_one(n, p))
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
