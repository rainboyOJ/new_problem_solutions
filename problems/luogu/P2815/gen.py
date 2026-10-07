#!/usr/bin/env python3
import random


def main():
    random.seed()
    parts = []
    for _ in range(8):
        x = random.randint(0, 0xFFFF)
        parts.append(f"{x:04x}")
    print(":".join(parts))


if __name__ == "__main__":
    main()
