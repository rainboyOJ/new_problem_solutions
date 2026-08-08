#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 8)
    print(n)
    for i in range(1, n + 1):
        name = f"stu{i}"
        year = random.randint(1998, 2003)
        month = random.randint(1, 12)
        day = random.randint(1, 28)
        print(name, year, month, day)


if __name__ == "__main__":
    main()
