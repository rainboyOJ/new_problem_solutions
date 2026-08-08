#!/usr/bin/env python3
import random


def main():
    random.seed()
    start = random.randint(-50, 50)
    diff = random.randint(1, 20)
    arr = [start + i * diff for i in range(4)]
    idx = random.randint(0, 3)
    arr.pop(idx)
    random.shuffle(arr)
    print(*arr)


if __name__ == "__main__":
    main()
