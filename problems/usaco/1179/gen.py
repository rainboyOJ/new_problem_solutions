#!/usr/bin/env python3
import random


def main():
    random.seed()
    letters = "ABCD"
    for _ in range(6):
        row = []
        for _ in range(3):
            row.append(random.choice(letters))
        print("".join(row))


if __name__ == "__main__":
    main()
