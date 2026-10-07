#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 8)
    money = random.randint(1, 20)
    rp = random.randint(1, 20)
    print(n)
    for _ in range(n):
        need_money = random.randint(1, money)
        need_rp = random.randint(1, rp)
        need_time = random.randint(1, 20)
        print(need_money, need_rp, need_time)
    print(money, rp)


if __name__ == "__main__":
    main()
