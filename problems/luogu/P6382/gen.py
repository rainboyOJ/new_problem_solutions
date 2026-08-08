#!/usr/bin/env python3
import random


def main():
    random.seed()
    prefix = "".join(random.choice("ABCDEFGHIJKLMNOPQRSTUVWXYZ") for _ in range(3))
    body = [random.choice("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") for _ in range(5)]
    if not any(ch.isdigit() for ch in body):
        body[random.randrange(5)] = random.choice("0123456789")
    print(prefix + "".join(body))


if __name__ == "__main__":
    main()
