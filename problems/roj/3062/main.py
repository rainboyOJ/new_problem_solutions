#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 13:05
# update_at: 2026-10-01 13:20

import sys
from collections.abc import Iterator

MAX_PIECE = 50  # 题面保证每节不超过 50 个单位；数据里混进的更长木棍不合法，直接忽略


def candidate_lengths(sticks: list[int]) -> Iterator[int]:
    """从小到大产出可能的目标长度：总长的因数，且不小于最长的那一节。

    sticks 已按降序排列，所以 sticks[0] 就是最长的一节。目标木棒越长根数越少，
    按根数从多到少枚举，长度就是从短到长，第一个能拼成的就是最小答案。
    """
    total = sum(sticks)
    for groups in range(total // sticks[0], 0, -1):
        if total % groups == 0:
            yield total // groups


def best_length(sticks: list[int]) -> int:
    """求原始木棒的最小可能长度；sticks 已降序排列且只含合法长度，空表返回 0。"""
    if not sticks:
        return 0
    total = sum(sticks)
    n = len(sticks)
    used = [False] * n

    def fit(length: int, done: int, current: int, start: int) -> bool:
        """已在目标长度 length 下拼好 done 根，当前这根长 current，从下标 start 继续选。"""
        if done == total // length - 1:  # 只剩最后一根，剩余木棍总长恰好是 length，必然拼成
            return True
        if current == length:            # 这根拼满，换下一根，从最长的一节重新搜
            return fit(length, done + 1, 0, 0)
        failed = 0                       # 本层试过并失败的长度：等长木棍互换后结果完全相同
        for i in range(start, n):
            if used[i] or current + sticks[i] > length or sticks[i] == failed:
                continue
            used[i] = True
            if fit(length, done, current + sticks[i], i + 1):
                return True
            used[i] = False
            failed = sticks[i]
            # 空木棒都放不下它、或它恰好补满这根：再用更短的木棍补同一个空缺只会更没希望
            if current == 0 or current + sticks[i] == length:
                return False
        return False

    for length in candidate_lengths(sticks):
        if fit(length, 0, 0, 0):
            return length
    return total  # 每节各成一根，总是可行，是搜索的保底上界


def solve() -> None:
    """多组数据：每组给出砍断后的各节长度，输出原始木棒的最小可能长度。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    for n in data:  # 每组的第一个数是节数，读到 0 表示输入结束
        if n == 0:
            break
        pieces = [next(data) for _ in range(n)]
        # 先放长的：长木棍落点少，尽早定下来能提前收紧搜索，砍掉更多分支
        sticks = sorted((x for x in pieces if x <= MAX_PIECE), reverse=True)
        out.append(str(best_length(sticks)))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
