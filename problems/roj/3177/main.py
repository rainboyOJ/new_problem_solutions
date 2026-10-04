#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 23:34
# update_at: 2026-10-01 23:34

import sys
from collections import deque


def min_ops(a: list[int], k: int) -> int:
    """排序后做连续分段 DP，单调队列（斜率优化）求最小总降序代价。

    f[i] = min{ f[j] + (S[i]-S[j]) - (i-j)*a[j] | j <= i-k, f[j] < +inf }，
    整理成 f[i] = S[i] - max{ i*a[j] - c[j] }，其中 c[j] = f[j]-S[j]+j*a[j]；
    max{} 是斜率 a[j] 随 j 递增的直线族、查询点 i 也递增，
    所以用双端队列维护上凸壳，均摊 O(1) 完成一次转移。
    """
    n = len(a)
    S = [0] * (n + 1)
    for i, v in enumerate(a, 1):
        S[i] = S[i - 1] + v  # 前缀和：段 (j, i] 的原始和

    f = [0] * (n + 1)  # f[i]：前 i 个数分成若干长度 >= k 的段的最小代价
    c = [0] * n        # c[j] = f[j]-S[j]+j*a[j]，直线 i*a[j]-c[j] 的截距
    q = deque()        # 决策下标 j；斜率 a[j] 从队头到队尾严格递增
    for i in range(k, n + 1):
        j = i - k  # 段长约束 i-j >= k：决策 j 到此刻才首次合法
        if j == 0 or j >= k:  # 0 < j < k 的前缀切不出合法段，f[j] = +inf，不入队
            cj = f[j] - S[j] + j * a[j]
            while q and a[q[-1]] == a[j] and c[q[-1]] >= cj:
                q.pop()  # 同斜率、截距不更小 → 队尾直线处处被支配
            if not (q and a[q[-1]] == a[j]):  # 同斜率但队尾更优 → 新直线全劣，不入队
                while len(q) >= 2:
                    l2, l1 = q[-2], q[-1]
                    # l1 永远取不到 max ⟺ 它与左右两直线的交点次序颠倒（叉乘免除法）
                    if (c[l1] - c[l2]) * (a[j] - a[l1]) >= (cj - c[l1]) * (a[l1] - a[l2]):
                        q.pop()
                    else:
                        break
                c[j] = cj
                q.append(j)

        # 查询点 i 递增 → 上凸壳的最优直线从队头单调后移
        while len(q) >= 2 and i * a[q[1]] - c[q[1]] >= i * a[q[0]] - c[q[0]]:
            q.popleft()
        f[i] = S[i] - (i * a[q[0]] - c[q[0]])

    return f[n]


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    out: list[str] = []
    T = int(next(data))
    for _ in range(T):
        n, k = int(next(data)), int(next(data))
        a = sorted(int(next(data)) for _ in range(n))  # 题面保证非降序，排序只是保险
        out.append(str(min_ops(a, k)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
