#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys

# 候选表：letter[i] = 数字编号 i 可以放在哪些字母幻灯片里（位掩码，第 j 位 = 幻灯片 j）
# n ≤ 26，一个 int 装下所有候选，方便做拓扑消元时的位运算。


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    # 每张幻灯片（按输入顺序编号 A,B,...）的边界，每行 xmin xmax ymin ymax
    rect = [(next(data), next(data), next(data), next(data)) for _ in range(n)]

    # 数字编号 i 的候选字母集合：数字点落在哪些幻灯片矩形内部
    candidates: list[int] = []
    for _ in range(n):
        x = next(data)
        y = next(data)
        inside = [j for j in range(n)
                  if rect[j][0] <= x <= rect[j][1] and rect[j][2] <= y <= rect[j][3]]
        candidates.append(sum(1 << j for j in inside))  # 空集合 = 无解

    # 拓扑排序式消元：候选只有 1 个字母的数字先确定，把该字母从别人的候选里删掉
    match: list[int] = [-1] * n  # match[i] = 数字 i 对应的字母下标
    queue = [i for i in range(n) if candidates[i].bit_count() == 1]
    while queue:
        nxt: list[int] = []
        for i in queue:
            letter = candidates[i].bit_length() - 1   # 唯一剩下的字母
            if match[letter] != -1:                   # 同一字母被两个数字抢 → 无解
                print("None")
                return
            match[letter] = i
            bit = 1 << letter
            for k in range(n):                        # 从其他数字的候选中删掉该字母
                if k != i and candidates[k] & bit:
                    candidates[k] &= ~bit
                    if candidates[k].bit_count() == 1:
                        nxt.append(k)
        queue = nxt

    if any(m == -1 for m in match):                   # 有字母没被匹配 → 多解或无解
        print("None")
        return

    # match[letter] = 数字，按字母升序输出
    print("\n".join(f"{chr(ord('A') + j)} {match[j] + 1}" for j in range(n)))


if __name__ == "__main__":
    solve()
