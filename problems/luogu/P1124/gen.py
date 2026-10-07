#!/usr/bin/env python3
import random


def encode(s: str):
    n = len(s)
    rot = []
    for i in range(n):
        rot.append((s[i:] + s[:i], i + 1))
    rot.sort(key=lambda x: (x[0][0], x[1]))
    last = "".join(x[0][-1] for x in rot)
    target = 1 if n == 1 else 2
    pos = next(i + 1 for i, x in enumerate(rot) if x[1] == target)
    return last, pos


def main():
    random.seed()
    n = random.randint(1, 8)
    s = "".join(random.choice("abcde") for _ in range(n))
    last, pos = encode(s)
    print(n)
    print(last)
    print(pos)


if __name__ == "__main__":
    main()
