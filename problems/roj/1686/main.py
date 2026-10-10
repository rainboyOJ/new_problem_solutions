#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 17:48
# update_at: 2026-10-07 17:48

import sys
from collections import defaultdict, deque

INF = 1 << 30  # 不可达；滑行次数上界远小于它

# 四个方向的行列增量，顺序固定为 上/下/左/右
DR = (-1, 1, 0, 0)
DC = (0, 0, -1, 1)

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Neigh = list[tuple[int, ...]]   # 每个格子的 4 个滑行落点（-1 表示会滑出边界）
type Dists = dict[int, int]          # 格子编号 -> 到达该格的最少滑行次数
type CellMap = dict[int, list[int]]  # 字符码 -> 该字符所在的全部格子编号


def slide(grid: list[bytes], n: int, m: int, u: int, d: int) -> int:
    """题目的基本操作：从格子 u 沿方向 d 滑到第一个字符不同的格子，返回落点编号。

    一路撞到边界（沿途字符始终与起点相同）则这一步不合法，返回 -1。
    """
    ch = grid[u // m][u % m]
    r, c = u // m + DR[d], u % m + DC[d]
    while 0 <= r < n and 0 <= c < m and grid[r][c] == ch:
        r, c = r + DR[d], c + DC[d]
    return r * m + c if 0 <= r < n and 0 <= c < m else -1


def slide_table(grid: list[bytes], n: int, m: int) -> Neigh:
    """预处理滑行图：每个格子 4 个方向各一次滑行的落点。"""
    return [tuple(slide(grid, n, m, u, d) for d in range(4)) for u in range(n * m)]


def start_dists(nxt: Neigh) -> Dists:
    """从左上角出发、只做滑行时，到各格所需的最少滑行次数（滑行图上的 BFS）。"""
    dist = {0: 0}
    queue = deque([0])
    while queue:
        u = queue.popleft()
        for v in nxt[u]:
            if v >= 0 and v not in dist:
                dist[v] = dist[u] + 1
                queue.append(v)
    return dist


def next_layer(cur: Dists, targets: list[int], nxt: Neigh, nm: int) -> Dists:
    """把"已选完若干字符、停在 cur 里的某个格子"推进到"再选一个指定字符"。

    cur 的键都是上一次定型时匹配的格子，值是那时的最少滑行次数；本层先从 cur
    的格子自由滑行（边权 1、源点初值不同），再只保留落在 targets 里的格子。
    初值不同但边权全为 1，用 Dial 桶队列（距离值分桶）代替堆；
    targets 全部定型就停，字符稀疏时能省掉大量扩展。
    """
    if not cur or not targets:
        return {}
    want = set(targets)
    base = min(cur.values())                   # 桶下标 = 距离 - base
    buckets: dict[int, list[int]] = defaultdict(list)
    dist: Dists = {}
    for u, w in cur.items():
        dist[u] = w
        buckets[w - base].append(u)
    bound = max(cur.values()) - base + nm + 2  # 多绕一圈也不超过滑行图直径
    found: Dists = {}
    for b in range(bound):
        for u in buckets[b]:
            if dist[u] != b + base:
                continue                       # 桶里的过期副本，已按更小的值处理过
            if u in want:
                found[u] = dist[u]
            for v in nxt[u]:
                nxt_dist = dist[u] + 1
                if v >= 0 and dist.get(v, INF) > nxt_dist:
                    dist[v] = nxt_dist
                    buckets[nxt_dist - base].append(v)
        if len(found) == len(want):
            break
    return found


def min_slides(nxt: Neigh, cells_of: CellMap, target: bytes) -> int:
    """目标串 target 全部选完所需的最少滑行次数（选择次数另算，恒为 len(target)）。"""
    # 第 1 个字符必须在字符等于 target[0] 的格子上选出
    cur = {u: w for u, w in start_dists(nxt).items() if u in cells_of.get(target[0], ())}
    for ch in target[1:]:                      # 之后每个字符：先滑到匹配格，再选择
        cur = next_layer(cur, cells_of.get(ch, []), nxt, len(nxt))
        if not cur:                            # 这一层就断了，后面永远接不上
            break
    return min(cur.values(), default=INF)


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n, m = int(next(data)), int(next(data))
    grid = [next(data) for _ in range(n)]      # 每行是 bytes，grid[r][c] 取到字符码
    target = next(data) + b'*'                 # 目标串 = s 后面再添一个 '*'

    cells_of: CellMap = defaultdict(list)
    for u in range(n * m):
        cells_of[grid[u // m][u % m]].append(u)

    slides = min_slides(slide_table(grid, n, m), cells_of, target)
    # 每次操作只能选一个字符，目标串共 len(target) 个字符 => 选择次数固定
    print(len(target) + slides if slides < INF else -1)


if __name__ == "__main__":
    solve()
