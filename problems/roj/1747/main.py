#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 21:02
# update_at: 2026-10-07 21:08

import sys
from bisect import bisect_right

NONE = -1  # "不存在的位置"：下标从 0 起，-1 比任何真实下标都小，可参与 bisect 的整数比较


def longest_run(a: list[int]) -> int:
    """返回满足"左端严格最小、右端严格最大"的最长区间长度，无解返回 0。

    st_ge 是身高非增的单调栈，栈顶即"左边最后一个身高 >= a[r] 的位置"p(r)；
    st_lt 是身高严格增的单调栈，栈内恰好是"右边界能一直延伸到 r 的所有合法左端"，
    且下标随栈深递增。下标 > p(r) 的最小者既满足 a[l] < a[r]、又满足 a[l] 是 (l, r]
    上的最小值，所以它就是右端固定为 r 时的最优左端。
    """
    st_ge: list[int] = []  # 存下标，身高随栈深非增
    st_lt: list[int] = []  # 存下标，身高随栈深严格增
    ans = 0

    for r, value in enumerate(a):
        while st_ge and a[st_ge[-1]] < value:
            st_ge.pop()  # 身高更矮的挡不住 value，后面再也用不上
        p = st_ge[-1] if st_ge else NONE
        st_ge.append(r)

        while st_lt and a[st_lt[-1]] >= value:
            st_lt.pop()  # 这些左端的右边界到不了 r，区间不可能延长到 r
        st_lt.append(r)

        pos = bisect_right(st_lt, p)  # st_lt 里第一个下标 > p 的位置
        left = st_lt[pos] if pos < len(st_lt) else r  # 没有就退化成 l = r，长度 1 不合法
        if left < r:
            ans = max(ans, r - left + 1)

    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    a = [next(data) for _ in range(n)]

    print(longest_run(a))


if __name__ == "__main__":
    solve()
