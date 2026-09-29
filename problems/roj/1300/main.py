#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:53
# update_at: 2026-09-30 03:53

import sys

# 答案上界：100 层楼、1 个鸡蛋时最坏要扔 100 次
MAX_FLOORS = 100
MAX_EGGS = 10


def build_min_drops() -> list[list[int]]:
    """预计算 f[i][j]：i 层楼、j 个鸡蛋在最坏情况下的最少扔蛋次数。

    f[i][1] = i（只有一个鸡蛋只能从低到高逐层试）；
    j>=2 时在 x 层扔一次：碎了测 [1,x-1] 剩 j-1 个蛋，
    没碎测 [x+1,i] 仍 j 个蛋，取两者最坏再 +1，x 取最小。
    """
    f = [[0] * (MAX_EGGS + 1) for _ in range(MAX_FLOORS + 1)]
    for floors in range(1, MAX_FLOORS + 1):
        f[floors][1] = floors                       # 单蛋：逐层往上扔
        for eggs in range(2, MAX_EGGS + 1):
            # 枚举第一次扔的位置 x（1..floors），取最坏子问题较小者
            f[floors][eggs] = 1 + min(
                max(f[x - 1][eggs - 1], f[floors - x][eggs])
                for x in range(1, floors + 1)
            )
    return f


def solve() -> None:
    f = build_min_drops()
    pairs = [list(map(int, line.split())) for line in sys.stdin if line.strip()]
    print('\n'.join(str(f[n][m]) for n, m in pairs))


if __name__ == "__main__":
    solve()
