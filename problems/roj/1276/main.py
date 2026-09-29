#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 02:53
# update_at: 2026-09-30 02:53

import sys


def edit_distance(a: str, b: str) -> int:
    """把 a 变成 b 的最少操作数：滚动一维 DP，prev 恒指"上一行"。"""
    prev = list(range(len(b) + 1))       # a 空前缀：b[0..j-1] 只能逐个插入
    for i, ca in enumerate(a, 1):
        cur = [i] + [0] * len(b)         # b 空前缀：a[0..i-1] 只能逐个删除
        for j, cb in enumerate(b, 1):
            # 收尾三种选择：删掉 ca、插入 cb、把 ca 对上 cb（相同则零代价）
            cur[j] = prev[j - 1] if ca == cb else 1 + min(prev[j], cur[j - 1], prev[j - 1])
        prev = cur
    return prev[-1]


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    a, b = next(data).decode(), next(data).decode()
    print(edit_distance(a, b))


if __name__ == "__main__":
    solve()
