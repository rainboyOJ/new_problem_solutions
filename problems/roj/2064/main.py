#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 06:54
# update_at: 2026-10-01 06:54

import sys
from functools import cache

T: str = "Begin the Escape execution at the Break of Dawn"  # 目标原文
N: int = len(T)  # 47
PAIRS: set[tuple[str, str]] = set(zip(T, T[1:]))  # T 中全部相邻字母对
SORTED_T: list[str] = sorted(T)  # T 的字母多重集
STRIP_COW: dict[int, None] = {ord(ch): None for ch in "COW"}  # 删掉 C/O/W 的翻译表


@cache
def dfs(s: str) -> bool:
    """判断密文 s 能否解密成 T：逆向枚举一步加密的 (C, O, W)，失败状态全部记忆化。"""
    if s == T:
        return True
    c: int = s.count("C")
    # 守恒剪枝：每解密一次长度 -3、C/O/W 各减 1，其余字母不变
    if c == 0 or len(s) != N + 3 * c or s.count("O") != c or s.count("W") != c:
        return False
    # 首个 C 之前、末个 W 之后的字符在所有交换中都不可移动
    p: int = s.find("C")
    q: int = s.rfind("W")
    if s[:p] != T[:p] or s[q + 1:] != T[N - (len(s) - q - 1):]:
        return False
    # 连续性剪枝：每段极大非标记子串只会被整段搬运，永远连续，故必是 T 的子串
    if any(seg and T.find(seg) < 0 for seg in s.replace("O", "C").replace("W", "C").split("C")):
        return False
    # 邻接剪枝：非标记序列里每个「T 中不相邻」的字母对至少要一次交换才能修复，
    # 一次交换只改 3 个邻接位置，故缺扣数不能超过剩余步数 3c
    nm: str = s.translate(STRIP_COW)
    if (N - 1) - sum((a, b) in PAIRS for a, b in zip(nm, nm[1:])) > 3 * c:
        return False
    # 枚举一组 (C, O, W)：i < j < k，逆着一步加密还原
    cs: tuple[int, ...] = tuple(i for i, ch in enumerate(s) if ch == "C")
    os_: tuple[int, ...] = tuple(i for i, ch in enumerate(s) if ch == "O")
    ws: tuple[int, ...] = tuple(i for i, ch in enumerate(s) if ch == "W")
    for i in cs:
        a: str = s[:i]  # 前段 A
        for j in os_:
            if j <= i:
                continue
            y: str = s[i + 1:j]  # C~O 之间的 Y
            for k in ws:
                if k <= j:
                    continue
                # 交换两段并删掉标记：A + X + Y + Z
                if dfs(a + s[j + 1:k] + y + s[k + 1:]):
                    return True
    return False


def main() -> None:
    data = iter(sys.stdin.buffer.read().splitlines())
    s: str = next(data).decode()
    # 其余字母的多重集是守恒量，先与目标比一次
    if sorted(ch for ch in s if ch not in "COW") != SORTED_T:
        print("0 0")
    elif dfs(s):
        print(f"1 {s.count('C')}")  # 加密次数 = C 的个数
    else:
        print("0 0")


if __name__ == "__main__":
    main()
