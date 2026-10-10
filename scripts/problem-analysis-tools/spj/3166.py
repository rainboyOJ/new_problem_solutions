"""3166《Trip 旅行》的判定器（special judge）。

题面原文（【输出格式】）：
  > 按**升序**顺序输出所有满足条件的路线列表。
  > 每个路线列表占一行。

⚠ 为什么不能逐字节比对（2026-10-09 实测）：
  题面明确要求「按升序（字典序）输出」，**但数据的 `.out` 不是字典序**！
  实测 11/11 点全部 `字典序=False`。例：
    trip1.in  = `abcabcaa` / `acbacba`   （LCS 长度 = 5，共 7 个）
    trip1.out = ababa abaca abcba 【acbca】 acaba acaca acbaa
    字典序     = ababa abaca abcba 【acaba】 acaca acbaa 【acbca】
    ⇒ 差别只在 `acbca` 的位置 ⇒ `.out` 违反题面的「升序」要求
      ⇒ **数据缺陷**（题面与数据不一致）

  另一处不一致：题面的【输出样例】只给了 6 行（缺 `acbca`），
  而数据的 `trip1.out` 有 7 行 —— 即**样例本身也不完整**。

判定原则（见 `spj_registry.py` 的设计约束）：
  **独立验证 `got` 的合法性**，而不是拿 `got` 与 `want` 比较。
  判据：
    ① `got` 的每一行都是 A、B 的**公共子序列**
    ② 每行的长度都等于 **LCS 长度 L**（即都是最长）
    ③ `got` 的**集合**恰好等于【全部**不同**的最长公共子序列】的集合
       （⇒ 既不能少、也不能多、也不能重复）
    ④ ★ 额外报告 `got` 是否按字典序（题面要求），但**不据此判错**
       —— 因为数据的 `.out` 自己就不满足，无法作为标准。

★ 第 ③ 条用「枚举全部不同 LCS」实现：DP 求长度 + 按字母序 DFS，
  每一步只取每个字符在两侧的**首次出现**，且要求取该字符后仍在最优路径上
  ⇒ 每个不同的 LCS **恰好枚举一次**（输出多项式复杂度）。
"""

from __future__ import annotations


def _parse_input(inp: str) -> tuple[str, str] | None:
    toks = inp.split()
    if len(toks) < 2:
        return None
    return toks[0], toks[1]


def _lcs_table(a: str, b: str) -> list[list[int]]:
    """dp[i][j] = LCS 长度 of a[i:], b[j:]。"""
    n, m = len(a), len(b)
    dp = [[0] * (m + 1) for _ in range(n + 1)]
    for i in range(n - 1, -1, -1):
        row, nxt = dp[i], dp[i + 1]
        for j in range(m - 1, -1, -1):
            if a[i] == b[j]:
                row[j] = nxt[j + 1] + 1
            else:
                row[j] = nxt[j] if nxt[j] >= row[j + 1] else row[j + 1]
    return dp


def _all_lcs(a: str, b: str, limit: int = 2_000_000) -> set[str] | None:
    """枚举【全部不同的】最长公共子序列。超过 limit 个则返回 None。"""
    dp = _lcs_table(a, b)
    L = dp[0][0]
    if L == 0:
        return {""}
    out: set[str] = set()
    n, m = len(a), len(b)

    def rec(pa: int, pb: int, cur: str) -> bool:
        if len(cur) == L:
            out.add(cur)
            return len(out) <= limit
        need = L - len(cur) - 1
        # 两侧剩余字符的交集，按字母序（决定枚举顺序，不影响集合）
        rest_a = set(a[pa:])
        for c in sorted(rest_a & set(b[pb:])):
            ia = a.index(c, pa)
            ib = b.index(c, pb)
            if dp[ia + 1][ib + 1] == need:
                if not rec(ia + 1, ib + 1, cur + c):
                    return False
        return True

    if not rec(0, 0, ""):
        return None
    return out


def check(inp: str, got: str, want: str) -> tuple[bool, str]:
    parsed = _parse_input(inp)
    if parsed is None:
        return False, "判定器无法解析输入"
    a, b = parsed

    lines = [ln.strip() for ln in got.replace("\r\n", "\n").split("\n")]
    lines = [ln for ln in lines if ln != ""]

    dp = _lcs_table(a, b)
    L = dp[0][0]

    if L == 0:
        if lines == [""] or lines == []:
            return True, "LCS 长度为 0 ⇒ 输出为空"
        return False, f"LCS 长度为 0 ⇒ 不应有输出，实际 {lines[:3]!r}"

    if not lines:
        return False, f"应输出全部最长公共子序列（长度 {L}），实际无输出"

    # ①② 每行都是长度 L 的公共子序列
    for s in lines:
        if len(s) != L:
            return False, f"行 {s!r} 长度 {len(s)} != 最长长度 {L}"
        it = iter(a)
        if not all(ch in it for ch in s):
            return False, f"行 {s!r} 不是 A={a!r} 的子序列"
        it = iter(b)
        if not all(ch in it for ch in s):
            return False, f"行 {s!r} 不是 B={b!r} 的子序列"

    # ③ 集合相等
    if len(set(lines)) != len(lines):
        from collections import Counter

        dup = [k for k, v in Counter(lines).items() if v > 1][:3]
        return False, f"输出有重复行：{dup}"

    truth = _all_lcs(a, b)
    if truth is None:
        return False, "判定器枚举 LCS 数量过多（超过上限），无法判定"

    gs = set(lines)
    if gs != truth:
        missing = sorted(truth - gs)[:5]
        extra = sorted(gs - truth)[:5]
        return False, (
            f"输出集合与全部最长公共子序列不符："
            f"应有 {len(truth)} 个、实际 {len(gs)} 个；"
            f"缺少 {missing}；多出 {extra}"
        )

    # ④ 顺序只报告、不判错
    ordered = lines == sorted(lines)
    note = "且按字典序升序" if ordered else "（★ 未按字典序；题面要求升序，但数据 .out 自身也不升序）"
    return True, f"输出 {len(lines)} 个最长公共子序列（长度 {L}），集合完整{note}"


if __name__ == "__main__":  # 自测
    demo = "abcabcaa\nacbacba\n"
    print("样本(字典序):", check(demo, "ababa\nabaca\nabcba\nacaba\nacaca\nacbaa\nacbca\n", ""))
    print("数据(非字典序):", check(demo, "ababa\nabaca\nabcba\nacbca\nacaba\nacaca\nacbaa\n", ""))
    print("缺一个:", check(demo, "ababa\nabaca\nabcba\nacaba\nacaca\nacbaa\n", ""))
    print("多一个(非最优):", check(demo, "ababa\nabaca\nabcba\nacbca\nacaba\nacaca\nacbaa\nabab\n", ""))
    print("重复:", check(demo, "ababa\nababa\nabaca\nabcba\nacbca\nacaba\nacaca\nacbaa\n", ""))
