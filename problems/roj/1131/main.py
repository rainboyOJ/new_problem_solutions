#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:15
# update_at: 2026-09-29 20:15

import sys


def solve() -> None:
    # 第一行是阈值，随后两行是等长的 DNA 序列
    lines = sys.stdin.read().split()
    threshold = float(lines[0])
    seq1, seq2 = lines[1], lines[2]

    length = len(seq1)
    same = sum(a == b for a, b in zip(seq1, seq2))  # 相同碱基对的个数

    print("yes" if same / length >= threshold else "no")


if __name__ == "__main__":
    solve()
