#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 02:22
# update_at: 2026-10-08 02:22

import sys
from collections.abc import Iterator

MOD = 1000000007

# 限制子矩形：(x1, x2, y1, y2, v)，横纵坐标都用左闭右开区间，v 是"内部最大值"
type Rect = tuple[int, int, int, int, int]


def submasks(mask: int) -> Iterator[int]:
    """降序产出 mask 的全部非空子掩码（标准 (sub-1)&mask 迭代）。"""
    sub = mask
    while sub:
        yield sub
        sub = (sub - 1) & mask


def build_areas(rects: list[Rect], h: int, w: int) -> list[int]:
    """返回"并集面积表"uni，uni[mask] = mask 里所有子矩形覆盖的格子总数。

    中间量是交集面积表 inter：先对每个掩码直接交边界，再用容斥 Σ(-1)^(|sub|+1)·inter[sub]
    合成并集。格子数最大 h·w = 1e8，用 Python 整数不会溢出。
    """
    n = len(rects)
    inter = [0] * (1 << n)
    for mask in range(1, 1 << n):
        x1, x2, y1, y2 = 1, h + 1, 1, w + 1
        for i, (a, b, c, d, _v) in enumerate(rects):
            if mask >> i & 1:
                x1, x2 = max(x1, a), min(x2, b)
                y1, y2 = max(y1, c), min(y2, d)
        inter[mask] = max(0, x2 - x1) * max(0, y2 - y1)

    uni = [0] * (1 << n)
    for mask in range(1, 1 << n):
        uni[mask] = sum(
            inter[sub] if sub.bit_count() % 2 else -inter[sub] for sub in submasks(mask)
        )
    return uni


def layer_ways(v: int, same: int, lower: int, uni: list[int]) -> int:
    """值为 v 的整层方案数：这层每个限制矩形的内部都必须出现 v。

    只有"上界恰好为 v"的格子能取到 v，它们构成集合 A_v（面积 size，且各层互不相交）。
    对"被强制取不到 v 的矩形集合" T 做容斥：T 覆盖到的格子只能填 1..v-1（面积 forced），
    其余格子仍可填 1..v。v-1 = 0 时 0 的正数次幂为 0，恰好表示"这些格子无处可填"。
    """
    size = uni[same | lower] - uni[lower]
    total = pow(v, size, MOD)
    for t in submasks(same):
        forced = uni[t | lower] - uni[lower]
        one = pow(v - 1, forced, MOD) * pow(v, size - forced, MOD) % MOD
        total += -one if t.bit_count() & 1 else one
    return total % MOD


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        h, w, m, n = next(data), next(data), next(data), next(data)

        rects: list[Rect] = []
        for _ in range(n):
            x1, y1, x2, y2, v = next(data), next(data), next(data), next(data), next(data)
            rects.append((x1, x2 + 1, y1, y2 + 1, v))  # 双闭区间转左闭右开
        rects.sort(key=lambda r: r[4])                  # 按 v 升序，v 小的层先算

        uni = build_areas(rects, h, w)
        ans = pow(m, h * w - uni[-1], MOD)  # 未被任何限制覆盖的格子：随便填 1..m

        lower = 0  # 已处理完的、v 更小的那些限制的掩码
        i = 0
        while i < n:
            v = rects[i][4]
            j, same = i, 0
            while j < n and rects[j][4] == v:  # 同 v 的限制合成一层，一起容斥
                same |= 1 << j
                j += 1
            ans = ans * layer_ways(v, same, lower, uni) % MOD
            if ans == 0:  # 某一层已经不可能满足，再乘下去也还是 0
                break
            lower |= same
            i = j

        out.append(str(ans))

    print("\n".join(out))


if __name__ == "__main__":
    solve()
