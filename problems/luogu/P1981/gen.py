#!/usr/bin/env python3
import random


def main():
    parts = random.randint(1, 40)
    out = []
    for i in range(parts):
        out.append(str(random.randint(0, 100000)))
        if i + 1 < parts:
            out.append(random.choice(["+", "*"]))
    print("".join(out))


if __name__ == "__main__":
    main()
