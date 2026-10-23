"""P3825《[NOI2017] 游戏》的多解判定（special judge）。

题面原文：
  > 输出一行。
  > 若无解输出 `-1`。
  > 若有解，则包含一个长度为 n 的仅包含大写字母 A、B、C 的字符串……
  > 如果存在多组解，输出其中任意一组即可。

⚠ 为什么不能逐字节比对：
  样例只有 3 场游戏 + 1 条规则，合法解有多组（样例文件给的是 `ABA`，
  「禁 A / 禁 B 枚举 + 2-SAT」的常规实现通常得到 `BAA`），两者都满足全部规则。
  逐字节比对会把合法解判成 WA。

判定原则（见 `spj_registry.py` 的设计约束）：
  **独立验证 got 的合法性**，而不是拿 got 与 want 比较。
  ① got 是 `-1` 时，必须独立确认问题确实无解（枚举所有合法赋值，
     赋值的搜索空间是 3^n，只对 n 较小的情况做穷举，n 大时退化为
     「want 也是 -1 或 got 与 want 相同结构」的弱化确认）；
  ② got 是一行长度 n 的 A/B/C 串时，逐场检查该车不被地图禁止，
     再逐条检查规则是否满足；
  ③ 其他情况一律不合法。

⚠ 这个判定器只服务于 `check_sample.py`（本地样例自测）。正确性验证用的是
`problem-analysis-workspace` 里记录的对拍，那里的暴力基线会独立给出解或无解。
"""

from __future__ import annotations

import itertools

BRUTE_LIMIT = 12  # 独立确认「无解」时做 3^n 穷举的最大 n


def _parse_input(inp: str):
    toks = inp.split()
    if len(toks) < 4:
        return None
    try:
        n = int(toks[0])
        d = int(toks[1])
    except ValueError:
        return None
    s = toks[2]
    if len(s) != n:
        return None
    p = 3
    try:
        m = int(toks[p])
    except ValueError:
        return None
    p += 1
    if len(toks) < p + 4 * m:
        return None
    rules = []
    for _ in range(m):
        try:
            i = int(toks[p])
        except ValueError:
            return None
        hi = toks[p + 1]
        try:
            j = int(toks[p + 2])
        except ValueError:
            return None
        hj = toks[p + 3]
        p += 4
        if hi not in "ABC" or hj not in "ABC":
            return None
        if not (1 <= i <= n and 1 <= j <= n):
            return None
        rules.append((i, hi, j, hj))
    return n, d, s, m, rules


def _allowed(s_ch: str, car: str) -> bool:
    """地图 s_ch 是否允许赛车 car（'A'/'B'/'C'）。"""
    if s_ch == "x":
        return True
    return s_ch.upper() != car


def _candidates(s_ch: str):
    return [c for c in "ABC" if _allowed(s_ch, c)]


def _validate_answer(ans: str, n: int, s: str, rules) -> tuple[bool, str]:
    if len(ans) != n:
        return False, f"答案长度为 {len(ans)}，应为 {n}"
    if any(ch not in "ABC" for ch in ans):
        return False, "答案只能包含大写字母 A、B、C"
    for pos in range(n):
        if not _allowed(s[pos], ans[pos]):
            return False, f"第 {pos + 1} 场地图 {s[pos]} 不允许赛车 {ans[pos]}"
    for i, hi, j, hj in rules:
        if ans[i - 1] == hi and ans[j - 1] != hj:
            return False, f"规则 ({i},{hi},{j},{hj}) 被违反"
    return True, "合法"


def _solution_exists(n: int, s: str, rules) -> bool | None:
    """穷举全部合法赋值确认是否有解；n 太大时返回 None 表示无法确认。"""
    if n > BRUTE_LIMIT:
        return None
    pools = [_candidates(s[pos]) for pos in range(n)]
    for combo in itertools.product(*pools):
        ok = True
        for i, hi, j, hj in rules:
            if combo[i - 1] == hi and combo[j - 1] != hj:
                ok = False
                break
        if ok:
            return True
    return False


def check(inp: str, got: str, want: str) -> tuple[bool, str]:
    parsed = _parse_input(inp)
    if parsed is None:
        return False, "输入解析失败"
    n, _d, s, _m, rules = parsed

    lines = [ln.strip() for ln in got.strip().splitlines()]
    lines = [ln for ln in lines if ln]
    if len(lines) != 1:
        return False, f"输出应为恰好一行，实际 {len(lines)} 行"
    ans = lines[0]

    if ans == "-1":
        exists = _solution_exists(n, s, rules)
        want_lines = [ln.strip() for ln in want.strip().splitlines() if ln.strip()]
        want_is_minus1 = len(want_lines) == 1 and want_lines[0] == "-1"
        if exists is True:
            return False, "输出 -1，但存在合法方案"
        if exists is False:
            return True, "-1（已穷举确认无解）"
        # n 太大无法穷举：只接受「标准答案也是 -1」这种较弱的一致性证据
        if want_is_minus1:
            return True, "-1（与标准答案一致，未能穷举验证）"
        return False, "输出 -1，但标准答案给出了方案，无法确认无解"

    ok, detail = _validate_answer(ans, n, s, rules)
    if not ok:
        return False, detail
    return True, f"{ans}（逐条规则校验通过）"
