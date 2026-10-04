#!/usr/bin/env python3
"""P9237 像素放置：随机生成小棋盘数据，服务于 brute.cpp 与 main.cpp 的对拍。

生成方法：
1. 随机选一个隐藏答案（每格 0/1）；
2. 随机决定哪些格子写数字（数字由隐藏答案算出，所以一定有解）；
3. 用一个小搜索器数解的个数，只接受「解唯一」的棋盘（题面保证解唯一）。

因为 n*m <= 18，brute.cpp 的 2^(nm) 枚举也能在规定时间内跑完。
"""
import random

CELL_MIN = 10         # n*m 的下限，让数据尽量有分量
CELL_MAX = 18         # n*m 的上限，保证 brute.cpp 的 2^(nm) 枚举能跑完
SOLUTION_LIMIT = 2    # 只关心解的个数是否超过 1，数到 2 就可以停
NODE_BUDGET = 400000  # 约束太弱时搜索会爆炸，超出预算就放弃这个棋盘


def count_solutions(n, m, need):
    """统计合法解的数量（最多到 SOLUTION_LIMIT）；搜索超出预算返回 -1。"""
    # tot[i][j]：数字 (i,j) 的 3x3 窗口落在棋盘内的格子总数
    tot = [[0] * (m + 1) for _ in range(n + 1)]
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            r1, r2 = max(1, i - 1), min(n, i + 1)
            c1, c2 = max(1, j - 1), min(m, j + 1)
            tot[i][j] = (r2 - r1 + 1) * (c2 - c1 + 1)

    part = [[0] * (m + 1) for _ in range(n + 1)]   # 窗口内已确定的黑格数
    known = [[0] * (m + 1) for _ in range(n + 1)]  # 窗口内已确定的格子数
    state = [0, 0]                                 # [解的个数, 搜索节点数]

    def window(i, j):
        return (
            range(max(1, i - 1), min(n, i + 1) + 1),
            range(max(1, j - 1), min(m, j + 1) + 1),
        )

    def feasible(i, j):
        rows, cols = window(i, j)
        for r in rows:
            for c in cols:
                d = need[r][c]
                if d < 0:            # 这一格没有数字
                    continue
                if part[r][c] > d:   # 黑格已经超标
                    return False
                if part[r][c] + tot[r][c] - known[r][c] < d:  # 剩下全填黑也不够
                    return False
        return True

    def dfs(dep):
        if state[0] >= SOLUTION_LIMIT or state[1] > NODE_BUDGET:
            return
        if dep == n * m:
            state[0] += 1
            return
        i, j = dep // m + 1, dep % m + 1
        rows, cols = window(i, j)
        for b in (0, 1):
            state[1] += 1
            for r in rows:
                for c in cols:
                    if need[r][c] < 0:
                        continue
                    part[r][c] += b
                    known[r][c] += 1
            if feasible(i, j):
                dfs(dep + 1)
            for r in rows:
                for c in cols:
                    if need[r][c] < 0:
                        continue
                    part[r][c] -= b
                    known[r][c] -= 1
            if state[0] >= SOLUTION_LIMIT or state[1] > NODE_BUDGET:
                return

    dfs(0)
    if state[1] > NODE_BUDGET:
        return -1
    return state[0]


def try_build(n, m, attempts=40):
    """随机造一个棋盘，成功（解唯一）时返回 need 数组，否则返回 None。

    每次尝试都重新抽一个隐藏答案；概率从稀疏到密集，因为数字越多约束越强、
    越容易出现唯一解。"""
    for _ in range(attempts):
        for prob in (0.4, 0.55, 0.7, 0.85, 1.0):
            put = [[False] * (m + 1) for _ in range(n + 1)]
            for i in range(1, n + 1):
                for j in range(1, m + 1):
                    put[i][j] = random.random() < prob
            if not any(any(row) for row in put):
                continue  # 一个数字都没有，必定多解

            sol = [[random.randint(0, 1) for _ in range(m + 1)] for _ in range(n + 1)]
            need = [[-1] * (m + 1) for _ in range(n + 1)]
            for i in range(1, n + 1):
                for j in range(1, m + 1):
                    if not put[i][j]:
                        continue
                    cnt = 0
                    for r in range(max(1, i - 1), min(n, i + 1) + 1):
                        for c in range(max(1, j - 1), min(m, j + 1) + 1):
                            cnt += sol[r][c]
                    need[i][j] = cnt

            if count_solutions(n, m, need) == 1:
                return need
    return None


def pick_size():
    """在 1<=n,m<=10 且 n*m 落在 [CELL_MIN, CELL_MAX] 的范围内随机取一组大小。"""
    pairs = [
        (n, m)
        for n in range(1, 11)
        for m in range(1, 11)
        if CELL_MIN <= n * m <= CELL_MAX
    ]
    if not pairs:  # 理论上不会发生
        pairs = [(n, m) for n in range(1, 11) for m in range(1, 11) if n * m <= CELL_MAX]
    return random.choice(pairs)


def main():
    random.seed()
    n, m = pick_size()
    need = try_build(n, m)
    if need is None:  # 兜底：几乎不会走到这里
        n, m = 2, 2
        need = [[-1] * (m + 1) for _ in range(n + 1)]

    print(n, m)
    for i in range(1, n + 1):
        line = []
        for j in range(1, m + 1):
            line.append('_' if need[i][j] < 0 else str(need[i][j]))
        print(''.join(line))


if __name__ == "__main__":
    main()
