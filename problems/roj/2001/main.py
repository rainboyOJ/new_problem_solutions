#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 02:15
# update_at: 2026-10-01 02:18

import sys


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))
    names = [next(data).decode() for _ in range(n)]    # 题面第 2 ~ n+1 行：n 个名字
    index = {name: i for i, name in enumerate(names)}  # 名字 → 编号，查人 O(1)

    money = [0] * n
    for giver in data:                                 # 每组记录以送钱人的名字开头，读到文件末尾
        amount, cnt = int(next(data)), int(next(data))
        share, left = divmod(amount, cnt) if cnt else (0, 0)  # cnt 为 0 时不做除法
        money[index[giver.decode()]] += left - amount  # 送出的钱扣掉，除不尽的余数自己留下
        for _ in range(cnt):
            money[index[next(data).decode()]] += share  # 每位接收者拿到平分的 share

    print('\n'.join(f"{name} {value}" for name, value in zip(names, money)))


if __name__ == "__main__":
    solve()
