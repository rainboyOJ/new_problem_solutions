#!/usr/bin/env python3
# gen.py：为 P10840 生成随机小数据（n 小，便于对拍）。
import random


def main():
    random.seed()
    n = random.randint(1, 12)
    # 值域取小，便于出现"全相同"与"部分相同"两种情况
    vals = [random.randint(1, 3) for _ in range(n)]
    print(n)
    print(*vals)


if __name__ == "__main__":
    main()
