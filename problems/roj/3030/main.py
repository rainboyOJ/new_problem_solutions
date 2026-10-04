#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 11:03
# update_at: 2026-10-01 11:03

import sys

LIMIT = 20  # 题面只要求前 20 种方案，凑够即可整体剪枝

n: int = 0              # 火车数量
ans: list[str] = []     # 收集到的出栈序列：每个状态先试「出栈」再试「进栈」，产出天然按字典序


def dfs(next_in: int, stack: list[int], out: list[int]) -> None:
    """从当前（下一节进站编号, 栈, 已出站序列）出发，枚举所有出栈序列。"""
    if len(ans) == LIMIT:
        return                          # 前 20 个已收集完毕，其余分支全部放弃
    if len(out) == n:
        ans.append(''.join(map(str, out)))
        return
    if stack:                           # 分支一：栈顶火车出站——能让出站序列更小，优先走
        out.append(stack.pop())
        dfs(next_in, stack, out)
        stack.append(out.pop())         # 回溯：复原栈与出站序列
    if next_in <= n:                    # 分支二：右侧下一节火车进站
        stack.append(next_in)
        dfs(next_in + 1, stack, out)
        stack.pop()


def solve() -> None:
    global n
    n = int(sys.stdin.read())
    dfs(1, [], [])
    print('\n'.join(ans))


if __name__ == "__main__":
    solve()
