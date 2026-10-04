#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 13:59
# update_at: 2026-09-30 14:07

import sys
from collections import deque


def build_pattern(strings: list[bytes]) -> tuple[list[list[int]], list[bool]]:
    """把所有病毒串插进 Trie，返回完整转移表 TO 与危险标记表 END。

    危险 = 该节点代表的串含有病毒串作子串 = 自身是病毒串结尾，或 fail 链上
    存在病毒串结尾；建 fail 时沿队列顺序传播一次即得。
    """
    TO = [[-1, -1]]  # 每个节点两条出边：0 位、1 位，-1 表示 Trie 中尚无此边
    END = [False]    # 节点对应串是否危险
    for s in strings:
        v = 0
        for byte in s:
            bit = byte & 1                     # '0'=48→0，'1'=49→1
            if TO[v][bit] == -1:
                TO[v][bit] = len(TO)
                TO.append([-1, -1])
                END.append(False)
            v = TO[v][bit]
        END[v] = True

    # BFS 建 fail：缺失边抄 fail 的同位边（补成完整转移表），已存在的边更新
    # fail 并把危险标记沿 fail 链传播给孩子。
    fail = [0] * len(TO)
    q = deque(w for w in TO[0] if w != -1)      # 根的孩子先入队
    TO[0] = [w if w != -1 else 0 for w in TO[0]]  # 根的缺失边指回自己
    while q:
        v = q.popleft()
        for bit in (0, 1):
            w = TO[v][bit]
            if w == -1:
                TO[v][bit] = TO[fail[v]][bit]   # 缺失边：抄 fail[v] 的同位边
            else:
                fail[w] = TO[fail[v]][bit]
                END[w] |= END[fail[w]]         # 危险沿 fail 链传播
                q.append(w)
    return TO, END


def has_cycle(TO: list[list[int]], END: list[bool]) -> bool:
    """从根只走安全边的可达子图中是否存在环：Kahn 删不光所有点即有环。"""
    safe = [not end for end in END]
    if not safe[0]:
        return False  # 病毒串非空时根恒安全，这里只防御空串输入

    # 可达安全子图：只沿两端都安全的边 BFS，同时统计入度
    seen = [False] * len(TO)
    indeg = [0] * len(TO)
    seen[0] = True
    q = deque([0])
    total = 1                             # 子图中的安全节点数
    while q:
        v = q.popleft()
        for bit in (0, 1):
            w = TO[v][bit]
            if safe[w]:
                indeg[w] += 1
                if not seen[w]:
                    seen[w] = True
                    total += 1
                    q.append(w)

    # Kahn：入度归零的点入队并回删出边；环上节点入度永不归零
    q = deque(i for i in range(len(TO)) if seen[i] and indeg[i] == 0)
    removed = 0
    while q:
        v = q.popleft()
        removed += 1
        for bit in (0, 1):
            w = TO[v][bit]
            if safe[w]:
                indeg[w] -= 1
                if indeg[w] == 0:
                    q.append(w)
    return removed != total


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))
    strings = [next(data) for _ in range(n)]
    TO, END = build_pattern(strings)
    print("TAK" if has_cycle(TO, END) else "NIE")


if __name__ == "__main__":
    solve()
