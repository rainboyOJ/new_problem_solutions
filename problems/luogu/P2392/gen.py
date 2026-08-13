#!/usr/bin/env python3
"""生成 P2392 小数据：4 科，每科题数较小，适合 01 序列暴力对拍。"""
import random

random.seed()


def main():
    sizes = [random.randint(1, 12) for _ in range(4)]
    print(*sizes)
    for size in sizes:
        print(*[random.randint(1, 60) for _ in range(size)])


if __name__ == "__main__":
    main()
