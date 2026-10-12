#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:16
# update_at: 2026-10-12 15:05
# direct.py：原方法——区间/子串递归直接产出，不显式建结点树（对比新方法见 main.py）。

# 中序 + 层序还原二叉树并输出先序：区间递归，不显式建结点。
# 一段中序区间 [lo, hi) 就对应一棵子树，根 = 区间里层序名次最小的字符，
# 因为层序遍历中祖先一定排在子孙前面。
# 如何使用：
# 1. read_input()      # 读入中序、层序，建好 rank 排名表
# 2. preorder(0, n)    # 递归把中序区间 [lo, hi) 对应子树的先序写进 out
# 3. solve()           # 装配：读入 -> 递归 -> 输出

import sys

inorder = ""               # 中序遍历序列
level = ""                 # 层序遍历序列
rank: dict[str, int] = {}  # rank[c] = 字符 c 在层序中的名次（越小越靠近根）
out: list[str] = []        # 先序序列，按访问顺序收集字符


def read_input() -> None:
    """读入中序、层序序列，建好层序名次表。"""
    global inorder, level, rank
    data = iter(sys.stdin.buffer.read().split())
    inorder = next(data).decode()
    level = next(data).decode()
    rank = {ch: i for i, ch in enumerate(level)}


def preorder(lo: int, hi: int) -> None:
    """递归把中序区间 [lo, hi) 这棵子树的先序序列写进 out。"""
    if lo == hi:
        return
    # 根 = 层序名次最靠前的区间内字符：层序保证祖先一定排在子孙前面
    root = min(inorder[lo:hi], key=rank.__getitem__)
    out.append(root)
    mid = inorder.index(root, lo, hi)  # 根把中序切成左右子树两段
    preorder(lo, mid)                  # 左子树区间 [lo, mid)
    preorder(mid + 1, hi)              # 右子树区间 [mid+1, hi)


def solve() -> None:
    read_input()
    preorder(0, len(inorder))
    print(''.join(out))


if __name__ == "__main__":
    solve()
