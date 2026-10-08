#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 21:43
# update_at: 2026-10-08 12:35

import sys

type Rect = tuple[int, int, int, int]  # 一幢建筑 (x1, y1, x2, y2)，左下角格与右上角格
type Span = tuple[int, int, int, int]  # 它禁止的左下角区域 (xl, xr, yl, yr)，y 用半开区间 [yl, yr)


def build_spans(rects: list[Rect], L: int, W: int, H: int) -> list[Span]:
    """边长 L 的正方形左下角局限在 W×H 内；返回落在该域里、真正挡住位置的禁止区域。

    正方形与建筑在 x 方向相交 ⟺ 左下角 x 落在 [x1-L+1, x2]，y 方向同理；
    与可行域求交后为空的对可行域毫无影响，直接丢掉。
    """
    spans = [(max(1, x1 - L + 1), min(W, x2), max(1, y1 - L + 1), min(H + 1, y2 + 1))
             for x1, y1, x2, y2 in rects]
    return [s for s in spans if s[0] <= s[1] and s[2] < s[3]]


def seg_add(l: int, r: int, v: int, cnt: list[int], cov: list[int],
            seglen: list[int], size: int) -> None:
    """单位区间 [l, r) 的覆盖计数加 v（+1 进入 / -1 离开），随后回溯维护 cov。

    迭代式 Klee：先沿两条边界路径打标记，再从边界叶子的父结点各自上行重算到根。
    叶子的孩子恒为 0，且 seglen 越界下标恒为 0，所以不必判叶子。
    """
    left, right = l + size, r + size
    first, last = left >> 1, (right - 1) >> 1
    while left < right:
        if left & 1:
            cnt[left] += v
            cov[left] = seglen[left] if cnt[left] > 0 else cov[left << 1] + cov[left << 1 | 1]
            left += 1
        if right & 1:
            right -= 1
            cnt[right] += v
            cov[right] = seglen[right] if cnt[right] > 0 else cov[right << 1] + cov[right << 1 | 1]
        left >>= 1
        right >>= 1
    for node in (first, last):                      # 两条边界路径的祖先各重算一次
        while node:
            cov[node] = seglen[node] if cnt[node] > 0 else cov[node << 1] + cov[node << 1 | 1]
            node >>= 1


def has_gap(rects: list[Rect], n: int, m: int, L: int) -> bool:
    """边长 L 能否放下：可行域非空且禁止矩形没盖满它（有一列留缝就放得下）。"""
    W, H = n - L + 1, m - L + 1
    if W < 1 or H < 1:                              # 网格里根本排不下 L×L
        return False
    spans = build_spans(rects, L, W, H)
    if not spans:
        return True

    # y 方向坐标压缩：叶子是相邻端点之间的单位区间，共 units 段
    ys = sorted({y for s in spans for y in s[2:]})
    units = len(ys) - 1
    order = {y: i for i, y in enumerate(ys)}
    size = 1
    while size < units:
        size <<= 1
    seglen = [0] * (size << 2)
    seglen[size:size + units] = [ys[i + 1] - ys[i] for i in range(units)]
    for i in range(size - 1, 0, -1):
        seglen[i] = seglen[i << 1] + seglen[i << 1 | 1]
    cnt = [0] * (size << 2)
    cov = [0] * (size << 2)

    adds = sorted((s[0], order[s[2]], order[s[3]]) for s in spans)      # 在 xl 处进入
    rems = sorted((s[1] + 1, order[s[2]], order[s[3]]) for s in spans)  # 在 xr+1 处离开
    total, area, prev = W * H, 0, 1
    ia = ir = 0
    cnt_spans = len(spans)
    while ia < cnt_spans or ir < cnt_spans:
        xa = adds[ia][0] if ia < cnt_spans else W + 1
        xb = rems[ir][0] if ir < cnt_spans else W + 1
        cur = xa if xa < xb else xb
        if cur > prev:                              # 上一段 [prev, cur) 的覆盖已确定
            if cov[1] < H:                          # 有一段整列为空 -> 那里任一点都行
                return True
            area += (cur - prev) * cov[1]
            if area >= total:                       # 可行域已被盖满
                return False
            prev = cur
        while ia < cnt_spans and adds[ia][0] == cur:
            _, yl, yr = adds[ia]
            ia += 1
            seg_add(yl, yr, 1, cnt, cov, seglen, size)
        while ir < cnt_spans and rems[ir][0] == cur:
            _, yl, yr = rems[ir]
            ir += 1
            seg_add(yl, yr, -1, cnt, cov, seglen, size)
    if cov[1] < H:
        return True
    area += (W + 1 - prev) * cov[1]
    return area < total


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    while True:
        n = next(data, None)
        if n is None:                               # 多组数据读到 EOF
            break
        m, p = next(data), next(data)
        # 题面保证给出左下、右上；沿用 main.cpp 的容错：顺序反了也照样收进矩形
        rects: list[Rect] = []
        for _ in range(p):
            x1, y1, x2, y2 = next(data), next(data), next(data), next(data)
            rects.append((min(x1, x2), min(y1, y2), max(x1, x2), max(y1, y2)))

        lo, hi, best = 0, min(n, m), 0
        while lo <= hi:                             # 可行性关于 L 单调，可以二分
            mid = (lo + hi) >> 1
            if has_gap(rects, n, m, mid):
                best, lo = mid, mid + 1
            else:
                hi = mid - 1
        out.append(str(best))
    print("\n".join(out))


if __name__ == "__main__":
    solve()
