#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 19:41
# update_at: 2026-10-02 19:41

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)                    # 史莱姆数量
    cap = next(data)                  # 吊桥最大载重
    weight = sorted(next(data) for _ in range(n))    # 排序后最轻/最重才在两端

    # 最重的必须过桥：能和最轻的挤一趟就同乘，否则独占一趟。
    # 每趟耗时都是 1，趟数 = n - 成功同乘的对数，一趟最多消化两只。
    light, heavy = 0, n - 1
    trips = 0
    while light <= heavy:
        trips += 1
        if weight[light] + weight[heavy] <= cap:
            light += 1                 # 最轻的搭上这趟，向内收一格
        heavy -= 1                     # 最重的总是从这趟离开
    print(trips)


if __name__ == "__main__":
    solve()
