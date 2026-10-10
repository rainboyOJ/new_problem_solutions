#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 17:30
# update_at: 2026-10-07 17:30

import sys
from operator import add

MOD = 998244353
# 模式掩码：第 j 位（1 << j）表示第 j 个模式已经在 S 里出现过；
# p 与 q = ~reverse(p) 共用同一位，因为两者任一出现都意味着该模式被 S 包含。

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Go = list[list[int]]    # go[u] = 节点 u 读入 0 / 1 之后到达的节点
type Mask = list[int]        # 每个节点一个 2^n 掩码
type Rows = list[list[int]]  # DP 表：节点 -> 该节点上各掩码的方案数


def comp_rev(s: str) -> str:
    """返回 ~reverse(s)：p 出现在右半段 <=> q = ~reverse(p) 出现在 T 里。"""
    return ''.join('1' if c == '0' else '0' for c in reversed(s))


def insert(s: str, bit: int, go: Go, end: Mask) -> list[int]:
    """把 s 插进 trie，返回每个前缀的节点编号（第 k 项是长度 k 的前缀）。"""
    path = [0]
    u = 0
    for c in s:
        v = go[u][ord(c) - 48]
        if v < 0:
            go.append([-1, -1])  # 新节点：end 与节点一一对应，一起长
            end.append(0)
            v = len(go) - 1
            go[u][ord(c) - 48] = v
        u = v
        path.append(u)
    end[u] |= bit
    return path


def build_automaton(pats: list[str]) -> tuple[Go, Mask, Mask]:
    """插入 p 与 q 并建好 AC 自动机，返回 (转移表, 命中掩码, 中点掩码)。"""
    go: Go = [[-1, -1]]
    end = [0]
    pnode = [insert(p, 1 << j, go, end) for j, p in enumerate(pats)]
    qnode = [insert(comp_rev(p), 1 << j, go, end) for j, p in enumerate(pats)]
    mid = [0] * len(go)  # 中点标记与节点一一对应，插入阶段先空着

    # 横跨中点：左侧匹配 k 位（1 <= k <= L-1）时，左侧是 T 的后缀 k 位、
    # 必须等于 p 的前 k 位；右侧由 T 的后缀 L-k 位决定、必须等于 q 的前 L-k 位。
    # 两者同时成立 <=> 较短者是较长者的后缀，且 T 以较长者结尾，
    # 所以只需在"较长前缀"的节点上打标记，末尾看 T 是否停在这种节点上。
    for j, p in enumerate(pats):
        L = len(p)
        q = comp_rev(p)
        for k in range(1, L):
            if k > L - k:                       # 较长者是 p 的前 k 位
                if p[k - (L - k):k] == q[:L - k]:
                    mid[pnode[j][k]] |= 1 << j
            elif q[L - 2 * k:L - k] == p[:k]:   # 较长者是 q 的前 L-k 位
                mid[qnode[j][L - k]] |= 1 << j

    # 根节点缺的儿子指向自己；其余节点在 BFS 里补全成自动机转移，
    # 顺带沿 fail 链累积"命中"与"中点"两类掩码。
    for c in (0, 1):
        go[0][c] = max(go[0][c], 0)
    fail = [0] * len(go)
    hit = end[:]
    mid_all = mid[:]
    queue = [v for v in go[0] if v > 0]
    head = 0
    while head < len(queue):
        u = queue[head]
        head += 1
        hit[u] |= hit[fail[u]]
        mid_all[u] |= mid_all[fail[u]]
        for c in (0, 1):
            v = go[u][c]
            if v < 0:
                go[u][c] = go[fail[u]][c]
            else:
                fail[v] = go[fail[u]][c]
                queue.append(v)
    return go, hit, mid_all


def count_strings(m: int, go: Go, hit: Mask, mid_all: Mask, full: int) -> int:
    """逐位构造 T：dp[节点][已命中掩码]，末尾并入中点标记后统计覆盖全部模式的方案数。"""
    states = full + 1
    dp: Rows = [[0] * states for _ in range(len(go))]
    dp[0][0] = 1
    for _ in range(m):
        ndp: Rows = [[0] * states for _ in range(len(go))]
        for u, row in enumerate(dp):
            if not any(row):  # 这个节点上没有方案，两条出边都不用走
                continue
            for c in (0, 1):
                v = go[u][c]
                added = hit[v]
                tgt = ndp[v]
                if added:  # 命中集合变大：把并到同一个新掩码的来源逐个相加
                    for mask in range(states):
                        x = row[mask]
                        if x:
                            nm = mask | added
                            s = tgt[nm] + x
                            tgt[nm] = s - MOD if s >= MOD else s
                else:      # 命中集合不变：整行同位置相加，交给 map 走 C 循环
                    merged = [s - MOD if s >= MOD else s for s in map(add, tgt, row)]
                    ndp[v] = merged
        dp = ndp
    # 自动机转移是完整的，dp 永远有非零项，不需要提前退出
    return sum(cnt for u, row in enumerate(dp) for mask, cnt in enumerate(row)
               if mask | mid_all[u] == full) % MOD


def solve() -> None:
    tokens = iter(sys.stdin.buffer.read().split())
    n, m = int(next(tokens)), int(next(tokens))
    pats = [next(tokens).decode() for _ in range(n)]
    go, hit, mid_all = build_automaton(pats)
    print(count_strings(m, go, hit, mid_all, (1 << n) - 1))


if __name__ == "__main__":
    solve()
