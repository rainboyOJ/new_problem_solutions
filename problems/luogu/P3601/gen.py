#!/usr/bin/env python3
import os
import random


def main():
    random.seed(int(os.environ.get("DUPAI_SEED", "0")))

    left = random.randint(1, 300)
    right = left + random.randint(0, 30)
    print(left, right)


if __name__ == "__main__":
    main()
