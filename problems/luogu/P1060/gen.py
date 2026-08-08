#!/usr/bin/env python3
import random


def main():
    random.seed()

    budget = random.randint(1, 40)
    item_count = random.randint(1, 14)
    print(budget, item_count)
    for _ in range(item_count):
        price = random.randint(1, 20)
        importance = random.randint(1, 5)
        print(price, importance)


if __name__ == "__main__":
    main()
