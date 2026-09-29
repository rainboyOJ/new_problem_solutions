#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 10:15
# update_at: 2026-10-01 10:15

import sys

METERS = 4500                        # 赛道长度（米）
DIST = METERS * 36 // 10              # 速度是 km/h，换算后 16200：除以 v 恰得骑行秒数


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []

    while (n := next(data)) != 0:  # n = 0 表示输入结束
        arrivals = []  # Charley 可跟随（出发时刻不早于 0）的人的到达时刻
        for _ in range(n):
            v, t = next(data), next(data)  # 速度（km/h）、出发时刻（可为负）
            if t >= 0:
                arrivals.append(t + -(-DIST // v))  # ceil 除法：向上取整的骑行秒数

        out.append(str(min(arrivals, default=999999999)))  # 无人可跟时与参考实现一致

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
