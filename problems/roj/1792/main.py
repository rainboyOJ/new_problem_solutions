#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 03:23
# update_at: 2026-10-08 03:23

import sys


def min_cost(cost: list[int], grass: list[int]) -> int:
    """返回在最后一个牧场必建控制站时覆盖全部牧场的最小总花费 f[n]。

    转移 f[i] = a_i + i * S1[i] - S2[i] + min_j ( ys[j] - i * xs[j] )，
    其中 xs[j] = S1[j]（b 的前缀和，因 b_k > 0 而严格递增）、
    ys[j] = f[j] + S2[j]（S2 是 k * b_k 的前缀和）。
    查询斜率 i 严格递增，最优决策点在单调队列维护的下凸壳上单调右移，均摊 O(1)。
    """
    n = len(cost) - 1
    f = [0] * (n + 1)  # f[i]：第 i 个牧场建站，且前 i 个牧场都被控制的最小花费
    xs = [0] * (n + 1)  # xs[j]：决策点横坐标，即 b 的前缀和 S1[j]，严格递增
    ys = [0] * (n + 1)  # ys[j]：决策点纵坐标，即 f[j] + S2[j]
    q = [0] * (n + 1)  # 下凸壳上的决策点下标，队头到队尾横坐标递增、相邻斜率递增
    head, tail = 0, 1  # 队列区间 [head, tail)，初始只有虚拟起点 j = 0
    s1 = s2 = 0        # s1 = S1[i]，s2 = S2[i]，随扫描增量维护
    for i in range(1, n + 1):
        s1 += grass[i]
        s2 += i * grass[i]

        # 队头：斜率 i 下若后者已不劣于前者，则前者之后再也不会被选中
        while head + 1 < tail:
            u, v = q[head], q[head + 1]
            still_worse = ys[v] - ys[u] > i * (xs[v] - xs[u])
            if still_worse:
                break
            head += 1
        j = q[head]

        f[i] = cost[i] + i * s1 - s2 + ys[j] - i * xs[j]
        xs[i], ys[i] = s1, f[i] + s2

        # 队尾：新点落在队尾两点连线上方（上凸）时，队尾点永不可能最优
        while head + 1 < tail:
            u, v = q[tail - 2], q[tail - 1]
            upper = (ys[v] - ys[u]) * (xs[i] - xs[v]) >= (ys[i] - ys[v]) * (xs[v] - xs[u])
            if not upper:
                break
            tail -= 1
        q[tail] = i
        tail += 1

    return f[n]  # 最东边的牧场只能自建站才被覆盖，故答案就是 f[n]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)                                # 牧场数目
    cost = [0] + [next(data) for _ in range(n)]   # cost[i] = a_i，建站花费
    grass = [0] + [next(data) for _ in range(n)]  # grass[i] = b_i，放养量
    print(min_cost(cost, grass))


if __name__ == "__main__":
    solve()
