#!/usr/bin/env python3
import random


def main():
    # 覆盖两个阈值附近的边界。
    values = [1, 22360, 22361, 500000000, 500000001, 10**18]
    print(random.choice(values))


if __name__ == "__main__":
    main()
