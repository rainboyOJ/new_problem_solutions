#!/usr/bin/env python3
import random


def main():
    random.seed()
    # 暴力程序是 O(n) 的，所以随机数据只生成小范围。
    n = random.randint(1, 2000)
    print(n)


if __name__ == "__main__":
    main()
