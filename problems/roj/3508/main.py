#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 04:18
# update_at: 2026-10-02 04:18

import sys

# 判定精度的绝对/相对容差：|f| <= tol 视为零点附近
TOL = 1e-6


def eval_poly(c: list[float], x: float) -> float:
    """秦九韶算法求三次多项式 c[0]*x^3+c[1]*x^2+c[2]*x+c[3] 在 x 处的值。"""
    y = 0.0
    for coef in c:
        y = y * x + coef
    return y


def bisect(c: list[float], lo: float, hi: float) -> float:
    """已知 f(lo)*f(hi)<0，对 [lo,hi] 二分 80 次得到足够精确的根。"""
    flo = eval_poly(c, lo)
    for _ in range(80):
        mid = (lo + hi) / 2
        if eval_poly(c, mid) * flo < 0:
            hi = mid
        else:
            lo = mid
    return (lo + hi) / 2


def shrink(c: list[float], x: float) -> float:
    """重根收缩：重根处 f 不变号，二分失效；
    但重根必是导数的零点（驻点），取离 x 最近的驻点候选并验证。"""
    # 采样零点/二分结果本身已足够精确，直接采用
    if abs(eval_poly(c, x)) <= TOL:
        return x
    # 解 f'(x)=3c0x^2+2c1x+c2=0 的两个驻点，取离 x 最近者为重根候选
    c0, c1, c2 = c
    a, b, cc = 3 * c0, 2 * c1, c2
    disc = b * b - 4 * a * cc
    if disc < 0:
        return x
    r = disc**0.5
    cand = min(((-b + r) / (2 * a), (-b - r) / (2 * a)), key=lambda t: abs(t - x))
    # 候选处 |f| 足够小才采纳，防止把普通驻点误认为根
    return cand if abs(eval_poly(c, cand)) <= TOL else x


def roots(c: list[float]) -> list[float]:
    """在 [-100,100] 上从小到大找出全部实根（含重根），间隔 >= 1。"""
    step = 0.5
    xs = [-100.0 + i * step for i in range(401)]  # 401 个采样点
    vals = [eval_poly(c, x) for x in xs]
    ans: list[float] = []
    last = None  # 上一个已输出的根，用于去重重根
    # 逐区间检查变号：f 符号翻转 => 区间内恰有一根（间隔>=1保证唯一）
    for i in range(400):
        if vals[i] == 0.0:
            r = xs[i]
        elif vals[i] * vals[i + 1] < 0:
            r = bisect(c, xs[i], xs[i + 1])
        else:
            continue
        r = shrink(c, r)  # 端点根可能是重根，收缩到真正的重根位置
        if last is None or abs(r - last) >= 0.5:
            ans.append(r)
            last = r
    return ans


def solve() -> None:
    a, b, c, d = map(float, sys.stdin.buffer.read().split())
    print(" ".join(f"{r:.2f}" for r in roots([a, b, c, d])))


if __name__ == "__main__":
    solve()
