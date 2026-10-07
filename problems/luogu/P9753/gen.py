#!/usr/bin/env python3
"""P9753 消消乐随机数据生成器。

默认小字母表、短串，方便 brute.cpp 对拍；用 --alphabet / --max-n 可以放大。
"""
import argparse
import random


def parse_args():
    parser = argparse.ArgumentParser(description="Generate random test data for P9753.")
    parser.add_argument("--max-n", type=int, default=24, help="字符串长度上限")
    parser.add_argument("--alphabet", type=str, default="abc", help="允许出现的字符集合")
    return parser.parse_args()


def main():
    args = parse_args()
    random.seed()

    n = random.randint(1, args.max_n)
    s = "".join(random.choice(args.alphabet) for _ in range(n))
    print(n)
    print(s)


if __name__ == "__main__":
    main()
