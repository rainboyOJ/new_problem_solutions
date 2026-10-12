#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:16
# update_at: 2026-10-12 15:25

# 新方法：先建出二叉树，再先序遍历输出（原方法「区间递归直接产出」见 direct.py）。
# 树的存储：一个结点的字符、左儿子、右儿子收进 Node，编号即下标。
# 如何使用：
# 1. read_input()            # 读入中序、层序，建好层序名次表 rank
# 2. root = build(0, n)      # 用中序区间 [lo, hi) 建树，返回根编号
# 3. preorder(root)          # 先序遍历把字符写进 out，solve() 负责装配输出

import sys


class Node:
    """编号 u 的结点：字符 + 左右孩子（0 表示空）。"""

    def __init__(self) -> None:
        self.val = ""  # 结点字符
        self.lch = 0   # 左儿子编号，0 表示空
        self.rch = 0   # 右儿子编号，0 表示空


node: list[Node] = []  # node[u]：编号 u 的结点，下标 0 是占位
node_cnt = 0           # 已分配的结点个数
inorder = ""           # 中序遍历序列
level = ""             # 层序遍历序列
rank: dict[str, int] = {}  # rank[c] = 字符 c 在层序中的名次（越小越靠近根）
out: list[str] = []    # 先序序列，按访问顺序收集字符


def new_node(ch: str) -> int:
    """动态化静态开点：分配一个新结点并返回它的编号。"""
    global node_cnt
    node_cnt += 1
    node.append(Node())
    node[node_cnt].val = ch
    return node_cnt


def read_input() -> None:
    """读入中序、层序序列，建好层序名次表。"""
    global inorder, level, rank, node
    data = iter(sys.stdin.buffer.read().split())
    inorder = next(data).decode()
    level = next(data).decode()
    rank = {ch: i for i, ch in enumerate(level)}
    node = [Node()]  # 下标 0 占位，结点编号从 1 开始


def build(lo: int, hi: int) -> int:
    """用中序区间 [lo, hi) 建树，返回根编号；空区间返回 0。"""
    if lo == hi:
        return 0
    # 根 = 层序名次最靠前的区间内字符：层序保证祖先一定排在子孙前面
    root = min(inorder[lo:hi], key=rank.__getitem__)
    u = new_node(root)
    mid = inorder.index(root, lo, hi)  # 根把中序切成左右子树两段
    node[u].lch = build(lo, mid)       # 根左边一段是左子树
    node[u].rch = build(mid + 1, hi)   # 根右边一段是右子树
    return u


def preorder(u: int) -> None:
    """先序遍历：根 -> 左子树 -> 右子树，把结点字符依次写进 out。"""
    if u == 0:
        return
    out.append(node[u].val)
    preorder(node[u].lch)
    preorder(node[u].rch)


def solve() -> None:
    read_input()
    preorder(build(0, len(inorder)))
    print("".join(out))


if __name__ == "__main__":
    solve()
