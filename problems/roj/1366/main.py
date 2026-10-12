#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:15
# update_at: 2026-10-12 15:25

# 新方法：先序 + 中序还原二叉树，再按凹入表示法输出（结点长度 = 子树叶子数）
#（原方法「区间递归直接输出」见 direct.py）。
# 树的存储：一个结点的字符、左右孩子、长度收进 Node，编号即下标；
# 长度在建树时顺手算好：叶子为 1，非叶为左右之和（空子树为 0）。
# 如何使用：
# 1. read_input()            # 读入先序、中序，建好中序下标表 pos
# 2. root = build(0, 0, n)   # 先序首字符定根，中序位置切分，递归建树
# 3. walk(root)              # 先序输出「字符 × 长度」，solve() 负责装配输出

import sys


class Node:
    """编号 u 的结点：字符 + 左右孩子 + 长度（子树叶子数）。"""

    def __init__(self) -> None:
        self.val = ""  # 结点字符
        self.lch = 0   # 左儿子编号，0 表示空
        self.rch = 0   # 右儿子编号，0 表示空
        self.len = 0   # 结点长度 = 子树叶子数：叶为 1，非叶为左右之和，空子树为 0


node: list[Node] = []   # node[u]：编号 u 的结点，下标 0 是占位
node_cnt = 0            # 已分配的结点个数
pre = ""                # 先序遍历序列
ino = ""                # 中序遍历序列，只用来建 pos 表
pos: dict[str, int] = {}  # pos[c] = 字符 c 在中序中的下标（字符互不重复，可 O(1) 定位）
out: list[str] = []     # 凹入输出的每一行


def new_node(ch: str) -> int:
    """动态化静态开点：分配一个新结点并返回它的编号。"""
    global node_cnt
    node_cnt += 1
    node.append(Node())
    node[node_cnt].val = ch
    return node_cnt


def read_input() -> None:
    """读入先序、中序序列，建好中序下标表。"""
    global pre, ino, pos, node
    data = iter(sys.stdin.read().split())
    pre = next(data)
    ino = next(data)
    pos = {ch: i for i, ch in enumerate(ino)}
    node = [Node()]  # 下标 0 占位，结点编号从 1 开始


def build(pl: int, il: int, cnt: int) -> int:
    """用先序 pre[pl:pl+cnt] 与中序 ino[il:il+cnt] 建树，返回根编号；空子树返回 0。"""
    if cnt == 0:
        return 0
    u = new_node(pre[pl])             # 先序首字符就是根
    left_cnt = pos[pre[pl]] - il      # 根在中序中的位置给出左子树大小
    node[u].lch = build(pl + 1, il, left_cnt)
    node[u].rch = build(pl + 1 + left_cnt, il + left_cnt + 1, cnt - 1 - left_cnt)
    # 长度 = 子树叶子数：叶为 1，非叶为左右之和
    node[u].len = 1 if node[u].lch == 0 and node[u].rch == 0 else (
        node[node[u].lch].len + node[node[u].rch].len
    )
    return u


def walk(u: int) -> None:
    """按先序输出凹入表示：先根那一行（字符重复 len 次），再递归左右子树。"""
    if u == 0:
        return
    out.append(node[u].val * node[u].len)
    walk(node[u].lch)
    walk(node[u].rch)


def solve() -> None:
    read_input()
    walk(build(0, 0, len(pre)))
    print("\n".join(out))


if __name__ == "__main__":
    solve()
