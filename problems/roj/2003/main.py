#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 02:48
# update_at: 2026-10-01 02:55

import sys


def run_edge(color: list[bool]) -> tuple[list[int], list[int]]:
    """求"可当某种颜色"的极长连续段的两端。

    `color[i]` 为 True 表示第 i 颗能当这种颜色（本色或白珠）。返回 `(start, end)`：
    `start[i]`/`end[i]` 是含 i 的那个连续段的首尾下标，`color[i]` 为 False 时两者
    都是 -1（该格不属于这种颜色）。
    """
    size = len(color)
    start = [0] * size
    for i in range(size):
        if not color[i]:
            start[i] = -1
        elif i and color[i - 1]:
            start[i] = start[i - 1]         # 与左邻同段，继承段首
        else:
            start[i] = i                    # 本色段从这里起头
    end = [0] * size
    for i in range(size - 1, -1, -1):
        if not color[i]:
            end[i] = -1
        elif i + 1 < size and color[i + 1]:
            end[i] = end[i + 1]             # 与右邻同段，继承段尾
        else:
            end[i] = i
    return start, end


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    s = data[1].decode()[:n]

    r = s + s                               # 项链是环：接成两倍当成直线扫
    total = 2 * n
    missing = total + 1

    # next_nonwhite[i]：i 起向右第一颗非白珠；prev_nonwhite[i]：i 起向左第一颗非白珠
    next_nonwhite = [missing] * (total + 1)
    for i in range(total - 1, -1, -1):
        next_nonwhite[i] = i if r[i] != 'w' else next_nonwhite[i + 1]
    prev_nonwhite = [-1] * (total + 1)
    for i in range(total):
        prev_nonwhite[i] = i if r[i] != 'w' else (prev_nonwhite[i - 1] if i else -1)

    # 白珠两色都算，所以"可当红/可当蓝"是两条不同的连续段序列
    as_red = [ch != 'b' for ch in r]
    as_blue = [ch != 'r' for ch in r]
    red_start, red_end = run_edge(as_red)
    blue_start, blue_end = run_edge(as_blue)

    best = 0
    for k in range(n):
        # ---- 顺时针：从 k 出发，遇白珠吸收，直到颜色冲突 ----
        first = k if r[k] != 'w' else next_nonwhite[k]
        if first >= total:                  # 全是白珠
            best = n
            break
        end = red_end if r[first] == 'r' else blue_end
        left = min(end[first] - k + 1, n)
        if left >= n:                       # 整条项链都能收走
            best = n
            break

        budget = n - left                   # 逆时针最多还能收这么多颗
        back = prev_nonwhite[k + n - 1]
        if back < 0:
            right = budget
        else:
            start = red_start if r[back] == 'r' else blue_start
            right = min(k + n - start[back], budget)
        best = max(best, left + right)

    print(best)


if __name__ == "__main__":
    solve()
