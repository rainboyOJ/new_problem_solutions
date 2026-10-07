#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:55
# update_at: 2026-10-07 15:55

import sys

MOD = 9191  # 题目要求的取模值

# 类型别名：trie 上的一个节点 = (深度, 已并入的儿子答案累乘值, 自己是否为单词结尾)
type Frame = tuple[int, int, int]
type Stack = list[Frame]  # 手工栈：栈底是根，越靠近栈顶深度越大，父亲就是栈中下一个元素


def fold_top(stack: Stack) -> None:
    """弹出栈顶节点，把它的答案乘进父亲的累乘值。

    f[v] = 儿子答案之积 + (v 是单词结尾 ? 1 : 0)：
    乘积那部分对应「不选 v」，加上的 1 对应「只选 v，子树里一个都不选」。
    """
    depth, prod, is_end = stack.pop()
    pdepth, pprod, pis_end = stack[-1]
    stack[-1] = (pdepth, pprod * (prod + is_end) % MOD, pis_end)


def count_pfs(words: list[str]) -> int:
    """排序后用相邻最长公共前缀还原 trie 结构，逐节点统计合法子集数（含空集）。"""
    words.sort()
    stack: Stack = [(0, 1, 0)]  # 根：深度 0、累乘初值 1、不是任何单词的结尾
    prev = ""
    for word in words:
        lcp = 0  # 与上一个串的最长公共前缀长度 = 本串所在节点的父亲深度
        while lcp < len(word) and lcp < len(prev) and word[lcp] == prev[lcp]:
            lcp += 1
        while stack[-1][0] > lcp:  # 收掉所有比父亲更深的节点
            fold_top(stack)
        stack.append((len(word), 1, 1))  # 当前字符串自己是一个结尾节点
        prev = word
    while len(stack) > 1:  # 最后把整条路径收拢回根
        fold_top(stack)
    return stack[0][1] % MOD


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n = int(data[0])  # 题目保证 n >= 1
    words = [token.decode() for token in data[1:1 + n]]  # 需要整体排序，故一次性物化成列表
    print(count_pfs(words))


if __name__ == "__main__":
    solve()
