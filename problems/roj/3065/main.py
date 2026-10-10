#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 09:00
# update_at: 2026-10-09 18:44

import sys

MAXM = 20  # n <= 100 时最短链长最多 10，留够任意搜索路径


def dfs(u: int, depth: int, n: int, path: list[int], tried: set[int]) -> bool:
    """在长度恰好 depth 的限制下填 path[u]；tried 是本帧已试过候选值的集合（等效冗余剪枝）。"""
    if u == depth:
        return path[u - 1] == n
    max_val = path[u - 1]
    if max_val << (depth - u) < n:  # 后面每步最多翻倍，翻满仍够不到 n 就剪掉
        return False
    for i in range(u - 1, -1, -1):  # 候选值从大到小枚举，优先逼近 n
        for j in range(i, -1, -1):  # i, j 允许相等
            nxt = path[i] + path[j]
            if nxt > n or nxt <= max_val or nxt in tried:
                continue
            tried.add(nxt)
            path[u] = nxt
            if dfs(u + 1, depth, n, path, set()):
                return True
    return False


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return
    path = [0] * MAXM
    out: list[str] = []
    for n in data:
        if n == 0:  # 单行 0 表示输入结束
            break
        depth = 1
        path[0] = 1
        while not dfs(1, depth, n, path, set()):  # 迭代加深：长度不够就加一
            depth += 1
        out.append(f"{depth}   {' '.join(map(str, path[:depth]))}")  # 长度 m + 3 个空格 + 序列
    sys.stdout.write('\n'.join(out) + '\n' if out else '')


if __name__ == '__main__':
    solve()
