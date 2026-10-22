"""P3623《[APIO2008] 免费道路》的多解判定（special judge）。

题面原文：
  > 如果满足国王要求的道路维护方案不存在，你的程序应该在输出第一行打印 `no solution`。
  > 否则，你的程序应该输出一个符合要求的道路维护方案，也就是保持免费的道路列表。
  > 按照输入中给定的那样输出免费的道路。如果有多种合法方案，你可以任意输出一种。

⚠ 为什么不能逐字节比对：
  本题有多组最优方案，`.out` 只是其中一种。逐字节比对会把合法方案判成 WA。

判定原则（见 `spj_registry.py` 的设计约束）：
  **独立验证 got 的合法性**，而不是拿 got 与 want 比较。
  ① got 是 `no solution` 时，独立枚举是否存在合法方案；
  ② got 是方案时，逐条检查：每行是 `u v t`、能在输入边集中找到且不重复使用、
     恰好 n-1 条、无环、连通、免费道路（t=0）恰好 k 条；
  ③ 其他情况一律不合法。
"""

from __future__ import annotations

import itertools


def _parse_input(inp: str):
    toks = inp.split()
    if len(toks) < 3:
        return None
    try:
        n, m, k = int(toks[0]), int(toks[1]), int(toks[2])
    except ValueError:
        return None
    if n <= 0 or m < 0 or len(toks) < 3 + 3 * m:
        return None
    edges = []
    p = 3
    for _ in range(m):
        try:
            u, v, t = int(toks[p]), int(toks[p + 1]), int(toks[p + 2])
        except ValueError:
            return None
        edges.append((u, v, t))
        p += 3
    return n, m, k, edges


def _is_valid_scheme(n: int, k: int, edges, chosen: list[int]) -> tuple[bool, str]:
    """chosen 是边下标列表；检查它是否构成满足要求的生成树。"""
    if len(chosen) != n - 1:
        return False, f"需要 {n - 1} 条边，实际 {len(chosen)} 条"
    if len(set(chosen)) != len(chosen):
        return False, "同一条边被重复使用"

    parent = list(range(n + 1))

    def find(x: int) -> int:
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    free = 0
    for idx in chosen:
        u, v, t = edges[idx]
        ru, rv = find(u), find(v)
        if ru == rv:
            return False, "选出的边构成环"
        parent[ru] = rv
        if t == 0:
            free += 1

    if len({find(i) for i in range(1, n + 1)}) != 1:
        return False, "选出的边没有连通所有城市"
    if free != k:
        return False, f"免费道路需要恰好 {k} 条，实际 {free} 条"
    return True, "合法方案"


def _exists_solution(n: int, k: int, edges) -> bool:
    """独立判定是否存在合法方案：n 很小时枚举边集，否则用并查集贪心判定。

    评测数据的 n 可能较大，这里只用两遍 Kruskal 的快速判定：
      - 下界：先加全部水泥路，再补免费路，得到最少需要的免费路条数 need；
      - 上界：先加全部免费路，得到免费路能提供的最大条数 cap（在生成树里最多用 cap 条）。
      存在方案 <=> 图连通 且 need <= k <= cap。
    """
    # 连通性
    parent = list(range(n + 1))

    def find(x: int) -> int:
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    def union(a: int, b: int) -> bool:
        ra, rb = find(a), find(b)
        if ra == rb:
            return False
        parent[ra] = rb
        return True

    for u, v, _ in edges:
        union(u, v)
    if len({find(i) for i in range(1, n + 1)}) != 1:
        return False

    # 下界 need：先水泥后免费
    parent = list(range(n + 1))
    need = 0
    picked = 0
    for u, v, t in edges:
        if t != 1:
            continue
        if union(u, v):
            picked += 1
    for u, v, t in edges:
        if t != 0:
            continue
        ru, rv = find(u), find(v)
        if ru == rv:
            continue
        parent[ru] = rv
        need += 1
        picked += 1
    if picked != n - 1:
        return False

    # 上界 cap：先免费后水泥，统计免费边在生成树里最多能放几条
    parent = list(range(n + 1))
    cap = 0
    for u, v, t in edges:
        if t != 0:
            continue
        if union(u, v):
            cap += 1

    return need <= k <= cap


def check(inp: str, got: str, want: str) -> tuple[bool, str]:
    parsed = _parse_input(inp)
    if parsed is None:
        return False, "判定器无法解析输入"
    n, m, k, edges = parsed

    lines = [ln.strip() for ln in got.strip().splitlines() if ln.strip()]
    if not lines:
        return False, "输出为空"

    # 无解分支
    if lines[0].lower().startswith("no"):
        if _exists_solution(n, k, edges):
            return False, "题面：无解才输出 no solution，但该数据存在合法方案"
        return True, "该数据确实无解，输出正确"

    # 方案分支：每行必须是 u v t，且在输入边集中存在、不重复使用
    pool: dict[tuple[int, int, int], list[int]] = {}
    for i, (u, v, t) in enumerate(edges):
        pool.setdefault((u, v, t), []).append(i)

    chosen: list[int] = []
    used: dict[tuple[int, int, int], int] = {}
    for ln in lines:
        parts = ln.split()
        if len(parts) != 3:
            return False, f"每行应为 `u v t` 三个整数，实际是：{ln}"
        try:
            key = (int(parts[0]), int(parts[1]), int(parts[2]))
        except ValueError:
            return False, f"行内含非整数：{ln}"
        cnt = used.get(key, 0)
        if cnt >= len(pool.get(key, [])):
            return False, f"边 {key} 在输入中不存在，或已被重复使用"
        used[key] = cnt + 1
        chosen.append(pool[key][cnt])

    ok, msg = _is_valid_scheme(n, k, edges, chosen)
    if not ok:
        return False, msg
    return True, f"合法方案：{n - 1} 条边连通，其中免费道路 {k} 条"


if __name__ == "__main__":  # 自测
    demo = (
        "5 7 2\n"
        "1 3 0\n4 5 1\n3 2 0\n5 3 1\n4 3 0\n1 2 1\n4 2 1\n"
    )
    standard = "3 2 0\n4 3 0\n5 3 1\n1 2 1\n"   # 题面 .out
    for cand in [
        standard,                            # 与 .out 相同
        "1 3 0\n4 5 1\n3 2 0\n5 3 1\n",   # 另一种合法方案
        "1 3 0\n",                          # 边数不够
        "1 3 0\n4 5 1\n3 2 0\n3 2 0\n",   # 重复用同一条边
        "no solution\n",                    # 实际有解
    ]:
        print(repr(cand.strip()), "→", check(demo, cand, standard))
