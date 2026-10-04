#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-28 18:00
# update_at: 2026-09-28 18:00

import sys


def solve() -> None:
    """读取学生人数、分数与姓名，输出最高分的姓名。"""
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    best_score = -1
    best_name = ""
    # 每两项为一组：分数、姓名。
    for i in range(1, 2 * n + 1, 2):
        score = int(data[i])
        name = data[i + 1].decode()
        if score > best_score:
            best_score = score
            best_name = name
    print(best_name)


if __name__ == "__main__":
    solve()
