#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 20:55
# update_at: 2026-10-01 20:55

import sys

MOD = 10**9


def solve() -> None:
    text = sys.stdin.buffer.read().strip().decode()
    n = len(text)

    # dp[i][j]：s[i..j] 单独作为一棵子树（连同它的遍历序列）的方案数。
    # 长度偶数时不可能自成一棵子树（进入/退出成对），初值全为 0。
    dp = [[0] * n for _ in range(n)]
    for i in range(n):
        dp[i][i] = 1  # 单个房间，进出各记一次

    for span in range(3, n + 1, 2):
        for i in range(n - span + 1):
            j = i + span - 1
            if text[i] != text[j]:
                continue  # 进入与退出记录的颜色必须都是根色
            root = text[i]
            left = dp[i + 1]  # 剥掉根之后的内部序列，行下标固定，先取出来省一层索引
            total = 0
            # 切分点 k：第一棵子树占 s[i+1..k-1]，它自身的根色也是 root；
            # 剩下 s[k..j] 是同一层的其它子树（可以有多棵），由 dp[k][j] 收口。
            for k in range(i + 2, j + 1):
                if text[k] == root:
                    total += left[k - 1] * dp[k][j]
            dp[i][j] = total % MOD

    print(dp[0][n - 1] if n else 0)


if __name__ == "__main__":
    solve()
