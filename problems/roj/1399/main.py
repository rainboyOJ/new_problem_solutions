#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 08:37
# update_at: 2026-09-30 08:37

import sys

THRESHOLD = 37.5  # 初筛体温线，题面明确"含等于 37.5 度"


def solve() -> None:
    tokens = iter(sys.stdin.buffer.read().split())
    n = int(next(tokens))
    flu: list[str] = []  # 按输入顺序收集被初筛为甲流的姓名

    for _ in range(n):
        name = next(tokens).decode()
        temp = float(next(tokens))
        cough = next(tokens) == b'1'  # 是否咳嗽：1 是，0 否
        if temp >= THRESHOLD and cough:
            flu.append(name)

    print('\n'.join(flu + [str(len(flu))]))


if __name__ == "__main__":
    solve()
