#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 03:32
# update_at: 2026-10-01 03:35

import sys
from functools import cache


def choice_is_ok(choice: int, amount: tuple[tuple[int, ...], ...], need: list[int]) -> bool:
    """方案是否可行：被选饲料对每种维生素的贡献之和都不低于需求量。

    维生素按摄入总量计算，同一饲料的贡献可以累加，所以是逐种求和比较，
    而不是取单份饲料的最大值。
    """
    return all(subset_sum(choice, v, amount) >= need[v] for v in range(len(need)))


@cache
def subset_sum(choice: int, v: int, amount: tuple[tuple[int, ...], ...]) -> int:
    """方案 choice 在维生素 v 上的总含量：拆掉最低位那份饲料后递归累加。

    低位编号是固定的划分依据——每个方案唯一定位到"最低位饲料 + 其余部分"，
    于是 2^G 个方案的总含量只用各算一次，不必对每个方案重新扫全部饲料。
    """
    if choice == 0:
        return 0
    low = choice & -choice                     # 最低位的 1，锁定一份必选饲料
    g = low.bit_length() - 1
    return amount[g][v] + subset_sum(choice ^ low, v, amount)


def best_choice(amount: tuple[tuple[int, ...], ...], need: list[int]) -> int:
    """返回可行方案中饲料份数最少的那个，用位集表示（饲料编号 i 对应第 i-1 位）。

    按份数 k 严格递增扫描：份数更少的方案在更小的 k 上已经全部检查过，
    所以第一个通过可行性检查的方案就是最优解，不需要再比较大小。
    """
    full_choice = (1 << len(amount)) - 1       # 全选必然可行，兼作无解兜底
    return next(
        choice
        for k in range(1, len(amount) + 1)
        for choice in range(1, full_choice + 1)
        if choice.bit_count() == k and choice_is_ok(choice, amount, need)  # 位数 = 饲料份数
    )


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    V = next(data)
    need = [next(data) for _ in range(V)]                          # 每天每种维生素的最小量
    G = next(data)
    # amount[g][v]：第 g+1 号饲料的维生素 v 含量；必须是元组，@cache 的键要可哈希
    amount = tuple(tuple(next(data) for _ in range(V)) for _ in range(G))

    chosen = best_choice(amount, need)
    picks = [g + 1 for g in range(G) if chosen >> g & 1]           # 编号从 1 开始，天然升序
    print(f"{len(picks)} " + " ".join(map(str, picks)))


if __name__ == "__main__":
    solve()
