#!/usr/bin/env python3
import random


def main():
    random.seed()
    words = [
        "bessie", "elsie", "john", "nhoj", "moo", "cow", "bella", "grass",
        "runs", "jumps", "sees", "likes", "and", "but", "or", "then",
    ]
    types = ["noun", "transitive-verb", "intransitive-verb", "conjunction"]

    tests = random.randint(1, 5)
    print(tests)
    for case in range(tests):
        n = random.randint(1, 12)
        c = random.randint(1, n)
        p = random.randint(1, n)
        print(n, c, p)
        for i in range(n):
            word = words[(case * 17 + i * 5 + random.randint(0, 15)) % len(words)] + str(case) + "_" + str(i)
            tp = random.choice(types)
            print(word, tp)


if __name__ == "__main__":
    main()
