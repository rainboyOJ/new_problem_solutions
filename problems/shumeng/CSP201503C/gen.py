#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    month = random.randint(1, 12)
    kth = random.randint(1, 5)
    weekday = random.randint(1, 7)
    first_year = random.randint(1850, 2040)
    last_year = random.randint(first_year, 2050)
    print(month, kth, weekday, first_year, last_year)


if __name__ == "__main__":
    main()
