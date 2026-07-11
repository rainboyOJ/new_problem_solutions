#!/usr/bin/env python3
import random

ANIMALS = [
    "Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse",
    "Goat", "Monkey", "Rooster", "Dog", "Pig", "Rat",
]


def main():
    random.seed()
    n = random.randint(1, 10)
    known = ["Bessie"]
    lines = []

    for i in range(1, n + 1):
        if i == n:
            cow_a = "Elsie"
        else:
            cow_a = "Cow" + str(i)

        relation = random.choice(["previous", "next"])
        animal = random.choice(ANIMALS)
        cow_b = random.choice(known)
        known.append(cow_a)

        lines.append(f"{cow_a} born in {relation} {animal} year from {cow_b}")

    print(n)
    for line in lines:
        print(line)


if __name__ == "__main__":
    main()
