#!/usr/bin/env python3
# P1637 小数据随机生成器：n 随机、值域随机且可能重复，
# 供 O(n^3) 暴力对拍使用（n 最大 60，暴力 60^3 = 21.6 万次判断）。
import random


def main():
    random.seed()
    n = random.randint(1, 60)
    values = [random.randint(1, 40) for _ in range(n)]
    print(n)
    print(" ".join(map(str, values)))


if __name__ == "__main__":
    main()
