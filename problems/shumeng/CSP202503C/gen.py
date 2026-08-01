#!/usr/bin/env python3
"""生成模板展开的小规模随机模板。"""

import random


def main():
    random.seed()
    print(8)
    print("1 a hello")
    print("1 b world")
    print("2 c $a $b")
    print("3 c")
    print("1 a hi")
    print("3 c")
    print("1 d good $c")
    print("3 d")


if __name__ == "__main__":
    main()
