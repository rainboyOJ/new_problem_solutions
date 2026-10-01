#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 04:25
# update_at: 2026-10-02 04:25

import sys
from bisect import bisect_right

INF = 10**18          # 还没产生某一侧约束时的区间哨兵
PRICE_CAP = 300000     # 销量归零前的价位枚举上限（题面所有数字 < 100000）


def sales(xs: list[int], ss: list[int], drop: int, price: int) -> tuple[int, int]:
    """价位 price 的销量，返回 (分子, 分母)：已知价位间线性插值，超过最高价位后每涨 1 元减 drop。"""
    i = bisect_right(xs, price) - 1          # price 落在 xs[i] ~ xs[i+1] 的插值段内
    if i + 1 < len(xs):
        p0, p1 = xs[i], xs[i + 1]
        # 段内销量 = ss[i] + (ss[i+1]-ss[i])/(p1-p0) * (price-p0)，先不约分
        return ss[i] * (p1 - p0) + (ss[i + 1] - ss[i]) * (price - p0), p1 - p0
    return ss[i] - drop * (price - xs[i]), 1  # 超出最高价位：按固定数值递减


def ceil_div(a: int, b: int) -> int:
    """向上取整的整数除法，要求 b > 0。"""
    return -((-a) // b)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    target = next(data)                          # 政府预期价
    cost, low_sales = next(data), next(data)     # 成本价、成本价位上的销量

    known: dict[int, int] = {cost: low_sales}    # 已知价位 → 销量，按价位去重
    while True:
        price, count = next(data), next(data)
        if price == -1 and count == -1:
            break
        known[price] = count
    drop = next(data)                            # 超出最高价位后每涨 1 元减少的销量

    xs = sorted(known)                           # 升序价位表，供二分定位插值段
    ss = [known[p] for p in xs]

    if target < cost:              # 预期价低于成本，产品不会在该价位销售
        print("NO SOLUTION")
        return
    target_num, target_den = sales(xs, ss, drop, target)
    if target_num <= 0:            # 预期价位上没有销量，谈不上最大总利润
        print("NO SOLUTION")
        return

    base = target - cost           # 预期价位的不含税单位利润
    lo, hi = -INF, INF             # 补贴额 t 最终落在区间 [lo, hi]

    for price in range(cost, PRICE_CAP + 1):
        num, den = sales(xs, ss, drop, price)
        if num <= 0:               # 销量随价位单调不增，后面价位都没有销量
            break
        gain = price - cost        # 该价位的不含税单位利润
        # 要求 (base+t)·target_num/target_den ⩾ (gain+t)·num/den，
        # 两边乘正数 target_den·den 后是关于 t 的一次不等式：
        target_coef = target_num * den   # 左边 t 的系数
        price_coef = num * target_den    # 右边 t 的系数
        if target_coef == price_coef:
            # 销量相同：不含税单位利润必须不低，否则任何 t 都救不回来
            if gain > base:
                print("NO SOLUTION")
                return
        elif target_coef > price_coef:    # t 有下界
            lo = max(lo, ceil_div(price_coef * gain - target_coef * base,
                                  target_coef - price_coef))
        else:                            # t 有上界
            hi = min(hi, (price_coef * gain - target_coef * base)
                          // (target_coef - price_coef))

    if lo > hi:
        print("NO SOLUTION")
    else:
        # 区间内取绝对值最小：跨 0 取 0，否则取离 0 最近的端点
        print(0 if lo <= 0 <= hi else min((lo, hi), key=abs))


if __name__ == "__main__":
    solve()
