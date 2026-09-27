#!/usr/bin/env python3
import random


def main():
    random.seed()
    # 小规模随机数据，服务于暴力解和对拍（2^n 枚举）。
    n = random.randint(1, 8)
    d = random.randint(1, 10)
    print(n, d)
    for _ in range(n):
        x = random.randint(-20, 20)
        y = random.randint(0, 12)  # 允许 y > d，用来测试输出 -1 的情况
        print(x, y)


if __name__ == "__main__":
    main()
