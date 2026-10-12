#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:15
# update_at: 2026-10-12 15:05
# direct.py：原方法——区间/子串递归直接产出，不显式建结点树（对比新方法见 main.py）。

# FBI 树：子串区间递归，直接算出后序序列，不显式建结点。
# 一段 01 串 bits 就对应一棵 FBI 子树：全 0 为 B，全 1 为 I，既有 0 又有 1 为 F，
# 串长大于 1 时从中间切成等长两半，后序 = 左半 + 右半 + 根。
# 如何使用：
# 1. read_input()   # 读入 N 和 01 串 s
# 2. postorder(s)   # 返回串 s 构造出的 FBI 树的后序遍历序列
# 3. solve()        # 装配：读入 -> 递归 -> 输出

import sys
from functools import cache

s = "" # 输入的 01 串，串长 2^N


def read_input() -> None:
    """读入 N 和 01 串。"""
    global s
    data = sys.stdin.buffer.read().decode().split()
    s = data[1] if int(data[0]) else ""  # N == 0 时按空串处理


def node_kind(bits: str) -> str:
    """判断一段 01 串对应的 FBI 结点类型：全 0 为 B，全 1 为 I，否则为 F。"""
    return "B" if "1" not in bits else "I" if "0" not in bits else "F"


@cache
def postorder(bits: str) -> str:
    """返回 bits 所构造 FBI 树的后序遍历序列。"""
    mid = len(bits) // 2
    # 长度大于 1 时先递归左右子树，再拼上根；长度为 1 时直接返回自身类型。
    return postorder(bits[:mid]) + postorder(bits[mid:]) + node_kind(bits) if mid else node_kind(bits)


def solve() -> None:
    read_input()
    print(postorder(s))


if __name__ == "__main__":
    solve()
