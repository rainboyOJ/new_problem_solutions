#!/usr/bin/env python3
import random


def build_flights(m, times):
    flights = []
    pos = 0
    for _ in range(m):
        a = times[pos]
        b = times[pos + 1]
        pos += 2
        if a > b:
            a, b = b, a
        flights.append((a, b))
    return flights


def main():
    random.seed()
    n = random.randint(1, 8)
    m1 = random.randint(1, 8)
    m2 = random.randint(1, 8)
    times = random.sample(range(1, 200), 2 * (m1 + m2))
    domestic = build_flights(m1, times[: 2 * m1])
    international = build_flights(m2, times[2 * m1 :])

    print(n, m1, m2)
    for a, b in domestic:
        print(a, b)
    for a, b in international:
        print(a, b)


if __name__ == "__main__":
    main()
