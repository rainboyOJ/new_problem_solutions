#!/usr/bin/env python3
import random

def main():
    n = random.randint(1, 5)
    print(n)
    a = [random.randint(0, 9) for _ in range(n)]
    print(*a)

if __name__ == "__main__":
    main()
