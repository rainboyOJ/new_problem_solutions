#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 17:42
# update_at: 2026-09-29 17:42

def solve() -> None:
    """读入 n，输出交错调和级数前 n 项和，保留 4 位小数。"""
    n = int(input())
    total = sum((1 if i & 1 else -1) / i for i in range(1, n + 1))
    print(f"{total:.4f}")


if __name__ == "__main__":
    solve()
