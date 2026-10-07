#!/usr/bin/env python3
import random


def main():
    random.seed()

    weights = [1, 2, 3, 5, 10, 20]
    remain = 80
    answer = []
    for w in weights:
        max_cnt = remain // w
        c = random.randint(0, max_cnt)
        answer.append(c)
        remain -= c * w
    print(*answer)


if __name__ == "__main__":
    main()
