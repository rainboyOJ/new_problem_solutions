#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 12:20
# update_at: 2026-10-01 12:20

import sys


def wrap(kids: list[str]) -> str:
    """把若干儿子的规范串封成一个结点：0 + 儿子规范串排序拼接 + 自己回父亲的 1。"""
    return '0' + ''.join(sorted(kids)) + '1'


def canon(s: str) -> str:
    """把一条探索路线折叠成树的同构不动点：每个点 = 0 + 儿子规范串排序拼接 + 一个 1。

    同构的树无论从哪条路线遍历，折叠结果都相同；用显式栈自底向上合并，
    避免链形地铁把递归深度推到 1500。
    """
    stack: list[list[str]] = [[]]  # 栈里是每个"还没封口"的结点的儿子规范串，栈底是根
    for c in s:
        if c == '0':               # 走向更远的一站：开一个新结点
            stack.append([])
        else:                      # 退回：该结点的儿子已全部折叠完，封口
            # 不能写 stack[-1].append(wrap(stack.pop()))：绑定 append 时栈顶还没弹出，
            # 结果会追加进刚弹出的那层被丢掉
            kids = stack.pop()
            stack[-1].append(wrap(kids))
    return ''.join(sorted(stack.pop()))  # 循环结束回到中央车站：根没有前导 0 和尾 1


def solve() -> None:
    it = iter(sys.stdin.buffer.read().split())
    t = int(next(it))
    out = ['same' if canon(next(it).decode()) == canon(next(it).decode()) else 'different'
           for _ in range(t)]
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
