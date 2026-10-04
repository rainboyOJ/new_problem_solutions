#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 00:46
# update_at: 2026-09-30 00:46

import sys


def max_playing_time(caps: list[int]) -> float:
    """一组电池能玩的最长时间：两个上界取小。

    总上界 total/2：两个槽每小时各耗 1，总耗电 = 2T 不超过总电量。
    上界 total - max：若最大电池独大（max > total/2），它跑满速率 1 也只能贡献 T，
    其余电池的总电量必须撑起另一半且不能中途死光，故 T 不超过其余电量之和。
    """
    total = sum(caps)
    return min(total / 2, total - max(caps))


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    for n in data:  # 多组数据读到 EOF，n 是题面格式里的电池数目
        caps = [next(data) for _ in range(n)]  # 每节电池能用的小时数
        out.append(f"{max_playing_time(caps):.1f}")

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
