#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 11:47
# update_at: 2026-10-02 11:47

import sys
from collections.abc import Iterator
from functools import cache

# counts 共 15 个槽位：0..11 是顺子序（3..10、J、Q、K、A），12 是点数 2，13/14 是小王/大王。
# 2 和双王不能进顺子，所以顺子枚举只走前 12 个槽位。
SPLITS = (
    ((1, 0, 0, 0),),                                    # 1 张：单张
    ((0, 1, 0, 0), (2, 0, 0, 0)),                       # 2 张：对子 / 拆成两单
    ((0, 0, 1, 0), (1, 1, 0, 0), (3, 0, 0, 0)),         # 3 张：三张 / 对+单 / 三单
    ((0, 0, 0, 1), (1, 0, 1, 0), (0, 2, 0, 0),          # 4 张：炸弹 / 三+单 /
    (2, 1, 0, 0), (4, 0, 0, 0)),                        #       两对 / 对+两单 / 四单
)  # 一个点数拆成基础组的全部方式，每项是 (单张数, 对子数, 三张数, 炸弹数)


def slot_of(value: int, suit: int) -> int:
    """把输入的一张牌（点数, 花色）映射到 counts 槽位。"""
    if value == 0:                       # 小王 01、大王 02
        return 12 + suit
    if value == 2:                       # 点数 2 单独存放，永远进不了顺子
        return 12
    return 11 if value == 1 else value - 3  # A 的点数是 1，但顺子序里排在 K 之后


def absorb(single: int, pair: int, triple: int, bomb: int) -> int:
    """散牌最少出法：每手牌 = 一个基础组，三张带一单或一对、炸弹带两单或两对能带就带。"""
    bare = single + pair + triple + bomb
    best = bare
    for take_s in range(min(triple, single) + 1):            # 带单的三张个数
        for take_p in range(min(triple - take_s, pair) + 1):  # 带对的三张个数
            free_s, free_p = single - take_s, pair - take_p
            # 每个炸弹整手带走 2 个散组：两单或两对，两类凑够就能一次带满
            carried = 2 * min(bomb, free_s // 2 + free_p // 2)
            best = min(best, bare - take_s - take_p - carried)
    return best


@cache
def min_plain(c1: int, c2: int, c3: int, c4: int, jokers: int) -> int:
    """不打任何顺子类时打光这些牌的最少次数，答案只取决于各类点数的个数（直方图）。

    c_k = 恰好 k 张的点数个数（不含双王），jokers = 王数（0/1/2）。
    每个点数先拆成基础组，再让三张/炸弹顺带走散组，取所有拆法里的最小值。
    """
    states = {(0, 0, 0, 0)}
    for size, num in ((1, c1), (2, c2), (3, c3), (4, c4)):
        for _ in range(num):
            states = {
                (s + ds, p + dp, t + dt, b + db)
                for s, p, t, b in states
                for ds, dp, dt, db in SPLITS[size - 1]
            }
    plain = min(absorb(s + jokers, p, t, b) for s, p, t, b in states)
    if jokers == 2:  # 双王也可以合火箭：一手打完，比两张单各出一次少一手
        plain = min(plain, min(absorb(s, p, t, b) for s, p, t, b in states) + 1)
    return plain


def plain_of(cnt: tuple[int, ...]) -> int:
    """当前 counts 里非顺子部分（散牌）的最少出牌次数。"""
    hist = [0, 0, 0, 0]
    for k in cnt[:13]:           # 13 个普通点数（含点数 2），双王单独算
        if k:
            hist[k - 1] += 1
    return min_plain(hist[0], hist[1], hist[2], hist[3], cnt[13] + cnt[14])


def cuts(cnt: tuple[int, ...], start: int) -> Iterator[tuple[int, ...]]:
    """枚举从 start 起头的全部顺子类出法（单顺≥5、双顺≥3 对、三顺≥2 三），产出出完后的 counts。"""
    for need, min_len in ((1, 5), (2, 3), (3, 2)):
        for length in range(min_len, 13 - start):
            if any(cnt[start + k] < need for k in range(length)):
                break  # 更短的都凑不齐，更长的必然也不行
            nxt = list(cnt)
            for k in range(length):
                nxt[start + k] -= need
            yield tuple(nxt)


def min_rounds(cards: list[int]) -> int:
    """搜索顺子类牌型的所有组合，非顺子部分用 min_plain 精确结算，返回最少出牌次数。"""
    start = tuple(cards)
    best = [plain_of(start)]  # 一手顺子都不打也是一个可行解
    seen: dict[tuple[int, tuple[int, ...]], int] = {}

    def dfs(i: int, steps: int, cnt: tuple[int, ...]) -> None:
        value = steps + plain_of(cnt)  # 每个中间局面都可达，随手收紧上界
        if value < best[0]:
            best[0] = value
        if i == 12 or steps + 1 >= best[0]:
            return  # 顺子槽位走完；或再出一手也追不上当前最优
        key = (i, cnt)
        if key in seen and seen[key] <= steps:
            return  # 同一局面已经用更少的次数到过，继续只会更差
        seen[key] = steps

        if cnt[i] == 0:
            dfs(i + 1, steps, cnt)
            return
        # 先试出得最多的顺子，让上界尽快收紧；sum 越小说明这一手拿走的牌越多
        for nxt in sorted(cuts(cnt, i), key=sum):
            dfs(i, steps + 1, nxt)
        dfs(i + 1, steps, cnt)  # 这个点数不参与任何顺子，留作散牌

    dfs(0, 0, start)
    return best[0]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)
    n = next(data)
    for _ in range(T):
        cards = [0] * 15
        for _ in range(n):
            value, suit = next(data), next(data)
            cards[slot_of(value, suit)] += 1
        out.append(str(min_rounds(cards)))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
