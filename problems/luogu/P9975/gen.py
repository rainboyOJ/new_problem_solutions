#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 10)
    # 题面保证最开始至少有一头奶牛感染，
    # 所以最终状态中至少要出现一个 1。
    while True:
        s = "".join(random.choice("01") for _ in range(n))
        if "1" in s:
            break
    print(n)
    print(s)


if __name__ == "__main__":
    main()
