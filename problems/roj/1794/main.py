#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 03:26
# update_at: 2026-10-08 03:47

import sys

NEG = -(10 ** 30)                # 不可达哨兵：绝对值远大于任何真实得分

type Line = tuple[int, int]      # 凸包上的一条直线 (斜率 k, 截距 b)
type Hull = list[Line]           # 上凸包，斜率严格递增，支持查询 max(k*x+b)


def hull_add(hull: Hull, k: int, b: int) -> None:
    """往凸包里插入直线 y = kx + b；调用者保证斜率 k 单调递增。"""
    if hull and hull[-1][0] == k:                 # 同斜率只保留截距更大的一条（防御性）
        if hull[-1][1] >= b:
            return
        hull.pop()
    while len(hull) >= 2:
        (k1, b1), (k2, b2) = hull[-2], hull[-1]
        # 中间那条线的最优区间为空 <=> 交点 x(前,中) >= 交点 x(中,新)，化为整数交叉相乘
        mid_is_useless = (b1 - b2) * (k - k2) >= (b2 - b) * (k2 - k1)
        if not mid_is_useless:
            break
        hull.pop()
    hull.append((k, b))


def hull_peak(hull: Hull, x: int) -> int:
    """查询凸包在 x 处的最大值：取值沿下标单峰，二分找峰。"""
    lo, hi = 0, len(hull) - 1
    while lo < hi:
        mid = (lo + hi) >> 1
        if hull[mid][0] * x + hull[mid][1] <= hull[mid + 1][0] * x + hull[mid + 1][1]:
            lo = mid + 1
        else:
            hi = mid
    return hull[lo][0] * x + hull[lo][1]


def build_dp_l(pre: list[int], n: int) -> list[int]:
    """dp_l[i]：只在原序列前缀 1..i 上标记的最大得分（dp_l[0] = 0）。

    转移 = 要么不标记 i，要么拿 [m+1, i] 当最后一段（m = 0 表示从 1 开始，长度为 i-m）。
    把长度平方项展开后，对 m 的部分是直线 y = m*x + c_m 在 x = -i 处取最大值。
    """
    dp_l = [0] * (n + 1)
    hull: Hull = []
    for i in range(1, n + 1):
        m = i - 1
        before = dp_l[m - 1] if m else 0          # m = 0 时左边是空前缀
        hull_add(hull, m, before + pre[m] + m * (m - 1) // 2)
        cand = i * (i + 1) // 2 - pre[i] + hull_peak(hull, -i)
        dp_l[i] = max(dp_l[i - 1], cand)
    return dp_l


def build_dp_r(pre: list[int], n: int) -> list[int]:
    """dp_r[i]：只在原序列后缀 i..n 上标记的最大得分（dp_r[n+1] = dp_r[n+2] = 0）。

    与 dp_l 完全对称，区间写成 [i, j-1]，直线斜率改成 -j、查询点改成 x = i。
    """
    dp_r = [0] * (n + 3)
    hull: Hull = []
    for i in range(n, 0, -1):
        j = i + 1
        hull_add(hull, -j, dp_r[j + 1] - pre[j - 1] + j * (j + 1) // 2)
        cand = pre[i - 1] + i * (i - 1) // 2 + hull_peak(hull, i)
        dp_r[i] = max(dp_r[i + 1], cand)
    return dp_r


def cdq(left: list[int], right: list[int], n: int) -> list[int]:
    """CDQ 分治：mark_best[P] = max{left[a] + right[b] - a*b : a <= P <= b}。

    按 P 落在下标的哪一半，把 "a <= P" 与 "b >= P" 两个条件各自消掉一个：
    P 在左半时 b 自动 >= P，于是只需在右半 b 的凸包里对每个 a 查一次，再对 a 取前缀最大值；
    P 在右半时完全对称，在左半 a 的凸包里对每个 b 查一次，再对 b 取后缀最大值。
    """
    best = [NEG] * (n + 2)
    stack = [(1, n)]                              # 显式栈，规避深递归与递归上限
    while stack:
        lo, hi = stack.pop()
        if lo == hi:
            best[lo] = max(best[lo], left[lo] + right[lo] - lo * lo)
            continue
        mid = (lo + hi) >> 1                      # 左半 [lo,mid]，右半 [mid+1,hi]
        stack.append((lo, mid))
        stack.append((mid + 1, hi))

        hull: Hull = []
        for b in range(hi, mid, -1):              # b 递减使斜率 -b 递增，满足凸包插入顺序
            hull_add(hull, -b, right[b])
        ptr, size = 0, len(hull)
        run = NEG
        for a in range(lo, mid + 1):              # 查询点 x = a 递增，最优下标单调右移
            k, v = hull[ptr]
            here = k * a + v
            while ptr + 1 < size:
                nk, nv = hull[ptr + 1]
                step = nk * a + nv
                if step < here:
                    break
                ptr += 1
                here = step
            run = max(run, left[a] + here)
            best[a] = max(best[a], run)           # 前缀最大值覆盖所有 a <= P

        hull = []
        for a in range(mid, lo - 1, -1):          # a 递减使斜率 -a 递增
            hull_add(hull, -a, left[a])
        ptr, suf = len(hull) - 1, NEG
        for b in range(hi, mid, -1):              # 查询点 x = b 递减，最优下标单调左移
            k, v = hull[ptr]
            here = k * b + v
            while ptr > 0:
                nk, nv = hull[ptr - 1]
                step = nk * b + nv
                if step < here:
                    break
                ptr -= 1
                here = step
            suf = max(suf, right[b] + here)
            best[b] = max(best[b], suf)           # 后缀最大值覆盖所有 b >= P
    return best


def build_mark_best(dp_l: list[int], dp_r: list[int], pre: list[int], n: int) -> list[int]:
    """mark_best[P]：原序列中强制标记位置 P 时的最大得分。

    覆盖 P 的区间 [a,b] 贡献 dp_l[a-2] + f(a,b) + dp_r[b+2] = left[a] + right[b] - a*b，
    于是 mark_best[P] = max{left[a] + right[b] - a*b : a <= P <= b}，交给 cdq 求解。
    """
    left = [0] * (n + 1)                          # 区间左端 a 的贡献，含 dp_l[a-2]
    right = [0] * (n + 1)                         # 区间右端 b 的贡献，含 dp_r[b+2]
    for a in range(1, n + 1):
        left[a] = (dp_l[a - 2] if a >= 2 else 0) + pre[a - 1] + (a * a - 3 * a) // 2
    for b in range(1, n + 1):
        right[b] = dp_r[b + 2] - pre[b] + (b * b + 3 * b + 2) // 2
    return cdq(left, right, n)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    t = [0] + [next(data) for _ in range(n)]
    pre = [0] * (n + 1)
    for i in range(1, n + 1):
        pre[i] = pre[i - 1] + t[i]

    dp_l = build_dp_l(pre, n)
    dp_r = build_dp_r(pre, n)
    mark_best = build_mark_best(dp_l, dp_r, pre, n)

    m = next(data)
    out = []
    for _ in range(m):
        p, x = next(data), next(data)
        # 不被覆盖时 T[p] 的值无关紧要；被覆盖时整段和多出 x - t[p]，得分等量减少
        uncovered = dp_l[p - 1] + dp_r[p + 1]
        covered = mark_best[p] - x + t[p]
        out.append(max(0, uncovered, covered))
    sys.stdout.write('\n'.join(map(str, out)) + '\n')


if __name__ == "__main__":
    solve()
