#!/usr/bin/env python3
"""gen.py：矩形加点求和的小数据生成器（对拍用，格式与 main.cpp / brute.cpp 一致）。

坐标压到 0..COORD，并把大量询问/矩形端点放在同一批坐标上，
专门制造「点正好落在矩形右/上边界」和「多个矩形共边」的情况，
用来检验半开区间 [l,r) x [d,u) 与二维差分的符号有没有写反。
n、q 都控制在暴力 O(q*n) 能瞬间跑完的规模。
"""

import random
import sys

COORD = 6  # 坐标上界，小到暴力能瞬间跑完


def main() -> None:
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else 0
    rng = random.Random(seed)

    n = rng.randint(1, 6)
    q = rng.randint(1, 8)

    out = [f"{n} {q}"]
    for _ in range(n):
        x1 = rng.randint(0, COORD)
        x2 = rng.randint(x1 + 1, COORD + 1)
        y1 = rng.randint(0, COORD)
        y2 = rng.randint(y1 + 1, COORD + 1)
        w = rng.choice((0, 1, 2, 5, 100))  # 含 w = 0，验证零权值不影响结果
        out.append(f"{x1} {y1} {x2} {y2} {w}")

    for _ in range(q):
        if rng.random() < 0.5:
            x1 = rng.randint(0, COORD)
            x2 = rng.randint(x1 + 1, COORD + 1)
            y1 = rng.randint(0, COORD)
            y2 = rng.randint(y1 + 1, COORD + 1)
            w = rng.choice((0, 1, 3, 7, 1000))
            out.append(f"0 {x1} {y1} {x2} {y2} {w}")
        else:
            # 一半概率取小坐标，命中大量边界
            x = rng.randint(0, COORD + 1)
            y = rng.randint(0, COORD + 1)
            out.append(f"1 {x} {y}")

    print("\n".join(out))


if __name__ == "__main__":
    main()
