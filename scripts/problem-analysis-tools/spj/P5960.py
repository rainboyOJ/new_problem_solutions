"""P5960《【模板】差分约束》的多解判定（special judge）。

题面原文：
  > 一行，n 个数，表示 x_1, x_2, ..., x_n 的一组可行解，
  > 如果有多组解，请输出任意一组，无解请输出 `NO`。

⚠ 为什么不能逐字节比对：
  SPFA 初始把所有点距离设为 0 并全部入队，跑出来的是**分量最小**的那组解
  （样例得到的是 `0 -2 0`），而题面给的标准答案是 `5 3 5`。
  两者都满足全部不等式，用「是否等于 out1」判定会把合法解误判为 WA。

判定原则（见 `spj_registry.py` 的设计约束）：
  **独立验证 got 的合法性**，而不是拿 got 与 want 比较。
  ① got 是 `NO` 时，必须独立确认约束确实矛盾；
  ② got 是一行 n 个整数时，逐个检查 x_c - x_c' <= y 是否全部成立，
     并要求取值在 int 范围内（题面要求）。
  ③ got 既不是 NO 也不是 n 个整数 → 不合法。
"""

from __future__ import annotations

INT_MIN = -2**31
INT_MAX = 2**31 - 1


def _parse_input(inp: str) -> tuple[int, int, list[tuple[int, int, int]]] | None:
    toks = inp.split()
    if len(toks) < 2:
        return None
    try:
        n, m = int(toks[0]), int(toks[1])
    except ValueError:
        return None
    if n <= 0 or m < 0 or len(toks) < 2 + 3 * m:
        return None
    cons: list[tuple[int, int, int]] = []
    for i in range(m):
        try:
            c, c2, y = int(toks[2 + 3 * i]), int(toks[3 + 3 * i]), int(toks[4 + 3 * i])
        except ValueError:
            return None
        cons.append((c, c2, y))
    return n, m, cons


def _violations(values: list[int], cons: list[tuple[int, int, int]]) -> list[int]:
    bad = []
    for idx, (c, c2, y) in enumerate(cons, 1):
        if values[c - 1] - values[c2 - 1] > y:
            bad.append(idx)
    return bad


def _feasible(n: int, cons: list[tuple[int, int, int]]) -> bool:
    """独立判可行性：Bellman-Ford 式全源松弛，负环即无解（不复用被测程序的实现）。"""
    INF = 1 << 62
    dis = [0] * n  # 全局可行性检查：等价于 0 权超级源
    for _ in range(n):
        changed = False
        for c, c2, y in cons:
            # x_c <= x_c' + y，松弛 c2 -> c
            cand = dis[c2 - 1] + y
            if cand < dis[c - 1] and cand > -INF:
                dis[c - 1] = cand
                changed = True
        if not changed:
            return True
    return False


def check(inp: str, got: str, want: str) -> tuple[bool, str]:
    parsed = _parse_input(inp)
    if parsed is None:
        return False, "判定器无法解析输入"
    n, m, cons = parsed

    toks = got.split()
    feasible = _feasible(n, cons)

    if toks == ["NO"]:
        if feasible:
            return False, "题面：无解才输出 NO，但该约束组存在可行解"
        return True, "约束组确实矛盾，输出 NO 正确"

    if len(toks) != n:
        return False, f"应输出 {n} 个整数或 NO，实际 {len(toks)} 个 token"
    try:
        values = [int(t) for t in toks]
    except ValueError:
        return False, "输出含非整数 token"

    bad_range = [v for v in values if v < INT_MIN or v > INT_MAX]
    if bad_range:
        return False, f"取值超出 int 范围，例如 {bad_range[:3]}"

    bad = _violations(values, cons)
    if bad:
        c, c2, y = cons[bad[0] - 1]
        return False, (
            f"第 {bad[0]} 条约束不满足：x_{c} - x_{c2} = "
            f"{values[c - 1] - values[c2 - 1]} > {y}（共 {len(bad)} 条违反）"
        )

    return True, f"全部 {m} 条 x_c - x_c' <= y 约束均满足"


if __name__ == "__main__":  # 自测
    demo = "3 3\n1 2 3\n2 3 -2\n1 3 1\n"
    for cand in ["5 3 5\n", "0 -2 0\n", "0 0 0\n", "NO\n", "1 2\n", "a b c\n"]:
        print(repr(cand.strip()), "→", check(demo, cand, "5 3 5\n"))
    unsat = "2 2\n1 2 1\n2 1 -2\n"
    for cand in ["NO\n", "0 0\n"]:
        print(repr(cand.strip()), "→", check(unsat, cand, "NO\n"))
