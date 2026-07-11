#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 20)
    print(n)
    for _ in range(n):
        width = random.randint(1, 25)
        height = random.randint(1, 25)

        # 两种方向的矩形围栏，都是合法闭合且不自交的路径。
        if random.randint(0, 1) == 0:
            s = "N" * height + "E" * width + "S" * height + "W" * width
        else:
            s = "E" * width + "N" * height + "W" * width + "S" * height
        print(s)


if __name__ == "__main__":
    main()
