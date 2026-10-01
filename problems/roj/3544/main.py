#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 06:30
# update_at: 2026-10-02 06:30

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)                                   # 题面的 N：生成的随机数个数
    # 集合推导一次完成"去重"，sorted 再完成"排序"，O(N log N)
    uniq = sorted({next(data) for _ in range(n)})

    print(len(uniq))                                 # 去重后的个数 M
    print(*uniq)                                     # 空格分隔的升序结果


if __name__ == "__main__":
    solve()
