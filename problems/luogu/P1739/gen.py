#!/usr/bin/env python3
import random


def main():
    random.seed()
    chars = ["a", "b", "+", "-", "*", "/", "(", ")"]
    n = random.randint(1, 80)
    print("".join(random.choice(chars) for _ in range(n)) + "@")


if __name__ == "__main__":
    main()
