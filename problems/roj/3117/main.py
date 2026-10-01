#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 18:04
# update_at: 2026-10-01 18:04

import sys
from math import gcd

N, M = 0, 0
cnt: list[int] = []  # cnt[c]：当前窗口里颜色 c 的袜子只数
cur = 0              # 当前窗口内同色袜子对数 C(c,2) 之和


def expand(i: int) -> None:
    """右端点加入第 i 只袜子，登记它与窗口内同色袜子配成的新对。"""
    global cur
    c = a[i]
    cur += cnt[c]     # 新增同色对数 = 窗口内已有该颜色只数
    cnt[c] += 1


def shrink(i: int) -> None:
    """左端点移出第 i 只袜子，撤销它贡献的同色对。"""
    global cur
    c = a[i]
    cnt[c] -= 1
    cur -= cnt[c]     # 先减后撤：剩下的同色只数就是它原来配成的对数


def mo_order(q: list[tuple[int, int, int]]) -> list[tuple[int, int, int]]:
    """把询问按（左端点所在块，右端点）排序：块间从左到右，块内右端点单调。"""
    size = max(1, N // max(1, int(M**0.5)))  # 块长 √(N²/M)，退化为 M=1 也能工作
    return sorted(q, key=lambda x: (x[0] // size, x[1] if x[0] // size % 2 == 0 else -x[1]))


def solve() -> None:
    global N, M, cnt
    data = iter(sys.stdin.buffer.read().split())
    N, M = int(next(data)), int(next(data))
    global a
    a = [int(next(data)) for _ in range(N)]
    cnt = [0] * (max(a) + 1)  # 颜色值域内开计数数组

    # 询问带上原始下标，排完序算完后还能按输入顺序输出
    queries = [(int(next(data)) - 1, int(next(data)) - 1, i) for i in range(M)]

    order = mo_order(queries)
    ans: list[str] = [""] * M

    cur_l, cur_r = 0, -1  # 当前窗口 [cur_l, cur_r]，空窗口用 cur_r < cur_l 表示
    for l, r, i in order:
        while cur_l > l:  # 左端点左移：扩张
            cur_l -= 1
            expand(cur_l)
        while cur_r < r:  # 右端点右移：扩张
            cur_r += 1
            expand(cur_r)
        while cur_l < l:  # 左端点右移：收缩
            shrink(cur_l)
            cur_l += 1
        while cur_r > r:  # 右端点右移：收缩
            shrink(cur_r)
            cur_r -= 1

        total = (r - l + 1) * (r - l) // 2  # 从区间里任取两只袜子的方案数
        same = cur
        if same == 0:
            ans[i] = "0/1"
        else:
            g = gcd(same, total)
            ans[i] = f"{same // g}/{total // g}"

    print("\n".join(ans))


if __name__ == "__main__":
    solve()
