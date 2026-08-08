#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 50)
    s = "".join(random.choice("GR") for _ in range(n))
    print(s)


if __name__ == "__main__":
    main()
