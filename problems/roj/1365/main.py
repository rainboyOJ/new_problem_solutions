#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:15
# update_at: 2026-10-12 15:25

# 新方法：按题面规则构造 FBI 树，再后序遍历输出结点类型
#（原方法「子串递归直接拼后序」见 direct.py）。
# 树的存储：一个结点的类型、左儿子、右儿子收进 Node，编号即下标。
# 如何使用：
# 1. read_input()            # 读入 n 和 01 串
# 2. root = build(0, 2**n)   # 一段 01 串就建一棵 FBI 子树，返回根编号
# 3. postorder(root)         # 左 -> 右 -> 根 收集类型，solve() 负责装配输出

import sys


class Node:
    """编号 u 的结点：类型 + 左右孩子（0 表示叶子/空）。"""

    def __init__(self) -> None:
        self.type = ""  # 结点类型：全 0 为 B，全 1 为 I，既有 0 又有 1 为 F
        self.lch = 0    # 左儿子编号，0 表示叶子
        self.rch = 0    # 右儿子编号，0 表示叶子


node: list[Node] = []  # node[u]：编号 u 的结点，下标 0 是占位
node_cnt = 0           # 已分配的结点个数
s = ""                 # 输入的 01 串，子串 s[l:r] 就是一棵待建的子树
out: list[str] = []    # 后序序列，按访问顺序收集类型


def new_node(kind: str) -> int:
    """动态化静态开点：分配一个新结点并返回它的编号。"""
    global node_cnt
    node_cnt += 1
    node.append(Node())
    node[node_cnt].type = kind
    return node_cnt


def read_input() -> None:
    """读入 n 和 01 串（串长固定为 2^n）。"""
    global s, node
    data = iter(sys.stdin.read().split())
    n = int(next(data))
    s = next(data)
    assert len(s) == 1 << n  # 题面保证串长恰好 2^n
    node = [Node()]  # 下标 0 占位，结点编号从 1 开始


def node_kind(l: int, r: int) -> str:
    """判断子串 s[l:r] 的类型：全 0 为 B，全 1 为 I，否则为 F。"""
    has0 = has1 = False
    for ch in s[l:r]:
        if ch == "0":
            has0 = True
        else:
            has1 = True
        if has0 and has1:
            return "F"  # 0 和 1 都出现了，不用再看后面
    return "B" if has0 else "I"


def build(l: int, r: int) -> int:
    """递归构造子串 s[l:r] 对应的 FBI 子树，返回根编号。"""
    u = new_node(node_kind(l, r))  # 根的类型由整段串决定
    if r - l > 1:                  # 串长为 1 时是叶子，不再往下分
        mid = (l + r) // 2         # 从中间切成等长的左右两半
        node[u].lch = build(l, mid)
        node[u].rch = build(mid, r)
    return u


def postorder(u: int) -> None:
    """后序遍历：左子树 -> 右子树 -> 根，把类型依次写进 out。"""
    if u == 0:
        return
    postorder(node[u].lch)
    postorder(node[u].rch)
    out.append(node[u].type)


def solve() -> None:
    read_input()
    postorder(build(0, len(s)))
    print("".join(out))


if __name__ == "__main__":
    solve()
