"""1425《加工生产调度》的多解判定（special judge）。

题面原文：
  > 第一行一个数据，表示最少的加工时间；
  > 第二行是**一种**最小加工时间的加工顺序。

⚠ 为什么不能逐字节比对（2026-10-09 实测）：
  本题是**流水作业调度（Johnson 规则）**，最优排列通常**不唯一**。
  实测 `prod1..prod12` 全部 12 个点：
    · `.out` 的**排列结构完全规范**：S1（A≤B）全部在 S2（A>B）之前、
      S1 内 A 升序、S2 内 B 降序 ✅
    · `.out` 的**值**恰等于 Johnson 最优 makespan ✅
    · **但并列时的次序无法复现** —— 试了 5 种 tie-breaker
      （S1/S2 内按 id 升/降、纯 stable 等）**均不匹配**（最多 4/12）。
      原因是出题人用 `std::sort`（**不稳定**）⇒ 并列次序是实现的副产物。

  ⇒ 逐字节比对会把**同样最优但并列次序不同**的合法解判错。
     这是**闸门的适用性缺陷**，不是程序缺陷。

判定原则（见 `spj_registry.py` 的设计约束）：
  **独立验证 `got` 的合法性**，而不是拿 `got` 与 `want` 比较。
  判据两条：
    ① 第一行的数值 == **独立算出的 Johnson 最优 makespan**
    ② 第二行是 `1..n` 的一个**排列**，且该排列的 makespan == 第一行的值

  ★ 注意：**不要求** got 的第二行等于 want 的第二行（题面允许「一种」）。
  ★ 也**不要求** got 的排列满足 S1/S2 结构 ——
    只要 makespan 达到最优即可（这是「最优」的定义，且是更宽的判据）。
    这样即使存在**非 Johnson 形状**的最优排列也能通过。
"""

from __future__ import annotations


def _parse_input(inp: str) -> tuple[int, list[int], list[int]] | None:
    """返回 (n, A, B)；解析失败返回 None。"""
    toks = inp.split()
    if not toks:
        return None
    try:
        n = int(toks[0])
    except ValueError:
        return None
    if n < 0 or len(toks) < 1 + 2 * n:
        return None
    try:
        A = [int(x) for x in toks[1 : 1 + n]]
        B = [int(x) for x in toks[1 + n : 1 + 2 * n]]
    except ValueError:
        return None
    return n, A, B


def _makespan(A: list[int], B: list[int], order: list[int]) -> int:
    """按 order（0-indexed 的任务下标）算完工时间。"""
    t_a = 0
    t_b = 0
    for i in order:
        t_a += A[i]
        if t_b < t_a:
            t_b = t_a
        t_b += B[i]
    return t_b


def _johnson_optimal(n: int, A: list[int], B: list[int]) -> int:
    """Johnson 规则给出的最优 makespan（与 got/want 无关的独立计算）。

    注意：**只取数值**，不取具体排列 —— 因为并列次序不可复现，
    而最优值本身是唯一的。
    """
    if n == 0:
        return 0
    s1 = sorted((i for i in range(n) if A[i] <= B[i]), key=lambda i: A[i])
    s2 = sorted((i for i in range(n) if A[i] > B[i]), key=lambda i: -B[i])
    return _makespan(A, B, s1 + s2)


def check(inp: str, got: str, want: str) -> tuple[bool, str]:
    parsed = _parse_input(inp)
    if parsed is None:
        return False, "判定器无法解析输入"
    n, A, B = parsed

    lines = [ln for ln in got.replace("\r\n", "\n").split("\n") if ln.strip() != ""]
    if len(lines) < 2:
        return False, f"输出应有 2 行（最优时间 + 一个最优排列），实际 {len(lines)} 行"

    try:
        stated = int(lines[0].split()[0])
    except (ValueError, IndexError):
        return False, f"第一行不是整数：{lines[0][:40]!r}"

    opt = _johnson_optimal(n, A, B)
    if stated != opt:
        return False, f"第一行的最优时间错误：得到 {stated}，Johnson 最优为 {opt}"

    perm_toks = lines[1].split()
    if len(perm_toks) != n:
        return False, f"第二行应是 {n} 个编号，实际 {len(perm_toks)} 个"
    try:
        perm = [int(x) for x in perm_toks]
    except ValueError:
        return False, "第二行含非整数 token"

    if sorted(perm) != list(range(1, n + 1)):
        bad = [x for x in perm if x < 1 or x > n][:5]
        if bad:
            return False, f"编号越界（应在 1..{n}），例如 {bad}"
        from collections import Counter

        c = Counter(perm)
        dup = [k for k, v in c.items() if v > 1][:5]
        miss = sorted(set(range(1, n + 1)) - set(perm))[:5]
        return False, f"第二行不是 1..{n} 的排列（重复 {dup}，缺失 {miss}）"

    ms = _makespan(A, B, [x - 1 for x in perm])
    if ms != stated:
        return False, f"第二行的加工时间是 {ms}，与第一行声明的 {stated} 不一致"
    if ms != opt:
        return False, f"该排列不是最优：{ms} > 最优 {opt}"

    return True, f"最优加工时间 {opt} 正确，且第二行排列达到该最优（makespan={ms}）"


if __name__ == "__main__":  # 自测
    demo = "5\n3 5 8 7 10\n6 2 1 4 9\n"
    for cand in ["34\n1 5 4 2 3\n", "34\n1 5 2 4 3\n", "34\n5 1 4 2 3\n",
                 "35\n1 5 4 2 3\n", "34\n1 5 4 2\n", "34\n1 5 4 2 3 6\n"]:
        print(repr(cand.replace("\n", "|")), "→", check(demo, cand, "34\n1 5 4 2 3\n"))
    prod1 = "5\n3 5 8 7 10\n6 3 2 5 8\n"
    print("prod1 原解:", check(prod1, "35\n1 5 4 2 3\n", "35\n1 5 4 2 3\n"))
