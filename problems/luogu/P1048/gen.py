#!/usr/bin/env python3
import random


def main():
    random.seed()

    total_time = random.randint(0, 25)
    herb_count = random.randint(0, 14)

    print(total_time, herb_count)
    for _ in range(herb_count):
        t = random.randint(0, 20)
        v = random.randint(0, 30)
        print(t, v)


if __name__ == "__main__":
    main()
