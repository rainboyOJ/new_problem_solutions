#!/usr/bin/env python3
"""生成 P1558 小数据：L 格色板，T 种颜色，O 个涂色 / 查询操作，规模适合暴力对拍。

注意 a、b 不保证有序，随机生成时保留无序情况，用来测试交换逻辑。
"""
import random

random.seed()


def main():
    L = random.randint(1, 30)
    T = random.randint(1, 30)
    O = random.randint(1, 100)
    print(L, T, O)
    for _ in range(O):
        if random.random() < 0.5:
            # 涂色操作：C a b c
            a = random.randint(1, L)
            b = random.randint(1, L)
            c = random.randint(1, T)
            print("C", a, b, c)
        else:
            # 查询操作：P a b
            a = random.randint(1, L)
            b = random.randint(1, L)
            print("P", a, b)


if __name__ == "__main__":
    main()
