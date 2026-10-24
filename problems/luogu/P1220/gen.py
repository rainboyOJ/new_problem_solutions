#!/usr/bin/env python3
"""P1220 对拍数据生成器：n in [1,8]，覆盖单灯、相邻/同坐标、极端功率。"""
import random
import sys


def main():
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else random.randrange(10**9)
    rng = random.Random(seed)
    n = rng.randint(1, 8)
    c = rng.randint(1, n)
    # 随机生成 n 个 1..100 内的可重位置，排序后输出（题面保证位置单调递增）
    pos = sorted(rng.randint(1, 100) for _ in range(n))
    ws = [rng.choice([1, 1, rng.randint(1, 100), 100, rng.randint(90, 100)])
          for _ in range(n)]
    print(n, c)
    for p, w in zip(pos, ws):
        print(p, w)


if __name__ == "__main__":
    main()
