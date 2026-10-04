#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 11:20
# update_at: 2026-10-02 11:20

import sys
from collections import defaultdict

MOD = 10007  # 题面要求的取模值


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    numbers = [next(data) for _ in range(n)]
    colors = [next(data) for _ in range(n)]

    # 三元组 (x,y,z) 要求 x+z=2y，即 x、z 同奇偶，且 color[x]=color[z]。
    # 于是按 (颜色, 下标奇偶) 分桶，每桶统计 [个数 k, 下标和, 数字和, 下标x数字积和]。
    acc: dict[tuple[int, int], list[int]] = defaultdict(lambda: [0, 0, 0, 0])
    for i, (num, col) in enumerate(zip(numbers, colors), 1):
        g = acc[(col, i & 1)]
        g[0] += 1                        # k
        g[1] += i                        # S_i = sum i
        g[2] += num                      # S_a = sum number_i
        g[3] += i * num                  # S_ia = sum i*number_i

    # 桶内无序对 {i,j} 的贡献 (i+j)(a_i+a_j) 求和展开：
    # 每个 i*a_i 在 k-1 个对里各出现一次，i*a_j + j*a_i 交叉项合计 S_i*S_a - S_ia，
    # 合起来即 (k-2)*S_ia + S_i*S_a。
    ans = sum((k - 2) * s_ia + s_i * s_a for k, s_i, s_a, s_ia in acc.values()) % MOD
    print(ans)


if __name__ == "__main__":
    solve()
