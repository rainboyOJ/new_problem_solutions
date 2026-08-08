#!/usr/bin/env python3
import random


def main():
    random.seed()
    print("".join(random.choice("01") for _ in range(8)))


if __name__ == "__main__":
    main()
