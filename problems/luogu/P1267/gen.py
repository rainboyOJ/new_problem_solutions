#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 3)
    tot = 4 * n * n
    nums = list(range(1, tot + 1))
    random.shuffle(nums)

    print(n)
    pos = 0
    for _ in range(4):
        face = []
        for row in range(1, n + 1):
            for _ in range(2 * row - 1):
                face.append(str(nums[pos]))
                pos += 1
        print(" ".join(face))


if __name__ == "__main__":
    main()
