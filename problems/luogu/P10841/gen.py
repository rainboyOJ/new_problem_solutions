#!/usr/bin/env python3
# gen.py：为 P10841 生成随机小数据（n 小，便于 01 序列暴力对拍）。
import random


def main():
    random.seed()
    T = random.randint(1, 5)
    print(T)
    for _ in range(T):
        n = random.randint(1, 9)
        print(n)
        print(''.join(random.choice('abc') for _ in range(n)))


if __name__ == "__main__":
    main()
