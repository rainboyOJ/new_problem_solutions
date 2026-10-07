#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 06:16
# update_at: 2026-10-08 06:16

import sys

CAP = 1e99  # 题面规定的答案上限，超过就原样输出它


def expected_score(n: int, m: int, k: int) -> float:
    """枚举"指定的 i 行 j 列全黑"，求和得到 E[2^(r+c)]（二项式展开消掉容斥）。"""
    choose = [1.0] * (n + 1)  # choose[i] = C(n,i)，最大约 9.4e88，只有 float 装得下
    for i in range(1, n + 1):
        choose[i] = choose[i - 1] * (n - i + 1) / i

    # cover_prob[t] = Π_{p<t} (k-p)/(m-p)，即"指定的 t 个格子全黑"的概率。
    # t > k 时选不出这么多数字，概率为 0，所以这些位置保持初值 0 不必特判。
    cover_prob = [1.0] + [0.0] * (n * n)
    for t in range(1, min(n * n, k) + 1):
        cover_prob[t] = cover_prob[t - 1] * (k - t + 1) / (m - t + 1)

    return sum(
        choose[i] * choose[j] * cover_prob[n * (i + j) - i * j]  # t = ni+nj-ij 格
        for i in range(n + 1)
        for j in range(n + 1)
    )


def solve() -> None:
    n, m, k = map(int, sys.stdin.buffer.read().split())
    print(f"{min(expected_score(n, m, k), CAP):.10e}")


if __name__ == "__main__":
    solve()
