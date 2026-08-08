#!/usr/bin/env python3
import random


def main():
    random.seed()
    length = random.randint(0, 100)
    steps = "".join(str(random.randint(1, 4)) for _ in range(length))
    print(steps if steps else "1")
    for _ in range(6):
        for _ in range(3):
            print("".join(str(random.randint(1, 3)) for _ in range(3)))


if __name__ == "__main__":
    main()
