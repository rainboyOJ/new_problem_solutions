#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 12)
    money = random.randint(0, 20)
    time = random.randint(0, 20)

    print(n, money, time)
    for _ in range(n):
        need_money = random.randint(0, 10)
        need_time = random.randint(0, 10)
        print(need_money, need_time)


if __name__ == "__main__":
    main()
