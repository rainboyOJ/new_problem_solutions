#!/usr/bin/env python3
import random


def main():
    random.seed()
    chars = "1234567890QWERTYUIOP[]ASDFGHJKL;'ZXCVBNM,./-="
    n = random.randint(1, 50)
    print("".join(random.choice(chars) for _ in range(n)))


if __name__ == "__main__":
    main()
