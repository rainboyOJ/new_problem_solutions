"""3218《「Team Them Up!」将他们分好队》的多解判定（special judge）。

题面原文：
  > 此任务可能有许多解决方案，你可以输出**任何一种**解决方案，或声明解决方案不存在。

输出格式（逐字节实测）：
  · 无解      → `No solution\\r\\n`（★ 英文，注意空格；行尾是 **CRLF**）
  · 有解      → 两行，每行 `<人数> <成员1> <成员2> ...`
                例 `2 2 4\\r\\n3 1 3 5\\r\\n` ⇒ 队1 = {2,4}，队2 = {1,3,5}

⚠ 为什么不能逐字节比对（2026-10-09 实测）：
  题面明确「可以输出任何一种解决方案」⇒ 不同的合法分队都应判对。
  闸门实测 `main.cpp` 18/56 通过（38 点因方案不同而失败）。
  56 点中 **8 点无解、48 点有解**。

判定原则（见 `spj_registry.py` 的设计约束）：
  **独立验证 `got` 的合法性**，而不是拿 `got` 与 `want` 比较。

建模（与主解不同源地独立求解）：
  · 定义「可同队」= i 认识 j **且** j 认识 i（题面要求「互相认识」）
  · 补图 G'：i—j 有边 ⟺ 【不】可同队
  · 同队 ⇒ 在 G' 中**无边** ⇒ 每队是 G' 的**独立集**
  · 两队划分 = G' 的**二染色**；某连通块非二分 ⇒ **无解**
  · 每个连通块的两色类大小 (a, b) ⇒ 该块给队1 贡献 a 或 b（差 ±(a-b)）
  · 用**背包 DP** 求队1 可达的人数集合 ⇒ 最小规模差 = min |2k - n|
"""

from __future__ import annotations


def _parse_input(inp: str) -> tuple[int, list[set[int]]] | None:
    """返回 (n, know[])，know[i] 是 1-indexed 的「i 认识的人」集合。"""
    toks = inp.split()
    if not toks:
        return None
    try:
        n = int(toks[0])
    except ValueError:
        return None
    if n <= 0:
        return None
    pos = 1
    know: list[set[int]] = [set() for _ in range(n + 1)]
    for i in range(1, n + 1):
        while pos < len(toks):
            v = int(toks[pos]); pos += 1
            if v == 0:
                break
            if 1 <= v <= n:
                know[i].add(v)
        else:
            return None  # 该行没有 0 结尾
    return n, know


def _can_team(know: list[set[int]], i: int, j: int) -> bool:
    """i 与 j 能否同队 ⟺ 互相认识。"""
    return j in know[i] and i in know[j]


def _min_size_diff(n: int, know: list[set[int]]) -> int | None:
    """独立求【最小规模差】；无解返回 None。

    做法：补图（不可同队 ⇒ 连边）的连通块二染色 + 背包 DP。
    """
    # 邻接（补图）
    adj: list[list[int]] = [[] for _ in range(n + 1)]
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            if not _can_team(know, i, j):
                adj[i].append(j)
                adj[j].append(i)

    color = [-1] * (n + 1)
    comps: list[tuple[int, int]] = []   # 每个连通块的两个色类大小 (a, b)
    for s in range(1, n + 1):
        if color[s] != -1:
            continue
        color[s] = 0
        stack = [s]
        cnt = [0, 0]
        while stack:
            u = stack.pop()
            cnt[color[u]] += 1
            for v in adj[u]:
                if color[v] == -1:
                    color[v] = color[u] ^ 1
                    stack.append(v)
                elif color[v] == color[u]:
                    return None    # 奇环 ⇒ 不可二分 ⇒ 无解
        comps.append((cnt[0], cnt[1]))

    # ★ 背包 DP：每个连通块把【其中一个色类】整体分给队1
    #   ⇒ 队1 的人数 = Σ (该块选 a 或选 b)
    #   ⚠ 不能用 k ± |a-b|（那是错的：a-b 不等于块的贡献）
    reach_set = {0}
    for a, b in comps:
        nxt = set()
        for k in reach_set:
            nxt.add(k + a)
            nxt.add(k + b)
        reach_set = nxt
    best = None
    for k in reach_set:
        if 0 <= k <= n:
            diff = abs(2 * k - n)
            if best is None or diff < best:
                best = diff
    return best


