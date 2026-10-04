#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 16:34
# update_at: 2026-09-30 16:34

import sys


def solve() -> None:
    K = int(sys.stdin.readline())
    mask = (1 << (K - 1)) - 1              # 节点只保留低 K-1 位（de Bruijn 图的后缀）
    edge_used = [False] * (1 << K)         # 边 (u << 1) | b 正好对应一个长度 K 的 01 串

    # 迭代式 Hierholzer 欧拉回路：栈元素为 (节点, 进入该节点的边标号)，起点记 -1。
    emit: list[int] = []                   # 后序记录的边标号，逆序才是回路走向
    stack: list[tuple[int, int]] = [(0, -1)]
    while stack:
        u, entry = stack[-1]
        for b in (0, 1):                   # 每个节点至多两条出边，先试 0 再试 1
            e = (u << 1) | b
            if not edge_used[e]:
                edge_used[e] = True
                stack.append((e & mask, b))  # 沿边走到新的 K-1 位后缀
                break
        else:                              # 出边耗尽才回溯，此时记录进入边
            stack.pop()
            if entry >= 0:
                emit.append(entry)

    circuit = ''.join(map(str, reversed(emit)))   # 边标号序列 = 环上的 01 串
    head = (circuit + circuit).find('0' * K)      # 全 0 子串环上唯一，旋到开头即字典序最小
    ring = circuit[head:] + circuit[:head]
    print(f"{1 << K} {ring}")


if __name__ == "__main__":
    solve()
