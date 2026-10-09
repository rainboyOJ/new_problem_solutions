"""1519《和平委员会》的多解判定（special judge）。

题面原文：
  > 如果委员会能以多种方法形成，程序**可以只输出它们的某一个**。

⚠ 为什么不能逐字节比对（2026-10-09 实测）：
  1. **多解**：spo8/9/10/11/13 上，程序与 `.out` 的**点数相同**，
     差异全是**同党伙伴对**（`2i-1` 与 `2i`）：
       `16000` vs `15999`、`137` vs `138`、`70` vs `69`、`422` vs `421`、`1007` vs `1008`
     ⇒ 两者**都是合法委员会**，只是为某些党派选了不同的代表。
  2. **数据行尾是 CRLF**：`spo*.out` 全部用 `\\r\\n`（实测 `spo0/4/8/10/11/13`
     的 `\\r\\n` 计数 == `\\n` 计数，纯 LF = 0），而实现输出 LF。
     ⇒ 逐字节比对必然失败（`check_bytes.py` 会一直报错，属**数据缺陷**，已记录）。

判定原则（见 `spj_registry.py` 的设计约束）：
  **独立验证 `got` 的合法性**，而不是拿 `got` 与 `want` 比较。
  对 `NIE` 的声明，用**独立的 2-SAT 求解**验证「确实无解」。

2-SAT 建模（1-indexed 代表 `r ∈ [1, 2n]`）：
  党派 `i` 的代表是 `2i-1`（奇）与 `2i`（偶）。
  变量 `x_i`：选 `2i-1` 为真、选 `2i` 为假。
  ⇒ 文字 `r` 的结点编号就是 **`r - 1`**，其否定是 **`(r-1) ^ 1`**（因为 `2i-1` 与 `2i` 相邻且奇偶配对）。
  厌恶对 `(a, b)` ⇒ 不能同时入选 ⇒ 蕴含 `a → ¬b`、`b → ¬a`
  ⇒ 加边 `(a-1) → ((b-1) ^ 1)`、`(b-1) → ((a-1) ^ 1)`。
  「每党恰 1 名」由变量编码**自动满足**（布尔变量天然取恰好一个文字）。
  可满足 ⟺ 不存在 `v` 使 `v` 与 `v^1` 在同一 SCC。
"""

from __future__ import annotations

import sys

# 深图可能很长（数据里 n 可达 8000、m 上万）⇒ 全程迭代，不用递归
sys.setrecursionlimit(10000)


def _parse_input(inp: str) -> tuple[int, int, list[tuple[int, int]]] | None:
    """返回 (n, m, pairs)；解析失败返回 None。"""
    toks = inp.split()
    if len(toks) < 2:
        return None
    try:
        n = int(toks[0])
        m = int(toks[1])
    except ValueError:
        return None
    if n < 0 or m < 0 or len(toks) < 2 + 2 * m:
        return None
    pairs: list[tuple[int, int]] = []
    for i in range(m):
        try:
            a = int(toks[2 + 2 * i])
            b = int(toks[3 + 2 * i])
        except ValueError:
            return None
        pairs.append((a, b))
    return n, m, pairs


def _scc(nodes: int, adj: list[list[int]], radj: list[list[int]]) -> list[int]:
    """Kosaraju（迭代版）。返回每个结点的 SCC 编号（拓扑序自小到大）。"""
    order: list[int] = []
    seen = bytearray(nodes)
    for s in range(nodes):
        if seen[s]:
            continue
        seen[s] = 1
        stack = [(s, 0)]
        while stack:
            v, pi = stack[-1]
            if pi < len(adj[v]):
                stack[-1] = (v, pi + 1)
                w = adj[v][pi]
                if not seen[w]:
                    seen[w] = 1
                    stack.append((w, 0))
            else:
                order.append(v)
                stack.pop()

    comp = [-1] * nodes
    cid = 0
    for s in reversed(order):
        if comp[s] != -1:
            continue
        comp[s] = cid
        stack = [s]
        while stack:
            v = stack.pop()
            for w in radj[v]:
                if comp[w] == -1:
                    comp[w] = cid
                    stack.append(w)
        cid += 1
    return comp


