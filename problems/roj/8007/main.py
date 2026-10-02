#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 16:23
# update_at: 2026-10-02 16:23

import sys


def candidates(digits: str, base: int) -> set[int]:
    """把写错的表示按位逐一翻成其他数字，收集所有候选值。

    题目保证恰好错了一个数字：真实表示与写下的表示只有一个数位不同，
    所以候选项 = 每一位取遍其余数字后的所有值（含前导 0，不影响数值）。
    """
    return {
        int(digits[:i] + d + digits[i + 1:], base)
        for i in range(len(digits))
        for d in map(str, range(base))
        if d != int(digits[i])
    }


def solve() -> None:
    two, three = sys.stdin.read().split()
    # 唯一解 = 两个候选集合的唯一交点：既可能来自二进制的修正，也可能来自三进制的修正
    (ans,) = candidates(two, 2) & candidates(three, 3)
    print(ans)


if __name__ == "__main__":
    solve()
