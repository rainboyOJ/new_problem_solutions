#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 02:26
# update_at: 2026-10-01 02:26


def rotate_cw(g: list[str]) -> list[str]:
    """顺时针旋转 90°：把原图行倒序后按列拼接（新图第 r 行 = 原图第 r 列自下而上）。"""
    return [''.join(row) for row in zip(*g[::-1])]


def solve() -> None:
    words = sys.stdin.read().split()
    n = int(words[0])
    src = words[1:1 + n]        # 转换前图案
    dst = words[1 + n:1 + 2 * n]  # 转换后图案

    r90, r180, r270 = rotate_cw(src), rotate_cw(rotate_cw(src)), rotate_cw(rotate_cw(rotate_cw(src)))
    mirror = [row[::-1] for row in src]  # #4：水平翻转（每行倒序）
    m90, m180, m270 = (rotate_cw(mirror), rotate_cw(rotate_cw(mirror)),
                       rotate_cw(rotate_cw(rotate_cw(mirror))))  # #5 的三种组合

    # 按序号从小到大列出全部候选，序号 5 对应三种"翻转后再旋转"
    candidates = ((1, r90), (2, r180), (3, r270), (4, mirror),
                  (5, m90), (5, m180), (5, m270), (6, src))
    print(next((no for no, pat in candidates if pat == dst), 7))


if __name__ == "__main__":
    import sys
    solve()