def _solvable(n: int, pairs: list[tuple[int, int]]) -> bool:
    """独立的 2-SAT 可满足性判定（不依赖 got/want）。"""
    nodes = 2 * n
    if nodes == 0:
        return True
    adj: list[list[int]] = [[] for _ in range(nodes)]
    radj: list[list[int]] = [[] for _ in range(nodes)]
    for a, b in pairs:
        va, vb = a - 1, b - 1
        if not (0 <= va < nodes and 0 <= vb < nodes):
            continue
        # a → ¬b, b → ¬a
        for u, w in ((va, vb ^ 1), (vb, va ^ 1)):
            adj[u].append(w)
            radj[w].append(u)
    comp = _scc(nodes, adj, radj)
    for i in range(n):
        if comp[2 * i] == comp[2 * i + 1]:
            return False
    return True


def check(inp: str, got: str, want: str) -> tuple[bool, str]:
    parsed = _parse_input(inp)
    if parsed is None:
        return False, "判定器无法解析输入"
    n, m, pairs = parsed

    gt = got.split()
    # `want` 只用于「该点是否为 NIE 点」的交叉提示，不参与合法性判定
    want_is_nie = want.split() == ["NIE"]

    if n == 0:
        return (gt == [] or gt == ["NIE"]), f"n=0：期望空输出，实际 {got[:40]!r}"

    solvable = _solvable(n, pairs)

    if not solvable:
        if gt == ["NIE"]:
            return True, "无解（独立 2-SAT 判定不可满足）⇒ 输出 NIE 正确"
        return False, f"该输入无解（独立 2-SAT 判定不可满足）⇒ 应输出 NIE，实际 {got[:60]!r}"

    # 有解
    if gt == ["NIE"]:
        note = "（与 .out 的 NIE 一致）" if want_is_nie else ""
        return False, f"该输入有解（独立 2-SAT 判定可满足）⇒ 不应输出 NIE{note}"

    if len(gt) != n:
        return False, f"应输出恰好 {n} 个代表编号，实际 {len(gt)} 个"

    try:
        reps = [int(x) for x in gt]
    except ValueError:
        return False, "输出含非整数 token"

    if any(r < 1 or r > 2 * n for r in reps):
        bad = [r for r in reps if r < 1 or r > 2 * n][:5]
        return False, f"代表编号越界（应在 1..{2 * n}），例如 {bad}"

    if reps != sorted(reps):
        return False, "输出未按升序排列"

    parties = [(r + 1) // 2 for r in reps]
    if len(set(parties)) != n:
        from collections import Counter

        cnt = Counter(parties)
        dup = [p for p, c in cnt.items() if c != 1][:5]
        return False, f"每个党派须恰有 1 名代表；党派 {dup} 的代表数 != 1"

    chosen = set(reps)
    for a, b in pairs:
        if a in chosen and b in chosen:
            return False, f"厌恶对 ({a}, {b}) 同时入选"

    return True, f"合法委员会：{n} 名代表（升序、每党恰 1 名、无厌恶对冲突）"


if __name__ == "__main__":  # 自测
    demo_in = "3 2\n1 3\n2 4\n"
    for cand in ["1\n4\n5\n", "1\n4\n6\n", "2\n3\n5\n", "2\n3\n6\n", "NIE\n", "1\n3\n5\n"]:
        print(repr(cand), "→", check(demo_in, cand, "1\n4\n5\n"))
    bad_in = "1 1\n1 2\n"  # 两党？n=1，代表 1 与 2 厌恶 ⇒ 无法每党恰 1 名
    print("无解例:", check(bad_in, "NIE\n", "NIE\n"))
