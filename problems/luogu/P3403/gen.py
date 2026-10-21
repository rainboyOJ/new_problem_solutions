#!/usr/bin/env python3
# 随机生成小数据：h 不太大，保证 brute.cpp 的逐层标记跑得动。
# 三类数据都覆盖：步长全相同、含步长 1、步长互不相同。
import random


def main():
    random.seed()

    mode = random.randint(1, 3)
    if mode == 1:
        # 三个步长全相同：余数图退化成一个点
        v = random.randint(1, 20)
        steps = [v, v, v]
    elif mode == 2:
        # 含步长 1：所有楼层都可达，用来检验计数上界
        steps = [1, random.randint(2, 20), random.randint(2, 30)]
        random.shuffle(steps)
    else:
        steps = [random.randint(1, 25) for _ in range(3)]

    # h 取小一些，让暴力解法能逐层标记
    h = random.randint(1, 2000)

    print(h)
    print(*steps)


if __name__ == "__main__":
    main()
