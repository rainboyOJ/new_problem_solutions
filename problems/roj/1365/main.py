#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:15
# update_at: 2026-09-30 07:15

import sys
from functools import cache


def node_kind(bits: str) -> str:
    """判断一段 01 串对应的 FBI 结点类型：全 0 为 B，全 1 为 I，否则为 F。"""
    return "B" if "1" not in bits else "I" if "0" not in bits else "F"


@cache
def postorder(bits: str) -> str:
    """返回 bits 所构造 FBI 树的后序遍历序列。"""
    mid = len(bits) // 2
    # 长度大于 1 时先递归左右子树，再输出根；长度为 1 时直接返回自身类型。
    return postorder(bits[:mid]) + postorder(bits[mid:]) + node_kind(bits) if mid else node_kind(bits)


def solve() -> None:
    data = sys.stdin.buffer.read().decode().split()
    n = int(data[0])
    s = data[1] if n else ""  # N=0 时串为空，但题目保证 0≤N≤10，此时只输出空行。
    print(postorder(s))


if __name__ == "__main__":
    solve()
