#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:18
# update_at: 2026-10-07 15:33

import sys

COMMA_FIRST = ",0123456789"  # '?' 的候选字符：',' 的 ASCII 是 44，小于所有数字，所以排在最前


def rank(num: str) -> tuple[int, str]:
    """无前导 0 的数字串的比较键：先比位数，再比字典序。"""
    return (len(num), num)


def minimal_number(pat: str, start: int, stop: int, lower: str) -> str:
    """把 pat[start:stop] 填成一个合法数字并尽量小：首位非 0、段内不含固定逗号、
    数值严格大于 lower（lower 为空串表示无下界）；填不出数字时返回空串。
    """
    length = stop - start
    if length <= 0:
        return ""
    base = "".join(                    # base = 忽略下界时这一段的"最小匹配数字"
        pat[i] if pat[i] != "?" else ("1" if i == start else "0") for i in range(start, stop)
    )
    if "," in base or base[0] == "0":
        return ""                      # 段内被固定逗号截断，或这一位只能放 0（前导 0 / 空数字）
    if rank(base) > rank(lower):
        return base                    # 已经比下界大，且是同位数里最小的
    if len(base) < len(lower):
        return ""                      # 位数比下界少，这一段的任何填法都不够大

    # 同位数且 base <= lower：任何更大的数都在"第一个超过 lower 的位置 j"上变大，
    # 前缀与 lower 相同、第 j 位放大、后面取最小；j 越靠右结果越小，所以从右往左找。
    for j in range(length - 1, -1, -1):
        if any(pat[start + i] not in ("?", lower[i]) for i in range(j)):
            continue                   # 前缀与 lower 冲突，这一段无法在 j 处变大
        pick = next((c for c in "123456789" if c > lower[j] and pat[start + j] in ("?", c)), "")
        if not pick:
            continue
        tail = "".join("0" if pat[i] == "?" else pat[i] for i in range(start + j + 1, stop))
        return lower[:j] + pick + tail
    return ""


def completable(pat: str) -> bool:
    """pat 里剩下的 '?' 还能否补成合法串。

    按"最后一个逗号的位置"从左往右递推：每个位置只保留左侧最后一个数最小的那条路径，
    因为下界更小对后面只会更宽松，丢掉别的路径不会丢解。
    """
    n = len(pat)
    best: list[str | None] = [None] * (n + 2)  # best[c + 1] = 逗号落在 c 时左端最后一个数的最小值
    best[0] = ""                               # 虚拟起点（逗号位置 -1）：还没有数字，无下界
    farthest = 0                               # 已被点亮的最大状态下标

    for c in range(-1, n):
        lower = best[c + 1]
        if lower is None:
            if c + 1 > farthest:
                break                          # 转移只向右，右侧没有点亮的状态，后面永远断线
            continue                           # 这个逗号位置走不到
        for stop in range(c + 2, n + 1):       # 当前数字段是 pat[c + 1:stop]
            if stop < n and pat[stop] not in "?,":
                continue                       # 段后面必须能放逗号（或这一段到串尾）
            value = minimal_number(pat, c + 1, stop, lower)
            if not value:
                continue
            if stop == n:
                return True                    # 最后一段也填出了合法数字，整体可行
            old = best[stop + 1]
            if old is None or rank(value) < rank(old):
                best[stop + 1] = value         # 逗号落在 stop，位置 stop + 1 即状态下标
                farthest = max(farthest, stop + 1)
    return False


def restore(pat: str) -> str:
    """把 pat 还原成字典序最小的合法串；无解时返回 'impossible'。

    先判定整体可不可行，再逐位贪心：每个 '?' 留下第一个仍能补全的字符。
    """
    if not completable(pat):
        return "impossible"
    chars = list(pat)
    for i, ch in enumerate(chars):
        if ch != "?":
            continue                           # 题目固定的字符必须原样保留
        for c in COMMA_FIRST:
            chars[i] = c
            candidate = "".join(chars)         # 这一位取 c 之后的候选串
            if completable(candidate):
                break
            chars[i] = "?"
    return "".join(chars)


def solve() -> None:
    data = iter(sys.stdin.read().split())
    T = int(next(data))
    out: list[str] = []

    for _ in range(T):
        out.append(restore(next(data)))

    print("\n".join(out))


if __name__ == "__main__":
    solve()
