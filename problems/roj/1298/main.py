#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:53
# update_at: 2026-09-30 03:53

import sys


def distance(a: bytes, b: bytes) -> int:
    """滚动数组版编辑距离：dp[j] = a 的前 i 个字符变成 b 的前 j 个字符的最小代价。"""
    if len(a) < len(b):  # 增与删互为反向操作，距离对称；让内层循环跑在短串上
        a, b = b, a

    dp = list(range(len(b) + 1))  # 第 0 行：空的 a 补齐 b 的前 j 个字符，代价 j
    for i, ca in enumerate(a, 1):
        diag = dp[0]  # 左上角：a 的前 i-1 个字符对上 b 的前 0 个字符
        dp[0] = i     # 第 i 行边界：a 的前 i 个字符整段删空
        for j, cb in enumerate(b, 1):
            old = dp[j]  # 先取出「上」：它马上会被本行覆盖，留给下一格当「左上」
            # 相同则白拿左上角；不同则改一个字符，或删 / 增一个字符再走
            dp[j] = diag if ca == cb else min(diag, old, dp[j - 1]) + 1
            diag = old
    return dp[-1]


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))  # 测试数据的组数
    out: list[str] = []

    for _ in range(n):
        first, second = next(data), next(data)  # 直接按字节比对，免去逐字符解码
        out.append(str(distance(first, second)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
