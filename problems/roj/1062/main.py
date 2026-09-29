#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 16:46
# update_at: 2026-09-29 16:57

import sys


def solve() -> None:
    tokens = sys.stdin.buffer.read().split()  # 第 1 个 token 是人数 n，后面跟着 n 个成绩
    n = int(tokens[0])                        # 人数 n 可以为 0，此时没有成绩
    scores = map(int, tokens[1:n + 1])        # 只取前 n 个成绩，惰性产出、不建中间列表
    print(max(scores, default=0))             # 成绩非负，空序列的最高分按 0 计


if __name__ == "__main__":
    solve()
