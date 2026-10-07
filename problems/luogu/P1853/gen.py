#!/usr/bin/env python3
import random


def main():
    random.seed()

    start_capital = random.randint(1000, 20000)
    years = random.randint(1, 5)
    types = random.randint(1, 4)
    print(start_capital, years, types)
    for _ in range(types):
        cost = random.randint(1000, 8000)
        cost = (cost // 1000) * 1000
        if cost == 0:
            cost = 1000
        profit = random.randint(1, cost // 10)
        print(cost, profit)


if __name__ == "__main__":
    main()
