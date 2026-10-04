#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 03:06
# update_at: 2026-10-04 11:41

import sys

State = tuple[int, int, int]  # (a, b, c) 三个桶当前的牛奶量；容量另用同型三元组 caps 表示


def pour(state: State, src: int, dst: int, caps: State) -> State:
    """把 src 桶倒向 dst 桶：倒到 dst 满或 src 空为止。

    倒出的量 = min(src 的存量, dst 还差多少)，这正是「每一次灌注都是完全的」的含义。
    """
    milk = list(state)
    volume = min(milk[src], caps[dst] - milk[dst])
    milk[src] -= volume
    milk[dst] += volume
    return tuple(milk)


def c_when_a_empty(caps: State) -> list[int]:
    """返回 A 桶为空时 C 桶所有可能的存量（升序）。

    从初始状态 (0, 0, C) 出发，沿 6 种倒法做图上搜索；每个状态只入栈一次，
    状态数是 O(A*B)，所以搜索一定结束。
    """
    start: State = (0, 0, caps[2])                # A、B 初始为空，C 装满
    moves = [(s, d) for s in range(3) for d in range(3) if s != d]  # 6 种倒法

    seen: set[State] = {start}
    stack: list[State] = [start]
    while stack:
        state = stack.pop()
        for src, dst in moves:
            nxt = pour(state, src, dst, caps)
            if nxt not in seen:
                seen.add(nxt)
                stack.append(nxt)

    return sorted(c for a, _, c in seen if a == 0)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    A, B, C = next(data), next(data), next(data)   # 题面唯一一行 A B C
    caps: State = (A, B, C)
    print(*c_when_a_empty(caps))


if __name__ == "__main__":
    solve()
