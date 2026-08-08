#!/usr/bin/env python3
import random
import string


def rand_name(length=5):
    chars = string.ascii_letters
    return "".join(random.choice(chars) for _ in range(length))


def main():
    random.seed()
    n = random.randint(1, 80)
    names = []
    used = set()
    while len(names) < n:
        s = rand_name(random.randint(1, 5))
        if s not in used:
            used.add(s)
            names.append(s)
    shuffled = names[:]
    random.shuffle(shuffled)
    print(n)
    print(*names)
    print(*shuffled)


if __name__ == "__main__":
    main()
