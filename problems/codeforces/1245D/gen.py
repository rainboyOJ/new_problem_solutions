#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else random.randrange(1 << 30)
    random.seed(seed)

    # 模式覆盖边界：n=1、所有 c 都很小、所有 k 都很大、坐标重复
    mode = random.choice(["tiny", "small_c", "big_k", "dup_pos", "normal"])
    n = 1 if mode == "tiny" else random.randint(1, 8)

    # dup_pos：坐标范围压到 2x2，让重复坐标必然大量出现
    pos_limit = 2 if mode == "dup_pos" else 5
    print(n)
    for _ in range(n):
        print(random.randint(1, pos_limit), random.randint(1, pos_limit))

    # small_c：电站都很便宜；其余模式电站价格正常随机
    c_hi = 3 if mode == "small_c" else 30
    print(*[random.randint(1, c_hi) for _ in range(n)])

    # big_k：拉线都很贵；其余模式拉线系数正常随机
    k_lo, k_hi = (100, 1000) if mode == "big_k" else (1, 10)
    print(*[random.randint(k_lo, k_hi) for _ in range(n)])


if __name__ == "__main__":
    main()
