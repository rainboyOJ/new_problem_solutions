#!/usr/bin/env python3
"""生成 P1019 小数据：n <= 6 个短单词 + 起始字母，规模适合暴力对拍。"""
import random

random.seed()


def rand_word():
    length = random.randint(1, 4)
    alpha = "ab"
    return "".join(random.choice(alpha) for _ in range(length))


def main():
    n = random.randint(2, 6)
    print(n)
    for _ in range(n):
        print(rand_word())
    print(random.choice("ab"))


if __name__ == "__main__":
    main()
