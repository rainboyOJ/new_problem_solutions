#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 18:58
# update_at: 2026-10-07 18:58

import sys

NEG = -10**18  # 不可达状态的生命值，比任何合法生命值都小

# 已释放过魔杖的状态：能量点数 -> 该状态下的最大生命值（0 表示刚释放完）
type State = dict[int, int]


def can_survive(cd: int, hp: int, a: list[int]) -> bool:
    """施法间隔放宽到 cd 时，英雄能否活过第 n 秒。"""
    never = hp          # 从未释放：能量点数恒等于当前秒数 i
    alive: State = {}   # 释放过一次及以上：能量点数 j 即"距上次释放的秒数"
    for i, dmg in enumerate(a, 1):
        nxt: State = {}
        if never > dmg:                       # 受伤后 hp>0 才来得及释放，否则本秒即死
            never -= dmg
            nxt[0] = never + 15 * i           # 首次释放不受间隔限制，回 15*i 点
        else:
            never = NEG                       # 这条链已死亡，之后不再是任何状态的来源
        for energy, h in alive.items():
            if h <= dmg:                      # 受伤瞬间 hp<=0，直接死亡
                continue
            h -= dmg
            energy += 1                       # 本秒又攒一点能量
            nxt[energy] = max(nxt.get(energy, NEG), h)          # 不释放
            if energy >= cd:                  # 距上次释放至少 cd 秒才允许再释放
                nxt[0] = max(nxt.get(0, NEG), h + 15 * energy)
        alive = nxt
        all_dead = never == NEG and not alive   # 两条来源都断了，之后永远不可达
        if all_dead:
            break
    return never > 0 or any(h > 0 for h in alive.values())


def best_cd(hp: int, a: list[int]) -> int | str:
    """最大的可行施法间隔；-1 表示必死，字符串表示没有上界。"""
    if not can_survive(1, hp, a):             # cd=1 最宽松，它都不行就必死
        return -1
    if can_survive(len(a) + 1, hp, a):        # cd>n 时至多释放一次，与 cd 无关
        return "No upper bound."
    lo, hi = 1, len(a)                        # can_survive 关于 cd 单调不增
    while lo < hi:
        mid = (lo + hi + 1) // 2
        if can_survive(mid, hp, a):
            lo = mid
        else:
            hi = mid - 1
    return lo


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, hp = next(data), next(data)
    a = [next(data) for _ in range(n)]

    print(best_cd(hp, a))


if __name__ == "__main__":
    solve()
