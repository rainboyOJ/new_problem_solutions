#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 09:20
# update_at: 2026-10-01 09:26

import sys
from collections.abc import Callable
from operator import and_, or_, xor

type BitOp = Callable[[int, int], int]  # 一扇门的运算：把攻击力与参数 t 按位合成
type Door = tuple[BitOp, int]           # 一扇门 = 运算 + 参数

OPS: dict[bytes, BitOp] = {b'AND': and_, b'OR': or_, b'XOR': xor}


def fold(doors: list[Door], x: int) -> int:
    """把攻击力 x 依次送过所有防御门，返回最终伤害。"""
    for op, t in doors:
        x = op(x, t)
    return x


def best_attack(lo: int, hi: int, m: int) -> int:
    """在 0..m 中选初始攻击力，返回最大伤害。

    lo = f(0)、hi = f(2^B-1)，它们的第 b 位就是第 b 位输入 0 / 输入 1 的输出。
    从高位往低位贪心：输入 0 就有 1 的位白拿，否则预算够且买得到 1 才买。
    """
    ans = a = 0  # ans = 最终伤害；a = 已花掉的预算（构造中的初始攻击力，低位暂为 0）
    for bit in range(max(lo, hi, m).bit_length() - 1, -1, -1):
        free = lo >> bit & 1                    # 输入 0 就已经是 1：白拿，不花预算
        affordable = a + (1 << bit) <= m        # 这一位还买得起吗（高位已定，低位尚为 0）
        buy = not free and affordable and hi >> bit & 1  # 花钱能买到 1 才花，否则放弃
        ans |= (free or buy) << bit             # free / buy 都是真值，位移后就是这一位的值
        a += buy << bit                         # 只有真花钱时才抬高初始攻击力
    return ans


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n, m = int(next(data)), int(next(data))
    doors: list[Door] = [(OPS[next(data)], int(next(data))) for _ in range(n)]

    # 每扇门都是逐位运算，某一位的输出只取决于输入的同一位。于是把 x 的所有位一起摆 1，
    # 一次穿越就同时拿到「每位输入 1 的结果」hi；输入 0 的 lo 同理，两次穿越即可。
    top = max(m, max((t for _op, t in doors), default=0)).bit_length()  # 需要决定的位数
    lo, hi = fold(doors, 0), fold(doors, (1 << top) - 1)

    print(best_attack(lo, hi, m))


if __name__ == "__main__":
    solve()
