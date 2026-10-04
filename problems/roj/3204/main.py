#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 02:00
# update_at: 2026-10-02 02:00

import sys


def row_ids(grid: list[str]) -> tuple[list[list[int]], int]:
    """横向切分：每格所属横向木板编号（干净格为 -1），返回编号表与横向木板总数。"""
    table: list[list[int]] = []
    total = 0
    for row in grid:
        ids: list[int] = []
        seg = -1                    # 正在走的横向段编号，-1 表示还没进入任何段
        for ch in row:
            if ch == '.':
                seg = -1
            elif seg < 0:
                seg = total         # 一块新的横向木板从这里开始
                total += 1
            ids.append(seg)
        table.append(ids)
    return table, total


def column_groups(grid: list[str], rows: list[list[int]]) -> list[list[int]]:
    """纵向木板 → 它压住的横向木板编号列表：每列扫到纵向段首时登记整段。"""
    n, m, groups = len(grid), len(grid[0]), []
    for c in range(m):
        r = 0
        while r < n:
            if grid[r][c] == '.':
                r += 1
                continue
            start = r
            while r < n and grid[r][c] == '*':
                r += 1
            groups.append([rows[i][c] for i in range(start, r)])
    return groups


def min_boards(groups: list[list[int]], row_cnt: int) -> int:
    """匈牙利算法：每个纵向段沿「横向段已配的纵向段」下潜找增广路，返回最大匹配。"""
    match = [-1] * row_cnt   # 横向木板 -> 配到的纵向木板，-1 表示还空着
    total = 0
    for v0 in range(len(groups)):
        seen: set[int] = set()
        # 显式栈代替递归：帧 = [纵向木板, 下一个待试邻居下标, 最近想抢的横向木板]
        stack = [[v0, 0, -1]]
        while stack:
            frame = stack[-1]
            u, i = frame[0], frame[1]
            if i == len(groups[u]):  # 这个纵向木板的所有出路都试过了，回溯
                stack.pop()
                continue
            x = groups[u][i]
            frame[1], frame[2] = i + 1, x
            if x in seen:            # 本轮已访问过的横向木板，再走一次没有新信息
                continue
            seen.add(x)
            if match[x] < 0:         # 撞上空闲横向木板：整条交替路上每个纵向段各拿一段
                for f in reversed(stack):
                    match[f[2]] = f[0]
                total += 1
                break
            stack.append([match[x], 0, x])  # 该横向木板已被占用，顺着它的匹配边走到 match[x]
    return total


def solve() -> None:
    lines = sys.stdin.read().split()
    n, m = int(lines[0]), int(lines[1])
    grid = lines[2:2 + n]
    rows, row_cnt = row_ids(grid)          # 左部顶点：横向木板
    groups = column_groups(grid, rows)     # 右部顶点：纵向木板，邻接 = 压住的横向木板
    # König 定理：二分图最小点覆盖 = 最大匹配，点覆盖里的每个「段」就是一块木板
    print(min_boards(groups, row_cnt))


if __name__ == "__main__":
    solve()
