#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:42
# update_at: 2026-10-07 15:42

import sys

# 每个字母在 S 中留一个只增不减的游标：游标指向该字母在"当前窗口左端及之后"的
# 首次出现位置。窗口左端单调右移，游标永不回退。
# 窗口 [p, p+m-1] 能编码成 T 的两条判据：模式同构（比较 prev 编码）+ 对合律。

type Occ = dict[str, list[int]]      # 字母 -> 在 S 中出现的下标（升序）
type ByLetter = dict[str, int]       # 字母 -> 一个位置（最近出现 / 首次出现 / 窗口游标）
type Index = tuple[str, Occ, ByLetter]  # (S, 出现位置表, 游标表)，判定对合律时一起传


def prev_codes(x: str) -> list[int]:
    """prev 编码：某位字符与它上一次出现的距离，首次出现记 0。"""
    last: ByLetter = {}
    codes: list[int] = []
    for i, c in enumerate(x):
        codes.append(i - last.get(c, i))  # 未出现过时 last.get 回退到 i，差为 0
        last[c] = i
    return codes


def aligned(pat_val: int, text_prev: int, k: int) -> bool:
    """模式串第 k 位的 prev 值能否与"窗口内相对第 k 位"的文本位对齐。

    text_prev 超过 k 说明该字符上一次出现在窗口之外，它在窗口内是首次出现，
    编码应当取 0；否则窗口内的编码就是 text_prev 本身。
    """
    window_code = text_prev if text_prev <= k else 0
    return pat_val == window_code


def isomorphic_starts(pv_s: list[int], pv_t: list[int], n: int, m: int) -> list[int]:
    """产出所有与模式串"模式同构"的窗口起点（0-based）。

    比较规则换成 prev 编码后，KMP 照常成立：border 表也按同一规则算。
    """
    fail = [0] * (m + 1)
    k = 0
    for j in range(1, m):
        while k and not aligned(pv_t[k], pv_t[j], k):
            k = fail[k]
        if aligned(pv_t[k], pv_t[j], k):
            k += 1
        fail[j + 1] = k

    starts: list[int] = []
    k = 0
    for i in range(n):
        while k and not aligned(pv_t[k], pv_s[i], k):
            k = fail[k]
        if aligned(pv_t[k], pv_s[i], k):
            k += 1
        if k == m:
            starts.append(i - m + 1)
            k = fail[m]
    return starts


def involute_ok(p: int, m: int, t: str, first_t: ByLetter, idx: Index) -> bool:
    """窗口 [p, p+m-1] 是否满足对合律（模式同构已经把双射 g 完全定死）。

    T 中字母 b 首次出现在第 first_t[b] 位，模式同构迫使 g(S[p+q]) = b；
    若 b 也出现在窗口内，则窗口内 b 的首次出现位置 j 必须满足 g(b) = T[j]。
    """
    s, occ, curs = idx
    right = p + m - 1
    for b, q in first_t.items():
        positions = occ.get(b)
        if positions is None:
            continue                            # b 在 S 中根本不出现，窗内必无
        size = len(positions)
        c = curs[b]
        while c < size and positions[c] < p:    # 游标只增不减，均摊 O(1)
            c += 1
        curs[b] = c
        if c == size or positions[c] > right:
            continue                            # b 不在窗口内，对合律不约束它
        jb = positions[c] - p                   # 窗口内 b 首次出现的位置（0-based）
        if t[jb] != s[p + q]:                   # g(b) 应当等于 g^-1 推回的字母 a
            return False
    return True


def build_index(s: str, t: str) -> tuple[ByLetter, Index]:
    """把两个串物化成对合律检查需要的查表：(T 的首现位置表, 对合律检查状态)。"""
    occ: Occ = {}
    for i, c in enumerate(s):
        occ.setdefault(c, []).append(i)
    first_t: ByLetter = {}                      # T 中每个字母的首次出现位置（0-based）
    for j, c in enumerate(t):
        first_t.setdefault(c, j)
    return first_t, (s, occ, dict.fromkeys(first_t, 0))


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n, m = int(next(data)), int(next(data))
    s, t = next(data).decode(), next(data).decode()

    first_t, idx = build_index(s, t)

    ans = [p + 1 for p in isomorphic_starts(prev_codes(s), prev_codes(t), n, m)
           if involute_ok(p, m, t, first_t, idx)]

    out = [str(len(ans))]
    if ans:
        out.append(' '.join(map(str, ans)))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
