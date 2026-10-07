#!/usr/bin/env python3
import random


def valid_addr():
    a = [str(random.randint(0, 255)) for _ in range(4)]
    e = str(random.randint(0, 65535))
    return ".".join(a) + ":" + e


def invalid_addr():
    mode = random.randint(1, 5)
    if mode == 1:
        return "256.1.1.1:80"
    if mode == 2:
        return "01.1.1.1:80"
    if mode == 3:
        return "1.1.1.1:065"
    if mode == 4:
        return "1.1.1:80"
    return "1.1.1.1.80"


def main():
    random.seed()
    n = random.randint(1, 20)
    pool = []
    print(n)
    for _ in range(n):
        typ = random.choice(["Server", "Client"])
        if pool and random.randint(1, 4) == 1:
            addr = random.choice(pool)
        elif random.randint(1, 5) == 1:
            addr = invalid_addr()
        else:
            addr = valid_addr()
            if random.randint(0, 1):
                pool.append(addr)
        print(typ, addr)


if __name__ == "__main__":
    main()
