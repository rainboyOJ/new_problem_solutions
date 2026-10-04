#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 17:23
# update_at: 2026-09-29 17:23

# 递推：F(0)=0、F(1)=1，F(i)=F(i-1)+F(i-2)。滚动窗口 (a, b) 表示 (F(i-1), F(i))，
# 一次加法和一次元组重绑定即推进一位，含 F(46)=1836311903 在内全在 Python 的 int 里精确。

from functools import reduce  # 用 (a, b) -> (b, a + b) 表示一步递推：F(i)=a+b 就是新元组的第二项
import sys


def fib_step(state: tuple[int, int], _step: int) -> tuple[int, int]:
    """一次递推：当前窗口 (F(i-1), F(i)) 推进到 (F(i), F(i+1))；步数下标不参与计算。"""
    a, b = state
    return b, a + b


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    k = next(data)  # 题面 1 <= k <= 46

    # 种子 (F(0), F(1)) = (0, 1)，推进 k 步后窗口为 (F(k), F(k+1))，首项就是答案。
    answer, _ = reduce(fib_step, range(k), (0, 1))
    print(answer)


if __name__ == "__main__":
    solve()
