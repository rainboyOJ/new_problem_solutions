#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 09:42
# update_at: 2026-10-02 09:42

import sys

W = 5  # 棋盘横向列数，x ∈ [0, 4]
H = 7  # 棋盘纵向行数，y ∈ [0, 6]

# 局面编码：5 元组，第 x 个元素是第 x 列的颜色序列（从下往上），空格子就是列比 y 短。


def clear_once(cols):
    """消去一次：横行或竖列出现连续三块同色就整组删掉，返回掉落压实后的新局面；无三连返回 None。"""
    mark: set[tuple[int, int]] = set()
    # 每行先补成定长 5，空位用 None 占据（None 不参与同色比较）
    rows = [[col[y] if y < len(col) else None for col in cols] for y in range(H)]

    for y, row in enumerate(rows):
        x = 0
        while x < W:
            k = x
            while k + 1 < W and row[x] is not None and row[k + 1] == row[x]:
                k += 1
            if k - x >= 2:  # 连续段长度 ≥ 3
                mark.update((i, y) for i in range(x, k + 1))
            x = k + 1

    for x, col in enumerate(cols):
        y = 0
        while y < len(col):
            k = y
            while k + 1 < len(col) and col[k + 1] == col[y]:
                k += 1
            if k - y >= 2:
                mark.update((x, i) for i in range(y, k + 1))
            y = k + 1

    if not mark:
        return None
    # 行、列的三连在同一轮里一起删：按列过滤即让被删格上方的方块掉落
    return tuple(
        tuple(color for i, color in enumerate(col) if (x, i) not in mark)
        for x, col in enumerate(cols)
    )


def slide(cols, x: int, y: int, d: int):
    """把 (x, y) 的方块横向拖 d 格并结算消除连锁；不合法或局面不变时返回 None。"""
    x2 = x + d
    if x2 < 0 or x2 >= W or y >= len(cols[x]):  # 出界或该格没方块
        return None

    src, dst = list(cols[x]), list(cols[x2])
    if y < len(dst):
        if src[y] == dst[y]:  # 换的是同色方块，局面完全不变，属于无效移动
            return None
        src[y], dst[y] = dst[y], src[y]  # 目标位置有方块：原地交换
    else:
        dst.append(src.pop(y))  # 目标为空：从竖列抽出，落到目标列顶（目标列必不高于 y）

    moved = list(cols)
    moved[x], moved[x2] = tuple(src), tuple(dst)
    nxt = tuple(moved)
    while (changed := clear_once(nxt)) is not None:  # 消除后掉落可能再次触发消除
        nxt = changed
    return nxt


def search(cols, depth: int, limit: int, seen: list[set], path: list) -> bool:
    """按字典序 DFS：从第 depth 步的局面出发，恰好用满 limit 步清空棋盘；找到即把路径倒序留在 path。"""
    if depth == limit:
        return not any(cols)  # 只有走满全部步数时清空才算解
    if cols in seen[depth]:  # 同一层的相同局面：先前那次已经搜过全部续接，直接剪掉
        return False
    seen[depth].add(cols)
    for x in range(W):
        for y in range(len(cols[x])):  # y 由小到大，配合外层 x 即字典序
            for d in (1, -1):  # 同一格先向右（1 优先于 -1）
                nxt = slide(cols, x, y, d)
                if nxt is not None and search(nxt, depth + 1, limit, seen, path):
                    path.append((x, y, d))  # 回溯时记录，最后反转成正序
                    return True
    return False


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    steps = next(data)

    columns = []
    for _ in range(W):
        column = []
        while (color := next(data)) != 0:  # 每列以 0 结尾，自下向上
            column.append(color)
        columns.append(tuple(column))

    seen: list[set] = [set() for _ in range(steps)]
    path: list[tuple[int, int, int]] = []
    if search(tuple(columns), 0, steps, seen, path):
        print('\n'.join(f'{x} {y} {d}' for x, y, d in reversed(path)))
    else:
        print(-1)


if __name__ == "__main__":
    solve()
