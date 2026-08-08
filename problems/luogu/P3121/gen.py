#!/usr/bin/env python3
import random


def main():
    random.seed()
    alphabet = "abcd"
    n = random.randint(1, 8)
    word_len = random.randint(2, 4)
    words = set()
    while len(words) < n:
        text = "".join(random.choice(alphabet) for _ in range(word_len))
        words.add(text)

    words = list(words)
    parts = []
    total_len = random.randint(20, 80)
    while len("".join(parts)) < total_len:
        if random.randint(0, 99) < 35:
            parts.append(random.choice(words))
        else:
            length = random.randint(1, 5)
            parts.append("".join(random.choice(alphabet) for _ in range(length)))

    s = "".join(parts)
    if len(s) == 0:
        s = "a"

    print(s)
    print(n)
    for word in words:
        print(word)


if __name__ == "__main__":
    main()
