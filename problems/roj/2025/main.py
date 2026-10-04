#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 03:38
# update_at: 2026-10-01 03:38

import sys

PER_LINE = 10  # 题面要求每行输出 10 个编码


def hamming_code(n: int, b: int, d: int) -> list[int]:
    """贪心构造字典序最小的 n 个 b 位编码：每步只接上最小的合法编码。"""
    space = 1 << b  # b 位编码的取值空间 [0, 2^b)
    code = [0]      # 0 一定在某个最优解里：把任意解整体异或上它自己的最小元即可
    for _ in range(n - 1):
        # 只在比当前最大编码更大的一侧扫描，输出天然递增；all(...) 就是两两海明距离校验
        nxt = next(
            (x for x in range(code[-1] + 1, space)
             if all((x ^ y).bit_count() >= d for y in code)),
            None,
        )
        if nxt is None:  # 空间容纳不下 n 个编码，能选几个算几个
            break
        code.append(nxt)
    return code


def solve() -> None:
    n, b, d = map(int, sys.stdin.buffer.read().split())
    code = hamming_code(n, b, d)
    lines = [' '.join(map(str, code[i:i + PER_LINE])) for i in range(0, len(code), PER_LINE)]
    print('\n'.join(lines))


if __name__ == "__main__":
    solve()
