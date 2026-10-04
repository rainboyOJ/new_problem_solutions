#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 05:52
# update_at: 2026-10-02 05:52

import sys

DAYS = 7     # 周一到周日共 7 天
LIMIT = 8    # 一天上课恰好 8 小时还不算，超过 8 小时才不高兴


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    loads = [next(data) + next(data) for _ in range(DAYS)]  # 每天的总课时（校内 + 妈妈安排）

    worst = max(loads)
    # list.index 取首个最大值，天然满足"同分时输出时间最靠前的一天"
    print(loads.index(worst) + 1 if worst > LIMIT else 0)


if __name__ == "__main__":
    solve()
