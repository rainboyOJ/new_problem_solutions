#!/usr/bin/env python3
"""P9720 随机数据生成器。

要点：
- 公园 P 用矩形表示，地图 M 是 P 的相似矩形（相似比 q = 公园 : 地图 为正整数）且完全在 P 内。
- 直接按“整数相似变换 + 平移”构造 M：M_i = O + T(P_i)/q，
  其中 T 取 8 个二面体变换之一（含旋转与翻转，对应题面说的“地图可以倒放”）。
- 为能对拍 brute（指数枚举），n 取得较小（0..6）。
- 覆盖边界：k=0 / k 很大、n=0、地图与公园等大、地图贴边、s/t 取在角或边上，
  以及把整体做整数相似旋转（[[15,-20],[20,15]]）得到的倾斜公园。
"""
import random
import sys

# 8 个二面体变换，每个为 (a, b, c, d)，表示 (x, y) -> (a*x + b*y, c*x + d*y)。
# 全部是正交整数矩阵，|det| = 1，保持形状与对应关系。
DIHEDRAL = [
    (1, 0, 0, 1),
    (0, -1, 1, 0),
    (-1, 0, 0, -1),
    (0, 1, -1, 0),
    (1, 0, 0, -1),
    (0, 1, 1, 0),
    (-1, 0, 0, 1),
    (0, -1, -1, 0),
]


def apply_T(t, p):
    a, b, c, d = t
    x, y = p
    return (a * x + b * y, c * x + d * y)


def build_case(rng, mode):
    """返回 (P, M, s, t, k, n)，均为整数点。"""
    q = rng.choice([1, 1, 2, 3, 4])           # 相似比 公园 : 地图
    w0 = rng.randint(1, 3)
    h0 = rng.randint(1, 3)
    W = w0 * q                                 # 均为 q 的倍数，保证除以 q 为整数
    H = h0 * q

    # 公园四个角（逆时针）
    P = [(0, 0), (0, H), (W, H), (W, 0)]
    if mode == "equal":
        q = 1
        W, H = w0, h0
        P = [(0, 0), (0, H), (W, H), (W, 0)]

    # 只有能把地图放进公园的朝向才可用：q>1 时必可行，q=1 且公园非正方形时
    # 90 度旋转会放不下，需要先筛掉。
    cands = DIHEDRAL[:]
    rng.shuffle(cands)
    chosen = None
    for t in cands:
        raw = [apply_T(t, p) for p in P]
        M0 = [(rx // q, ry // q) for (rx, ry) in raw]
        xs = [p[0] for p in M0]
        ys = [p[1] for p in M0]
        if (max(xs) - min(xs) <= W) and (max(ys) - min(ys) <= H):
            chosen = (t, M0, xs, ys)
            break
    assert chosen is not None, "没有可放下的朝向"
    t, M0, xs, ys = chosen

    # 选整数 offset，使地图落在公园内（含贴边）
    ox_lo = -min(xs)
    ox_hi = W - max(xs)
    oy_lo = -min(ys)
    oy_hi = H - max(ys)
    assert ox_lo <= ox_hi and oy_lo <= oy_hi, "地图放不进公园"
    ox = rng.randint(ox_lo, ox_hi)
    oy = rng.randint(oy_lo, oy_hi)

    M = [(x + ox, y + oy) for (x, y) in M0]

    # 随机反转遍历方向（仍满足第 i 个角一一对应，只是顺序反过来）
    if rng.random() < 0.5:
        M = M[::-1]

    def rand_pt():
        return (rng.randint(0, W), rng.randint(0, H))

    # 有一定概率把 s / t 放到角上，制造边界情形
    s = rng.choice(P) if rng.random() < 0.3 else rand_pt()
    t2 = rng.choice(P) if rng.random() < 0.3 else rand_pt()

    k = rng.choice([0, 0, 1, 2, 5, 10, 1000000])
    n = rng.randint(0, 6)

    # pyth 模式：整体乘 5 再旋转 [[3,-4],[4,3]]，得到倾斜公园，坐标仍是整数。
    if mode == "pyth":
        def tilt(p):
            x, y = p
            return (15 * x - 20 * y, 20 * x + 15 * y)
        P = [tilt(p) for p in P]
        M = [tilt(p) for p in M]
        s = tilt(s)
        t2 = tilt(t2)

    return P, M, s, t2, k, n


def validate(P, M, s, t):
    """校验：M 是 P 的相似矩形、相似比 >= 1、完全在 P 内，且 s/t 在 P 内。"""
    def sub(u, v):
        return (u[0] - v[0], u[1] - v[1])

    def norm2(u):
        return u[0] * u[0] + u[1] * u[1]

    def inside(pt, rect):
        o = rect[0]
        e1 = sub(rect[3], o)
        e2 = sub(rect[1], o)
        d = sub(pt, o)
        c1 = (d[0] * e1[0] + d[1] * e1[1]) / norm2(e1)
        c2 = (d[0] * e2[0] + d[1] * e2[1]) / norm2(e2)
        eps = 1e-9
        return -eps <= c1 <= 1 + eps and -eps <= c2 <= 1 + eps

    # 相似性：四组对应边长之比一致，取比值 >= 1
    sq_ratios = []
    for i in range(4):
        j = (i + 1) % 4
        sq_ratios.append(norm2(sub(P[i], P[j])) / norm2(sub(M[i], M[j])))
    assert max(sq_ratios) - min(sq_ratios) < 1e-7, "地图与公园不相似"
    assert min(sq_ratios) >= 1 - 1e-9, "地图比公园大"
    for p in M:
        assert inside(p, P), "地图角点不在公园内"
    assert inside(s, P) and inside(t, P), "s/t 不在公园内"


def main():
    random.seed(20221002)  # 固定种子，保证可复现
    T = random.randint(1, 4)
    cases = []
    for _ in range(T):
        r = random.random()
        if r < 0.15:
            mode = "equal"
        elif r < 0.4:
            mode = "pyth"
        else:
            mode = "axis"
        P, M, s, t, k, n = build_case(random, mode)
        validate(P, M, s, t)
        cases.append((P, M, s, t, k, n))

    out = [str(len(cases))]
    for (P, M, s, t, k, n) in cases:
        out.append(" ".join("%d %d" % (p[0], p[1]) for p in P))
        out.append(" ".join("%d %d" % (p[0], p[1]) for p in M))
        out.append("%d %d %d %d" % (s[0], s[1], t[0], t[1]))
        out.append("%d %d" % (k, n))
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
