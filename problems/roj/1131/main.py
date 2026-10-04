#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:15
# update_at: 2026-10-04 09:35

import sys


def solve() -> None:
    # 阈值在输入最前，随后依次是两条等长 DNA 序列
    data = iter(sys.stdin.buffer.read().split())
    threshold = float(next(data))
    seq1, seq2 = next(data), next(data)

    length = len(seq1)
    same = sum(a == b for a, b in zip(seq1, seq2))  # 相同碱基对的个数

    print("yes" if same / length >= threshold else "no")


if __name__ == "__main__":
    solve()
