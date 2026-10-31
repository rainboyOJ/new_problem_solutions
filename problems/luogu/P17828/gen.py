#!/usr/bin/env python3
"""对拍数据生成器：行程编码的字符串，段数少、总长短，便于暴力展开。"""
import sys

from cyaron import randint

ALPHABET = "abc"


def seg(n, hi, alpha):
    """随机生成 n 段，每段长度 1..hi，字符取自 alpha（允许相邻段同字符）。"""
    parts = []
    for _ in range(n):
        parts.append(f"{randint(1, hi)} {alpha[randint(0, len(alpha) - 1)]}")
    return parts


def main():
    mode = sys.argv[1] if len(sys.argv) > 1 else "rand"
    if mode == "min":                 # 最小规模：一段一个字符
        print(1)
        print("1 a")
        return
    if mode == "two":                 # 两段，检查段数很小时的边界
        print(2)
        for line in seg(2, 5, ALPHABET):
            print(line)
        return
    if mode == "same":                # 整个串只有一个字符，答案必为 0
        n = randint(1, 50)
        print(n)
        for _ in range(n):
            print(randint(1, 50), "a")
        return
    if mode == "big":                 # 上界量级的长度，检验 long long 与不展开
        n = randint(1, 200)
        print(n)
        for _ in range(n):
            print(randint(1, 10 ** 9), ALPHABET[randint(0, 2)])
        return
    n = randint(1, 60)
    print(n)
    for line in seg(n, randint(1, 6), ALPHABET):
        print(line)


if __name__ == "__main__":
    main()
