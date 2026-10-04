#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 01:23
# update_at: 2026-09-30 01:23

import sys

CM = 100  # 1 米 = 100 厘米：把"精确到厘米"的浮点长度统一放大成整数，避免浮点误差


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n, k = int(next(data)), int(next(data))
    # 每条网线长度精确到厘米：乘 100 并加 0.5 四舍五入，把两位小数的浮点数安全换成厘米整数
    lens = [int(float(next(data)) * CM + 0.5) for _ in range(n)]

    # 二分答案：lo 满足"能切出 k 条"（初值 0 表示最坏切不出 1cm），hi 恒不满足
    lo, hi = 0, max(lens) + 1
    while lo + 1 < hi:
        mid = (lo + hi) // 2
        can_cut = sum(L // mid for L in lens) >= k  # 每条网线按 mid 厘米切，最多 L//mid 段
        if can_cut:
            lo = mid
        else:
            hi = mid

    # lo = 0 表示连 1 厘米都切不出 k 条，按题意输出 0.00
    print(f'{lo / CM:.2f}')


if __name__ == "__main__":
    solve()
