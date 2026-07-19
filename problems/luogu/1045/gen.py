#!/usr/bin/env python3
import random


def main():
    random.seed()
    # 朴素解是 O(P * 500)，对拍时只生成较小的合法 P。
    p = random.randint(1001, 5000)
    print(p)


if __name__ == "__main__":
    main()
