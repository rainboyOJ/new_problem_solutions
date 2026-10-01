#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:20
# update_at: 2026-10-02 10:20

import sys

# 路线 = 走遍 4×N 个路口、回到邮局的闭合走法，即 4×N 网格上的哈密顿回路。
# 南北向街道只在同一列内连接相邻两行，所以可以从西往东一列一列地决定用哪些边；
# 每个路口度数恰好为 2，于是扫到某条列间切口时只需记住"跨过切口的横边两两配成一组"
# 这一件事，而 4 行之间只有 7 种配得出来的切面：
#
#   ∅、{01}、{03}、{12}、{23}、{01,23}、{03,12}      （数字 = 配对的两行）
#
# 下表是"扫过一列"的转移（行=旧切面，列=新切面，末列=本列收口数）。
#
#           | {03} {01,23} | {01} {23} {12} {03,12} | 收口
#   ∅       |  1     1     |                         |
#   {01}    |  1     1     |                         |
#   {23}    |  1     1     |                         |
#   {01,23} |  1     1     |                         |
#   {12}    |  1           |                         |
#   {03}    |              |  1    1    1    1       |  1
#   {03,12} |              |  1    1         1       |  1


def count_routes(n: int) -> int:
    """4×n 网格上从左上角出发、每个路口恰好经过一次的闭合路线条数。"""
    # 邮局左边的切口：还没有横边跨过来，只有空切面
    empty, s01, s03, s12, s23, s01_23, s03_12 = 1, 0, 0, 0, 0, 0, 0
    for _ in range(n - 1):        # 扫过第 1 … n-1 列；第 n 列右侧没有横边，只能收口
        # 右端全部取旧值；每一行对应上表的一列
        empty, s01, s03, s12, s23, s01_23, s03_12 = (
            0,                                        # 空切面只在第一列左侧存在
            s03 + s03_12,                             # 新 {01}
            empty + s01 + s12 + s23 + s01_23,         # 新 {03}
            s03,                                      # 新 {12}
            s03 + s03_12,                             # 新 {23}
            empty + s01 + s23 + s01_23,               # 新 {01,23}
            s03 + s03_12,                             # 新 {03,12}
        )
    return 2 * (s03 + s03_12)     # 收口处的一条回路，顺时针与逆时针是两条路线


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    n = int(data[0])
    print(count_routes(n))


if __name__ == "__main__":
    solve()
