#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    acts = sorted(
        ((next(data), next(data)) for _ in range(n)),
        key=lambda x: x[1],  # 按结束时间升序，为每次选最早结束者做准备
    )

    ans = 0
    last_end = -1  # 礼堂上次被占用的结束时刻；begin_i 非负，-1 表示尚未使用
    for begin, end in acts:
        can_use = begin >= last_end  # 当前活动与已安排的不冲突
        if can_use:
            ans += 1
            last_end = end

    print(ans)


if __name__ == "__main__":
    solve()
