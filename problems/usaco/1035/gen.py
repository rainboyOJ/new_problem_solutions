#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(3, 20)

    while True:
        bits = []
        zero_count = 0
        one_count = 0
        for _ in range(n):
            if random.randint(0, 1) == 0:
                bits.append("0")
                zero_count += 1
            else:
                bits.append("1")
                one_count += 1

        if zero_count >= 2 and one_count >= 1:
            break

    print(n)
    print("".join(bits))


if __name__ == "__main__":
    main()
