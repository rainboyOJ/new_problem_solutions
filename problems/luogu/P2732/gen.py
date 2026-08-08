#!/usr/bin/env python3
import random


def main():
    b = random.randint(1, 5)
    codes = random.sample(range(1, 30), b)
    need = [random.randint(1, 5) for _ in range(b)]
    price = [random.randint(2, 10) for _ in range(b)]

    s = random.randint(0, 8)
    print(s)
    for _ in range(s):
        k = random.randint(1, b)
        idxs = random.sample(range(b), k)
        offer_items = []
        normal_cost = 0
        for idx in idxs:
            cnt = random.randint(1, need[idx])
            offer_items.append((codes[idx], cnt))
            normal_cost += cnt * price[idx]
        offer_price = random.randint(1, max(1, normal_cost))
        print(k, end="")
        for code, cnt in offer_items:
            print(f" {code} {cnt}", end="")
        print(f" {offer_price}")

    print(b)
    for i in range(b):
        print(codes[i], need[i], price[i])


if __name__ == "__main__":
    main()
