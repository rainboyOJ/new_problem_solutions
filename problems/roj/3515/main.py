#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 04:52
# update_at: 2026-10-02 04:52

import sys

# 马的 8 个跳跃位移（“马走日”）
JUMPS = ((1, 2), (2, 1), (-1, 2), (-2, 1), (1, -2), (2, -1), (-1, -2), (-2, -1))


def solve() -> None:
    n, m, hx, hy = map(int, sys.stdin.buffer.read().split())

    # 马的控制点 = 马所在点 + 8 个跳跃落点；棋盘外的点不会被查到，留在集合里无害
    blocked = {(hx, hy)} | {(hx + dx, hy + dy) for dx, dy in JUMPS}

    # 滚动数组：f[j] = 从 (0,0) 走到“当前行”第 j 列的路径数
    f: list[int] = [0] * (m + 1)
    f[0] = 0 if (0, 0) in blocked else 1
    for i in range(n + 1):
        for j in range(m + 1):
            if (i, j) in blocked:
                f[j] = 0          # 控制点不可通行，路径数清零
            elif j:
                f[j] += f[j - 1]  # f[j] 原值是“从上面来”，f[j-1] 是“从左边来”
    print(f[m])


if __name__ == "__main__":
    solve()
