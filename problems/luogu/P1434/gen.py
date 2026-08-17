#!/usr/bin/env python3
import random


def main():
    # 小数据：格子少、高度范围小，保证暴力枚举所有路线也能快速跑完。
    # 高度范围只有 0..6，最长路线不超过 7 个格子，路径数可控。
    R = random.randint(1, 4)
    C = random.randint(1, 4)
    print(f"{R} {C}")
    for _ in range(R):
        print(" ".join(str(random.randint(0, 6)) for _ in range(C)))


if __name__ == "__main__":
    main()
