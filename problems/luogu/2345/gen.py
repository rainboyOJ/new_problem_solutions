#!/usr/bin/env python3
import random

def main():
    random.seed()
    n = random.randint(2, 40)
    xs = random.sample(range(1, 100), n)   # 坐标互不相同
    print(n)
    for x in xs:
        print(random.randint(1, 30), x)

if __name__ == "__main__":
    main()
