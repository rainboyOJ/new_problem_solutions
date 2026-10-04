#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 21:03
# update_at: 2026-09-30 21:11

import sys


def ok_each_start(gain: list[int]) -> list[bool]:
    """环形差额序列：判断以每个下标为起点顺推一圈，累计值是否始终不为负。

    起点 i 的整圈前缀分两段：不绕回段 gain[i..n-1] 的前缀最小值 tail（倒序滚动），
    以及绕回段 gain[0..i-1] 的前缀最小值 wrap（正向预处理），绕回段还要先补上
    余量 suffix = gain[i..n-1] 之和；两段更小者就是该起点整圈的最小前缀。
    """
    n = len(gain)
    wrap_min: list[int] = []  # wrap_min[i] = gain[0..i] 的前缀最小值
    run = 0
    for x in gain:
        run += x
        wrap_min.append(run if not wrap_min else min(run, wrap_min[-1]))

    ok = [False] * n
    tail = 0    # 不绕回段的前缀最小值；初值 0 让首项算出 min(x, x+0) = x
    suffix = 0  # 绕回段要接着用的余量 gain[i..n-1] 之和
    for i in range(n - 1, -1, -1):
        x = gain[i]
        tail = min(x, x + tail)               # 从右往左滚动的段内最小前缀
        suffix += x
        wrap = wrap_min[i - 1] if i else 0    # 绕回段 gain[0..i-1] 的最小前缀
        ok[i] = min(tail, suffix + wrap) >= 0
    return ok


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    cw: list[int] = [0] * n   # 顺时针差额 a_i = p_i - d_i
    ccw: list[int] = [0] * n  # 逆时针差额 p_i - d_{i-1}，倒序存放以复用同一判定
    p_first = prev_d = 0
    for i in range(n):
        p, d = next(data), next(data)
        cw[i] = p - d
        if i:
            # 第 i 站的逆时针差额放到倒序下标 n-1-i：只需要上一站的出边 d_{i-1}
            ccw[n - 1 - i] = p - prev_d
        else:
            p_first = p  # b_0 = p_0 - d_{n-1} 要等最后一站的出边读完
        prev_d = d
    ccw[n - 1] = p_first - prev_d

    ok_cw = ok_each_start(cw)
    ok_ccw = ok_each_start(ccw)
    # 原第 i 站逆时针可行 = 倒序数组从下标 n-1-i 出发正推一圈可行
    out = "\n".join(
        "TAK" if ok_cw[i] or ok_ccw[n - 1 - i] else "NIE" for i in range(n)
    )
    sys.stdout.write(out + "\n")


if __name__ == "__main__":
    solve()
