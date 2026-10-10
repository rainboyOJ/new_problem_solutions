#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:39
# update_at: 2026-10-07 15:39

import sys
from itertools import islice

# 一箱里放 k 个 3*3（k = 0,1,2,3）之后，还能塞下的 2*2 个数
LEFT_FOR_TWO = (0, 5, 3, 1)

END = (0, 0, 0, 0, 0, 0)  # 输入结束标志：六个 0 的一行
ORDER_LEN = 6                # 每个订单占 6 个整数（1*1 到 6*6）

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Order = tuple[int, ...]  # 一个订单的六个型号数量（1*1 到 6*6）


def ceil_div(a: int, b: int) -> int:
    """向上取整的整数除法。"""
    return -(-a // b)


def min_boxes(order: Order) -> int:
    """求一个订单所需的最小包裹数。"""
    c1, c2, c3, c4, c5, c6 = order

    # 6*6、5*5、4*4 各占一个包裹，3*3 每四个占一个
    boxes = c6 + c5 + c4 + ceil_div(c3, 4)
    # 已开的箱子里被大件腾出来的 2*2 槽位：5*5 旁只能放 1*1，4*4 旁能放 5 个，
    # 3*3 按每箱剩余 0/1/2/3 个分别是 LEFT_FOR_TWO 里的 0/5/3/1
    two_slots = 5 * c4 + LEFT_FOR_TWO[c3 % 4]
    # 槽位不够就再开新箱（每箱 9 个 2*2），够则为 0
    boxes += max(0, ceil_div(c2 - two_slots, 9))
    # 总面积扣掉大件已占的面积（36/25/16/9/4 对应 6*6 ~ 2*2），剩下的全归 1*1
    one_slots = 36 * boxes - 36 * c6 - 25 * c5 - 16 * c4 - 9 * c3 - 4 * c2
    # 剩余空间不够就再开新箱（每箱 36 个 1*1）
    boxes += max(0, ceil_div(c1 - one_slots, 36))
    return boxes


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []

    while True:
        order = tuple(islice(data, ORDER_LEN))  # 一次读满一个订单
        if not order or order == END:   # 六个 0 是结束标志，不产生输出
            break
        out.append(str(min_boxes(order)))

    # 全空输入（只有结束行）不输出任何字符
    sys.stdout.write('\n'.join(out) + ('\n' if out else ''))


if __name__ == "__main__":
    solve()
