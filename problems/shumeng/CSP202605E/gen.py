#!/usr/bin/env python3
import random


def main():
    random.seed()
    # brute.cpp 枚举完整聚拢状态，生成规模必须保持很小。
    n = random.randint(2, 7)
    print(n)
    for vertex in range(2, n + 1):
        print(random.randint(1, vertex - 1), vertex)


if __name__ == "__main__":
    main()
