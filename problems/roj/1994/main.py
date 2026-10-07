#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 06:59
# update_at: 2026-10-08 06:59

import sys
from itertools import accumulate

NAME = "PVCDB"                      # 输出优先级顺序；位 i（i 从 0 起）对应 NAME[i] 这件乐器
MAXT = 9 * 3600 + 59 * 60 + 59      # 题目给的 hh<=9，最大秒 35999，时间轴只有 36000 秒
LEN = MAXT + 2                      # 差分要在 r+1<=36000 处减一，故多留两格

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type DiffTable = list[list[int]]    # 每件乐器一条差分数组，行下标 = 乐器编号


def to_sec(token: str) -> int:
    """把 hh:mm:ss 折成绝对秒，即 3600*hh + 60*mm + ss。"""
    hh, mm, ss = token.split(':')
    return int(hh) * 3600 + int(mm) * 60 + int(ss)


def build_mask(diff: DiffTable) -> list[int]:
    """差分数组求前缀和，还原成"每一秒的乐器掩码"：位 i 为 1 表示该秒有 NAME[i] 在响。"""
    mask = [0] * LEN
    for instrument, row in enumerate(diff):
        bit = 1 << instrument
        for t, cover in enumerate(accumulate(row)):   # cover = 该秒被多少条记录覆盖
            if cover > 0:                             # 多条记录重叠，只要非零就算在演奏
                mask[t] |= bit
    return mask


def render(mask: int) -> str:
    """把某一秒的掩码渲染成一行答案：按 PVCDB 顺序拼字母，无人演奏则 None。"""
    return ''.join(ch for i, ch in enumerate(NAME) if mask >> i & 1) or "None"


def solve() -> None:
    tokens = iter(sys.stdin.buffer.read().decode().split())

    n = int(next(tokens))
    diff: DiffTable = [[0] * LEN for _ in range(5)]
    for _ in range(n):
        left = to_sec(next(tokens))
        right = to_sec(next(tokens))
        instrument = NAME.index(next(tokens))
        diff[instrument][left] += 1        # 闭区间 [left, right] 区间加一
        diff[instrument][right + 1] -= 1

    mask = build_mask(diff)

    m = int(next(tokens))
    times = [to_sec(next(tokens)) for _ in range(m)]
    print('\n'.join(render(mask[t]) for t in times))


if __name__ == "__main__":
    solve()
