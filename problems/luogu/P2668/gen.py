#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = 1
    n = random.randint(1, 10)
    print(t, n)
    cards = []
    for a in range(3, 14):
        for b in range(1, 5):
            cards.append((a, b))
    for b in range(1, 5):
        cards.append((1, b))
        cards.append((2, b))
    cards.append((0, 1))
    cards.append((0, 2))

    random.shuffle(cards)
    for i in range(n):
        print(cards[i][0], cards[i][1])


if __name__ == "__main__":
    main()
