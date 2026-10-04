#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 13:05
# update_at: 2026-09-30 13:05

import sys
from array import array

TOP_BIT = 30  # A_i < 2^31，二进制最高位是第 30 位
ABSENT = 0    # 孩子槽为 0 表示这条边不存在；根固定在下标 1，槽 0 永远空着


def insert(ch: array, x: int) -> None:
    """把 x 的 31 位从高到低插入 01 字典树，缺哪条边就新建哪个节点。"""
    u = 1
    for bit in range(TOP_BIT, -1, -1):
        b = x >> bit & 1
        v = ch[u * 2 + b]
        if v == ABSENT:
            v = len(ch) >> 1          # 两槽一对（下标 2u、2u+1），下一对就是新节点号
            ch.extend((0, 0))
            ch[u * 2 + b] = v
        u = v


def best_xor(ch: array, x: int) -> int:
    """在树上贪心取与 x 异或最大的已插入值：每位优先走与 x 相反的那条边。"""
    u, res = 1, 0
    for bit in range(TOP_BIT, -1, -1):
        b = x >> bit & 1
        v = ch[u * 2 + (b ^ 1)]
        if v == ABSENT:               # 没有相反位可走，只能将就走相同位（该位异或为 0）
            u = ch[u * 2 + b]
        else:
            u = v
            res |= 1 << bit           # 这一位成功取反，对答案贡献 2^bit
    return res


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    nums = list(map(int, data[1:1 + n]))

    ch = array('i', [0, 0, 0, 0])     # int32 平坦数组：0 号空槽 + 1 号根节点
    for x in nums:
        insert(ch, x)

    # 贪心走到的叶子一定是真实插入过的元素，所以 best_xor 的值总能作为某个配对达成；
    # 自己配自己只会得到 0，不会抬高最大值。
    print(max(best_xor(ch, x) for x in nums))


if __name__ == "__main__":
    solve()
