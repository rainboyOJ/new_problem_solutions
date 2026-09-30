#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-04-18 10:00
# update_at: 2026-04-18 10:00

import sys

Rect = tuple[int, int, int, int]


def clip(rect: Rect, cover: Rect) -> list[Rect]:
    """计算矩形 rect 被矩形 cover 覆盖后留下的互不相交的子矩形列表。"""
    rx1, ry1, rx2, ry2 = rect
    cx1, cy1, cx2, cy2 = cover

    # 若无交集，rect 完整保留
    if rx2 <= cx1 or rx1 >= cx2 or ry2 <= cy1 or ry1 >= cy2:
        return [rect]

    # 求交集边界
    ix1, iy1 = max(rx1, cx1), max(ry1, cy1)
    ix2, iy2 = min(rx2, cx2), min(ry2, cy2)

    # 用交集四条边将 rect 割裂为至多 4 个不相交小矩形：上、下、左、右
    pieces: list[Rect] = []
    if ry2 > iy2:
        pieces.append((rx1, iy2, rx2, ry2))  # 上方条带
    if ry1 < iy1:
        pieces.append((rx1, ry1, rx2, iy1))  # 下方条带
    if rx1 < ix1:
        pieces.append((rx1, iy1, ix1, iy2))  # 中间左侧
    if rx2 > ix2:
        pieces.append((ix2, iy1, rx2, iy2))  # 中间右侧

    return pieces


def visible_area(target: Rect, covers: list[Rect]) -> int:
    """计算 target 矩形在依次被 covers 中的矩形遮挡后的剩余可见总面积。"""
    pieces = [target]
    for cov in covers:
        pieces = [sub for p in pieces for sub in clip(p, cov)]
        if not pieces:  # 已被完全遮挡
            break
    return sum((x2 - x1) * (y2 - y1) for x1, y1, x2, y2 in pieces)


def solve() -> None:
    lines = sys.stdin.read().split()
    windows: list[tuple[str, Rect]] = []  # 窗体栈：从底到顶排序
    out: list[str] = []

    for line in lines:
        op = line[0]
        args = line[2:-1].split(',')
        wid = args[0]

        if op == 'w':
            x1, y1, x2, y2 = map(int, args[1:])
            rect = (min(x1, x2), min(y1, y2), max(x1, x2), max(y1, y2))
            windows.append((wid, rect))  # 新建窗体自动置顶
        elif op == 't':
            idx = next(i for i, (w, _) in enumerate(windows) if w == wid)
            item = windows.pop(idx)
            windows.append(item)  # 置顶
        elif op == 'b':
            idx = next(i for i, (w, _) in enumerate(windows) if w == wid)
            item = windows.pop(idx)
            windows.insert(0, item)  # 置底
        elif op == 'd':
            idx = next(i for i, (w, _) in enumerate(windows) if w == wid)
            windows.pop(idx)
        elif op == 's':
            idx = next(i for i, (w, _) in enumerate(windows) if w == wid)
            target = windows[idx][1]
            covers = [w[1] for w in windows[idx + 1:]]  # 在其之上的所有窗体
            total = (target[2] - target[0]) * (target[3] - target[1])
            vis = visible_area(target, covers)
            ratio = vis * 100.0 / total
            out.append(f"{ratio:.3f}")

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
