#!/usr/bin/env python3
"""友好城市的小数据生成器：两岸坐标互不相同，配对是一一对应。"""

import random


def main():
    random.seed()
    n = random.randint(1, 10)
    # 两岸的城市坐标都互不相同，配对方式随机打乱。
    south = random.sample(range(0, 21), n)
    north = random.sample(range(0, 21), n)
    random.shuffle(north)

    print(n)
    for i in range(n):
        print(south[i], north[i])


if __name__ == "__main__":
    main()
