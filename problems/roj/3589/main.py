#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 09:16
# update_at: 2026-10-02 09:16

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, k, p = next(data), next(data), next(data)

    total = [0] * k      # 每种色调已经出现过的客栈数
    valid = [0] * k      # 每种色调中「位置不超过最近一家低价店」的客栈数
    pending: list[int] = []  # 最近一家低价店之后出现的色调，还没计入 valid
    ans = 0

    for _ in range(n):
        color, price = next(data), next(data)
        if price <= p:
            # 本店就是低价店：任何之前的同色客栈与它配对都合法（区间含右端点）
            ans += total[color]
            # 上次低价店到本店之间的客栈，现在都落在最新低价店左侧（含），补计入
            for col in pending:
                valid[col] += 1
            pending.clear()
            valid[color] += 1  # 本店自身也是低价店，对更靠右的客栈可用
        else:
            # 区间内要有低价店，只有位置在最近低价店左侧（含）的同色客栈才可配对
            ans += valid[color]
            pending.append(color)
        total[color] += 1

    print(ans)


if __name__ == "__main__":
    solve()
