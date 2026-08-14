#!/usr/bin/env python3
# gen.py：为 P10843 生成随机小排列（n 小，便于 BFS 对拍）。
import random


def main():
    random.seed()
    T = random.randint(1, 3)
    print(T)
    for _ in range(T):
        n = random.randint(2, 6)
        perm = list(range(n))
        random.shuffle(perm)
        print(n)
        print(*perm)


if __name__ == "__main__":
    main()
