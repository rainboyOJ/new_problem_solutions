#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 17:54
# update_at: 2026-10-01 17:54

import sys


def union_area(rects: list[tuple[float, float, float, float]]) -> float:
    """所有矩形的面积并：按 x 扫竖边，线段树维护当前竖线上被覆盖的 y 总长度。"""
    ys = sorted({y for _x1, y1, _x2, y2 in rects for y in (y1, y2)})  # 离散化后的 y 坐标
    y_rank = {y: i for i, y in enumerate(ys)}                          # y 坐标 → 下标
    seg_cnt = len(ys) - 1                        # 基本段个数：第 i 段是 [ys[i], ys[i+1]]
    cover_cnt = [0] * (4 * seg_cnt)              # 结点被整段覆盖的次数
    cover_len = [0.0] * (4 * seg_cnt)            # 结点内被覆盖的总长度

    def cover(node: int, nl: int, nr: int, ql: int, qr: int, delta: int) -> None:
        """把基本段区间 [ql, qr] 的覆盖次数加 delta，再回填本结点的覆盖长度。"""
        if ql <= nl and nr <= qr:                # 整段落在同一条竖边的跨度里
            cover_cnt[node] += delta
        else:
            mid = (nl + nr) >> 1
            if ql <= mid:
                cover(node << 1, nl, mid, ql, qr, delta)
            if qr > mid:
                cover(node << 1 | 1, mid + 1, nr, ql, qr, delta)
        if cover_cnt[node]:                      # 被完整覆盖：整段都算
            cover_len[node] = ys[nr + 1] - ys[nl]
        elif nl == nr:                           # 叶子没被覆盖，长度为 0
            cover_len[node] = 0.0
        else:                                    # 否则由两个子结点拼接
            cover_len[node] = cover_len[node << 1] + cover_len[node << 1 | 1]

    edges = sorted(                              # 竖边：左边界 +1、右边界 -1
        (x, y_rank[y1], y_rank[y2] - 1, delta)
        for x1, y1, x2, y2 in rects
        for x, delta in ((x1, 1), (x2, -1))
    )
    area = 0.0
    prev_x = edges[0][0]
    for x, ql, qr, delta in edges:
        area += cover_len[1] * (x - prev_x)      # 区间 [prev_x, x) 用移动前的覆盖长度
        cover(1, 0, seg_cnt - 1, ql, qr, delta)
        prev_x = x
    return area


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    out: list[str] = []
    case = 0

    while (n := int(next(data))) != 0:
        case += 1
        rects = [
            (float(next(data)), float(next(data)), float(next(data)), float(next(data)))
            for _ in range(n)
        ]
        out += [f"Test case #{case}", "Total explored area: %.2f" % union_area(rects), ""]

    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == "__main__":
    solve()
