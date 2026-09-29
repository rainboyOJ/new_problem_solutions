#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 17:20
# update_at: 2026-09-29 17:20

import sys

LIMIT = 0.05  # 有效率差超过 5% 才判定为 better / worse


def judge(diff: float) -> str:
    """回答"差值 diff 对应三档判定中的哪一档"。"""
    if diff > LIMIT:
        return "better"
    if -diff > LIMIT:  # x - y > 5%，即 y 落后超过 5%
        return "worse"
    return "same"


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    total, effective = next(data), next(data)
    base = effective / total  # 第一组是鸡尾酒疗法的有效率 x

    out: list[str] = []
    for _ in range(n - 1):
        total, effective = next(data), next(data)
        out.append(judge(effective / total - base))  # y - x：正为新疗法更优

    print("\n".join(out))


if __name__ == "__main__":
    solve()
