"""3072《八数码》的多解判定（special judge）。

题面原文：
  > 输出占一行，包含一个字符串，表示得到正确排列的完整行动记录。
  > **如果答案不唯一，输出任意一种合法方案即可。**
  > 如果不存在解决方案，则输出 "unsolvable"。

⚠ 为什么不能逐字节比对（2026-10-08 实测）：
  输入 `6 4 7 8 5 x 3 2 1`
    期望 `dluldrurulldrrulldrrdllurrulddr`（31 步）
    程序 `dllururddlluurrddlulurrdldlurdr`（31 步）
  两者**都是合法最短解**，题面明确允许任意方案 ⇒ 逐字节比对必然把合法解判错。
  这是**闸门的适用性缺陷**，不是程序缺陷。

判定原则：**独立验证 got 的合法性**，而不是拿 got 与 want 比较。
由于本题明确「任意合法方案即可」，我们**不要求最短**（题面没要求）；
但会额外报告步数，便于人工判断是否明显劣化。
"""

from __future__ import annotations

TARGET = "12345678x"
MOVES = {"u": (-1, 0), "d": (1, 0), "l": (0, -1), "r": (0, 1)}


def _normalize_input(inp: str) -> list[str] | None:
    toks = inp.split()
    if len(toks) != 9:
        return None
    # 统一小写 x（题面与数据都用小写 x，但容忍大写）
    return ["x" if t.lower() == "x" else t for t in toks]


def _apply(state: list[str], op: str) -> list[str] | None:
    k = state.index("x")
    r, c = divmod(k, 3)
    if op not in MOVES:
        return None
    dr, dc = MOVES[op]
    nr, nc = r + dr, c + dc
    if not (0 <= nr < 3 and 0 <= nc < 3):
        return None          # 越界 ⇒ 非法移动
    s = state[:]
    j = nr * 3 + nc
    s[k], s[j] = s[j], s[k]
    return s


def _is_connected(state: list[str]) -> bool:
    """可解性：忽略 x 后的逆序数奇偶性必须与目标相同（目标逆序数 0）。"""
    seq = [int(t) for t in state if t != "x"]
    inv = sum(1 for i in range(len(seq)) for j in range(i + 1, len(seq)) if seq[i] > seq[j])
    return inv % 2 == 0


def check(inp: str, got: str, want: str) -> tuple[bool, str]:
    start = _normalize_input(inp)
    if start is None:
        return False, f"输入不是 9 个 token：{inp.split()!r}"

    got_raw = got
    got_line = got.strip()
    want_line = want.strip()

    # ── 情形 1：got 判无解 ──
    if got_line == "unsolvable":
        solvable = _is_connected(start)
        if want_line == "unsolvable":
            return True, "两者一致判定 unsolvable"
        # want 给了方案：用逆序数独立裁决谁对
        if solvable:
            return False, "本实现判 unsolvable，但逆序数表明有解"
        return True, "本实现正确判定 unsolvable（期望侧给了方案，属期望数据问题）"

    # ── 情形 2：got 给了方案（含空串）⇒ 必须**实际模拟验证**，
    #    不能因为 want == unsolvable 就直接放行。
    #    （worker-26 在 3072 上发现的漏判：可解输入 + want=unsolvable +
    #      got='uuuu' 曾被放行。）
    #
    #    合法解是否允许为空串？目标态输入时答案为空（不需任何操作），
    #    所以**空串是合法输出**（但仅限输入已是目标态）。
    if got_line == "" and got_raw.strip() != "":
        return False, "本实现输出为空白"
    for ch in got_line:
        if ch not in MOVES:
            return False, f"输出含非法字符 {ch!r}（只允许 u/d/l/r）"

    state = start[:]
    for step, op in enumerate(got_line):
        nxt = _apply(state, op)
        if nxt is None:
            return False, f"第 {step + 1} 步 {op!r} 越界（空格在 {state.index('x')}）"
        state = nxt

    if "".join(state) != TARGET:
        return False, (f"执行 {len(got_line)} 步后未到达目标；"
                       f"终态 = {''.join(state)}（空格在 {state.index('x')}）")

    # 走到这里：got 已被**独立模拟**证实是合法解。
    # 若 want 说无解，那就是期望侧的问题（但 got 仍然合法）。
    if want_line == "unsolvable":
        return True, (f"本实现给出合法解（{len(got_line)} 步，已模拟验证到达目标），"
                      f"而期望是 unsolvable；逆序数表明有解")

    detail = f"合法解，{len(got_line)} 步"
    if got_line == "":
        detail += "（输入已是目标态，空操作序列合法）"
    if want_line and want_line != got_line:
        detail += f"（与期望方案不同但同为合法解；期望 {len(want_line)} 步）"
    return True, detail
