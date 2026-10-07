#!/usr/bin/env python3
import random
import string


CHS = ".,:;!?- "


def main():
    random.seed()
    n = random.randint(5, 25)
    s = []
    for i in range(n):
        if i != 0 and i != n - 1 and random.randint(1, 5) == 1:
            s.append(random.choice(CHS))
        else:
            if random.randint(0, 1):
                s.append(random.choice(string.ascii_lowercase))
            else:
                s.append(random.choice(string.ascii_uppercase))
    print("".join(s))


if __name__ == "__main__":
    main()
