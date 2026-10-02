#!/usr/bin/env python3
"""P5658 随机数据生成器。

默认生成混合数据：一半概率是链（f_u = u - 1），一半是随机树，
这样对拍同时覆盖链上的特殊性质档和一般树。
"""
import argparse
import random


def parse_args():
    parser = argparse.ArgumentParser(description="Generate random test data for P5658.")
    parser.add_argument("--max-n", type=int, default=20, help="最大结点数，暴力解只适合小数据")
    parser.add_argument(
        "--mode",
        choices=["mixed", "chain", "tree"],
        default="mixed",
        help="mixed：一半链一半随机树；chain：只生成链；tree：只生成随机树",
    )
    return parser.parse_args()


def main():
    args = parse_args()
    random.seed()

    n = random.randint(1, args.max_n)
    s = "".join(random.choice("()") for _ in range(n))
    print(n)
    print(s)

    if n >= 2:
        if args.mode == "chain" or (args.mode == "mixed" and random.random() < 0.5):
            parents = [i - 1 for i in range(2, n + 1)]
        else:
            parents = [random.randint(1, i - 1) for i in range(2, n + 1)]
        print(" ".join(str(x) for x in parents))


if __name__ == "__main__":
    main()
