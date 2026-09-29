#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 22:00
# update_at: 2026-07-05 22:00

import sys


def next_collatz(n: int) -> tuple[int, str]:
    """返回 n 的下一步结果与等式字符串。"""
    if n & 1:  # 奇数
        m = n * 3 + 1
        return m, f"{n}*3+1={m}"
    m = n >> 1  # 偶数除以 2
    return m, f"{n}/2={m}"


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    n = int(data[0])

    out: list[str] = []
    while n != 1:
        n, line = next_collatz(n)
        out.append(line)
    out.append("End")

    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    solve()
