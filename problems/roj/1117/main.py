#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 19:48
# update_at: 2026-10-04 11:10

import sys

LIMIT = 5001  # 值域上界 5000 也必须是合法下标，所以表长取 5001 而不是 5000


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))                                  # 题面第一行：元素个数

    # seen 按「值」索引登记首次出现；keep 的第 k 格留给「第 k 个首次出现的值」的输出文本，
    # 「谁先出现谁占前面的格」正是本题要求的保序，故无需任何排序。
    seen = bytearray(LIMIT)
    keep = [b''] * LIMIT
    k = 0                                                # 已登记的首次出现个数 = 紧凑前缀长度

    for _ in range(n):                                   # 只取前 n 个 token，多余输入不理会
        token = next(data)
        x = int(token)
        if not seen[x]:                                  # 首次出现：登记，并落到前缀第 k 格
            seen[x] = 1
            keep[k] = token                              # 直接复用输入 token，省一次 str()
            k += 1
        # 非首次出现：什么都不做，等价于把该位置删掉

    sys.stdout.buffer.write(b' '.join(keep[:k]) + b'\n')


if __name__ == "__main__":
    solve()
