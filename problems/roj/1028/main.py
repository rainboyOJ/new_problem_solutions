#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 14:06
# update_at: 2026-09-29 14:06

import sys

SIZE = 5  # 菱形对角线长：共 5 行，第 2 行（0 起）是最宽的中间行


def diamond(ch: str) -> str:
    """生成 SIZE 行字符菱形：行到中间行的距离就是前导空格数，字符数按 2 倍距离收窄。"""
    return "\n".join(
        " " * (gap := abs(r - SIZE // 2)) + ch * (SIZE - 2 * gap)  # gap = 该行离中间行多远
        for r in range(SIZE)
    )


def solve() -> None:
    ch = sys.stdin.buffer.read().split()[0].decode()  # 输入只含一个字符
    print(diamond(ch))


if __name__ == "__main__":
    solve()
