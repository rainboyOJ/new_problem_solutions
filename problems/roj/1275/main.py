#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 02:51
# update_at: 2026-10-09 14:25

import sys


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))  # n 位数字
    k = int(next(data))  # 切 k 刀
    s = next(data).decode()  # 数字串本身是字符串，不能进 map(int)，否则丢前导 0

    # dp[i]：前 i 位数字用掉当前刀数后能得到的最大乘积
    dp = [0] + [int(s[:i]) for i in range(1, n + 1)]  # 0 刀时整段就是一个因子

    for j in range(1, k + 1):  # 逐刀加入，第 j 层复用第 j-1 层的结果
        # 最后一刀落在第 t 位之后：左半段是上一层的 dp[t]，右半段是子串 s[t:i]
        dp = [
            max((dp[t] * int(s[t:i]) for t in range(j, i)), default=0)
            for i in range(n + 1)
        ]

    print(dp[n])


if __name__ == "__main__":
    solve()
