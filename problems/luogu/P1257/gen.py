#!/usr/bin/env python3
import random

def main():
    random.seed()
    n = random.randint(2, 200)
    print(n)
    for _ in range(n):
        print(random.randint(0, 10000), random.randint(0, 10000))

if __name__ == "__main__":
    main()
