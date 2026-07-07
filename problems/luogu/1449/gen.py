#!/usr/bin/env python3
import random


def build(depth):
    if depth == 0 or random.random() < 0.35:
        return str(random.randint(1, 20)) + "."
    left = build(depth - 1)
    right = build(depth - 1)
    op = random.choice(["+", "-", "*", "/"])
    if op == "/":
        right = str(random.randint(1, 9)) + "."
    return left + right + op


def main():
    random.seed()
    print(build(3) + "@")


if __name__ == "__main__":
    main()
