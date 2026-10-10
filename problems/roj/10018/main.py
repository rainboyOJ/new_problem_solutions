#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-10 07:12
# update_at: 2026-10-10 07:12

import sys

MAX_COMB = 530


def dfs_state(text: str, filled_count: int, n: int, seen: set[str], states: list[str]) -> None:
    """生成按实力递增填入轮次时可能出现的 LIS 轮廓。"""
    if text in seen:
        return
    seen.add(text)
    states.append(text)
    if filled_count == n:
        return

    for pos, ch in enumerate(text):
        if ch == "0":
            best = max(text[:pos], default="0")
            dfs_state(text[:pos] + chr(ord(best) + 1) + text[pos + 1 :], filled_count + 1, n, seen, states)


def can_still_reach(text: str, n: int, need_lis: int) -> bool:
    """把空位按最优方式补齐后，判断 LIS 轮廓是否可能达到 need_lis。"""
    cur = list(text)
    best = "0"
    for i in range(n):
        if cur[i] == "0":
            cur[i] = chr(ord(best) + 1)
            best = chr(ord(best) + 1)
        else:
            best = max(best, cur[i])
    return max(cur) >= chr(ord("0") + need_lis)


def build_states(n: int, need_lis: int) -> tuple[list[str], list[int], dict[str, int]]:
    """过滤无用轮廓，并建立 1 下标状态表。"""
    raw_states: list[str] = []
    dfs_state("0" * n, 0, n, set(), raw_states)

    state_text = [""]
    state_mask = [0]
    state_id: dict[str, int] = {}
    for text in raw_states:
        if not can_still_reach(text, n, need_lis):
            continue
        state_id[text] = len(state_text)
        state_text.append(text)
        mask = sum(1 << i for i, ch in enumerate(text) if ch != "0")
        state_mask.append(mask)
    return state_text, state_mask, state_id


def build_comb(mod: int) -> tuple[list[int], list[list[int]]]:
    """预处理阶乘与组合数，规模覆盖 2^9 个选手。"""
    fact = [1] * (MAX_COMB + 1)
    for i in range(1, MAX_COMB + 1):
        fact[i] = fact[i - 1] * i % mod

    comb = [[0] * (MAX_COMB + 1) for _ in range(MAX_COMB + 1)]
    comb[0][0] = 1
    for i in range(1, MAX_COMB + 1):
        for j in range(i + 1):
            comb[i][j] = 1 if j == 0 or i == 1 else (comb[i - 1][j] + comb[i - 1][j - 1]) % mod
    return fact, comb


def fill_position(text: str, pos: int) -> str:
    """在 pos 轮填入当前最大买通选手，得到新的 LIS 轮廓。"""
    best = max(text[:pos], default="0")
    return text[:pos] + chr(ord(best) + 1) + text[pos + 1 :]


def count_answers(n: int, m: int, need_lis: int, mod: int, beat: list[int]) -> int:
    """做与官方 std.cpp 等价的轮廓背包 DP。"""
    state_text, state_mask, state_id = build_states(n, need_lis)
    fact, comb = build_comb(mod)

    dp = [[0] * len(state_text) for _ in range(m + 1)]
    dp[0][state_id["0" * n]] = 1

    for i, value in enumerate(beat):
        for sid in range(1, len(state_text)):
            cur = dp[i][sid]
            if cur == 0:
                continue
            dp[i + 1][sid] = (dp[i + 1][sid] + cur) % mod

            text = state_text[sid]
            used_mask = state_mask[sid]
            for pos, ch in enumerate(text):
                subtree_size = 1 << pos
                enough_smaller = value >= used_mask + subtree_size + 1
                if ch == "0" and enough_smaller:
                    next_text = fill_position(text, pos)
                    next_id = state_id.get(next_text, 0)
                    if next_id == 0:
                        continue
                    choose_row = value - used_mask - 2
                    ways = cur * comb[choose_row][subtree_size - 1] % mod * fact[subtree_size] % mod
                    dp[i + 1][next_id] = (dp[i + 1][next_id] + ways) % mod

    full_mask = (1 << n) - 1
    answer = sum(dp[m][sid] for sid in range(1, len(state_text)) if state_mask[sid] == full_mask) % mod
    return answer * pow(2, n, mod) % mod


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    try:
        n = next(data)
    except StopIteration:
        return
    m, need_lis, mod = next(data), next(data), next(data)
    beat = sorted(next(data) for _ in range(m))
    print(count_answers(n, m, need_lis, mod, beat))


if __name__ == "__main__":
    solve()