def _parse_teams(got: str, n: int) -> tuple[list[int], list[int]] | str:
    """返回 (team1, team2) 或错误说明字符串。"""
    lines = [ln for ln in got.replace("\r\n", "\n").split("\n") if ln.strip() != ""]
    if len(lines) != 2:
        return f"有解时应输出恰好 2 行（每行 `<人数> <成员...>`），实际 {len(lines)} 行"
    teams: list[list[int]] = []
    for ln in lines:
        parts = ln.split()
        try:
            cnt = int(parts[0])
        except (ValueError, IndexError):
            return f"行首不是整数：{ln[:40]!r}"
        members = []
        for x in parts[1:]:
            try:
                members.append(int(x))
            except ValueError:
                return f"成员含非整数：{x!r}"
        if cnt != len(members):
            return f"声明人数 {cnt} 与实际成员数 {len(members)} 不符"
        teams.append(members)
    return teams[0], teams[1]


def check(inp: str, got: str, want: str) -> tuple[bool, str]:
    parsed = _parse_input(inp)
    if parsed is None:
        return False, "判定器无法解析输入"
    n, know = parsed

    gt = got.replace("\r\n", "\n").strip()
    got_is_nie = gt.lower().startswith("no solution")
    best = _min_size_diff(n, know)

    if best is None:
        if got_is_nie:
            return True, "无解（独立二染色发现奇环）⇒ 输出 `No solution` 正确"
        return False, "该输入【无解】（独立二染色发现奇环）⇒ 应输出 `No solution`"

    if got_is_nie:
        return False, "该输入【有解】（独立二染色成功）⇒ 不应输出 `No solution`"

    parsed_teams = _parse_teams(got, n)
    if isinstance(parsed_teams, str):
        return False, parsed_teams
    t1, t2 = parsed_teams

    if len(t1) == 0 or len(t2) == 0:
        return False, "每个团队至少要有 1 名成员"
    allm = t1 + t2
    if sorted(allm) != list(range(1, n + 1)):
        from collections import Counter
        c = Counter(allm)
        dup = [k for k, v in c.items() if v > 1][:5]
        miss = sorted(set(range(1, n + 1)) - set(allm))[:5]
        bad = [x for x in allm if x < 1 or x > n][:5]
        return False, (f"两队并集必须是 1..{n} 的一个划分"
                       f"（重复 {dup}，缺失 {miss}，越界 {bad}）")

    for name, team in (("队1", t1), ("队2", t2)):
        for a in range(len(team)):
            for b in range(a + 1, len(team)):
                u, v = team[a], team[b]
                if not _can_team(know, u, v):
                    return False, f"{name}中 {u} 与 {v} 并非【互相认识】"

    diff = abs(len(t1) - len(t2))
    if diff != best:
        return False, (f"两队规模差为 {diff}（{len(t1)} vs {len(t2)}），"
                       f"但最小可达规模差为 {best} ⇒ 未达到「尽可能接近」")

    return True, (f"合法分队：{len(t1)} vs {len(t2)}（规模差 {diff} = 最小值），"
                  f"两队内部两两互相认识")


if __name__ == "__main__":  # 自测
    demo = "5\r\n2 3 5 0\r\n1 4 5 3 0\r\n1 2 5 0\r\n1 2 3 0\r\n4 3 2 1 0\r\n"
    print("样例原解      :", check(demo, "2 2 4\r\n3 1 3 5\r\n", ""))
    print("交换两队      :", check(demo, "3 1 3 5\r\n2 2 4\r\n", ""))
    print("规模差非最小  :", check(demo, "1 1\r\n4 2 3 4 5\r\n", ""))
    print("队内不互识    :", check(demo, "2 1 2\r\n3 3 4 5\r\n", ""))
    print("无解点给解    :", check("5\r\n3 4 5 0\r\n1 3 5 0\r\n2 1 4 5 0\r\n2 3 5 0\r\n1 2 3 4 0\r\n",
                                  "2 1 2\r\n3 3 4 5\r\n", "No solution"))
    print("无解点正确    :", check("5\r\n3 4 5 0\r\n1 3 5 0\r\n2 1 4 5 0\r\n2 3 5 0\r\n1 2 3 4 0\r\n",
                                  "No solution\r\n", "No solution"))
    print("有解点误报无解:", check(demo, "No solution\r\n", ""))
