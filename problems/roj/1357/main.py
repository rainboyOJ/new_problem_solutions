#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 10:30
# update_at: 2026-10-01 10:30

import sys


def solvable(a: list[int]) -> bool:
    """目标出站序列能否由 1..n 依次入站（车站 C 是栈）得到。"""
    stack: list[int] = []       # 车站 C：栈底是先入站的车厢
    cur = 1                     # 下一节还没进站的车厢编号
    for x in a:
        # 编号不超过 x 的车厢依次入栈；x < cur 时没有新车厢可入，cur 也不能回退
        if x >= cur:
            stack += range(cur, x + 1)
            cur = x + 1
        if not stack or stack.pop() != x:  # x 必须恰好是栈顶才能出站
            return False
    return True


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    a = [next(data) for _ in range(n)]
    print("YES" if solvable(a) else "NO")


if __name__ == "__main__":
    solve()
