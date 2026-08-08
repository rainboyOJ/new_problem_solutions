#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 80)
    m = random.randint(1, 120)
    print(n, m)
    print(" ".join(str(random.randint(1, 100)) for _ in range(n)))
    has_query = False
    for i in range(m):
        if i == m - 1 and not has_query:
            op = "Q"
        else:
            op = random.choice(["Q", "R"])
        if op == "Q":
            has_query = True
            l = random.randint(1, n)
            r = random.randint(l, n)
            print("Q", l, r)
        else:
            p = random.randint(1, n)
            c = random.randint(1, 100)
            print("R", p, c)


if __name__ == "__main__":
    main()
import random


def main():
    random.seed()
    # TODO: generate input for this problem.


if __name__ == "__main__":
    main()
