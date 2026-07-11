#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 12)

    chars = []
    for _ in range(n):
        chars.append(random.choice("GH"))

    # 题目保证两种品种都出现。
    if "G" not in chars:
        chars[random.randrange(n)] = "G"
    if "H" not in chars:
        chars[random.randrange(n)] = "H"

    e = []
    for i in range(1, n + 1):
        e.append(random.randint(i, n))

    print(n)
    print("".join(chars))
    print(*e)


if __name__ == "__main__":
    main()
