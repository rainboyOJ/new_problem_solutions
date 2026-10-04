#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 23:58
# update_at: 2026-10-01 23:58

import sys

A_CODE = 65  # 'A' 的 ASCII 码，变量编号 = 字母 - A_CODE


def closure(bits: list[int], n: int) -> list[int]:
    """把邻接位图原地扩成传递闭包：bits[i] 第 j 位为 1 表示已知 i < j（含 i = j）。

    逐个把点 k 当一次中转站：凡是能到 k 的点，把 k 的出边整条并进来。
    自环位一开始就置上，所以补完闭包后"是否成环"与"每个点能到达几个点"都能直接读出来。
    """
    for k in range(n):
        bit = 1 << k
        for i in range(n):
            if bits[i] & bit:
                bits[i] |= bits[k]
    return bits


def ordered(bits: list[int], n: int) -> str | None:
    """位图构成全序时返回输出串（由小到大），否则返回 None。

    无环时"i 能到达几个点"就是 i 的排名：全序时这 n 个数只能是 1..n；
    反之只要有并列，就说明还存在不可比的两点，尚未定序。
    """
    if len({b.bit_count() for b in bits}) != n:
        return None
    return ''.join(chr(A_CODE + i) for i in sorted(range(n), key=lambda i: -bits[i].bit_count()))


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    pos, out = 0, []

    while (n := int(data[pos])):              # 读到 "0 0" 就结束
        m = int(data[pos + 1])
        pos += 2

        relations: list[bytes] = []
        while len(relations) < m:             # 兼容 "A<B" 与拆成 "A" "<" "B" 的写法
            token = data[pos]
            pos += 1
            if len(token) == 1:
                pos += 1                      # 跳过单独出现的 "<"
                token += b'<' + data[pos]
                pos += 1
            relations.append(token)

        bits = [1 << i for i in range(n)]     # 位图关系，先只保留自环
        for step, relation in enumerate(relations, 1):
            lo, hi = relation[0] - A_CODE, relation[2] - A_CODE
            if bits[hi] >> lo & 1:            # 已知 hi < lo，再加 lo < hi 就成环
                out.append(f"Inconsistency found after {step} relations.")
                break
            bits[lo] |= 1 << hi               # 不等式统一成"小字母 → 大字母"的有向边
            closure(bits, n)
            if (seq := ordered(bits, n)):     # 两两关系都定下来了
                out.append(f"Sorted sequence determined after {step} relations: {seq}.")
                break
        else:
            out.append("Sorted sequence cannot be determined.")

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
