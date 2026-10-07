#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 17:29
# update_at: 2026-10-07 17:33

import sys
from collections import deque

IMPOSSIBLE = "IMPOSSIBLE"  # 目标不可达时的输出文本

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Point = tuple[int, int]   # 棋盘上的一个整数坐标点
type Vectors = list[Point]     # 题面给出的 n 个可走向量


def search(start: Point, target: Point, vecs: Vectors) -> int:
    """BFS 求最少步数：每步加一个向量，返回步数，不可达返回 -1。

    棋盘无限大，但一条最优路径总可以贴着「起点-终点」连线走，于是只让落在
    连线走廊（到连线距离 <= 单步最大长度 sqrt(D)）内的点入队，另额外保留
    起点/终点半径 sqrt(D) 球内的点。走廊长度 O(|dx|+|dy|)、宽度 O(sqrt(D))，
    状态数 O((|dx|+|dy|)*sqrt(D))，远小于全平面。
    """
    sx, sy = start
    tx, ty = target
    # 向量分量全非负时，目标落在起点左下方必然到不了（坐标只会不减）
    if (tx < sx or ty < sy) and all(u >= 0 and v >= 0 for u, v in vecs):
        return -1

    dx, dy = tx - sx, ty - sy                  # 连线方向向量
    mx, my = dy, -dx                           # 连线法向量，与 (dx,dy) 垂直
    const = sy * tx - sx * ty                  # 连线方程 mx*x + my*y + const = 0
    norm = mx * mx + my * my                   # 法向量模长平方，比较距离时约掉
    d = max(x * x + y * y for x, y in vecs)    # 单步最大长度的平方 D

    seen: set[Point] = {start}
    queue: deque[Point] = deque([start])
    step = 0
    while queue:
        for _ in range(len(queue)):            # 按层推进，出一层就把步数加一
            cx, cy = queue.popleft()
            if (cx, cy) == target:
                return step
            for u, v in vecs:
                px, py = cx + u, cy + v
                if (px, py) in seen:
                    continue
                # 起终点附近半径 sqrt(D) 的球内一律保留，兜住「起终点很近」的退化情形
                near_end = ((px - sx) ** 2 + (py - sy) ** 2 <= d
                            or (px - tx) ** 2 + (py - ty) ** 2 <= d)
                ray = (px - sx) * dx + (py - sy) * dy      # 相对起点的投影，<0 表示落到身后
                ahead = (px - tx) * dx + (py - ty) * dy    # 相对终点的投影，>0 表示越过头
                off = (mx * px + my * py + const) ** 2     # 到连线距离平方 * |法向量|^2
                if not near_end and (ray < 0 or ahead > 0 or off > d * norm):
                    continue
                seen.add((px, py))
                queue.append((px, py))
        step += 1
    return -1


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        fx, fy, tx, ty = next(data), next(data), next(data), next(data)
        n = next(data)
        vecs: Vectors = [(next(data), next(data)) for _ in range(n)]

        ans = search((fx, fy), (tx, ty), vecs)
        out.append(str(ans) if ans >= 0 else IMPOSSIBLE)

    print("\n".join(out))


if __name__ == "__main__":
    solve()
