#!/usr/bin/env python3
import random
import string


CHARS = string.ascii_lowercase[:6]


def main():
    random.seed()
    total_s = random.randint(1, 25)
    total_t = random.randint(1, 25)
    n = random.randint(1, 8)
    m = random.randint(1, 8)
    if (n + m) % 2 == 1:
        m += 1
    s_list = ["".join(random.choice(CHARS) for _ in range(n)) for _ in range(total_s)]
    t_list = ["".join(random.choice(CHARS) for _ in range(m)) for _ in range(total_t)]
    print(total_s, total_t, n, m)
    for s in s_list:
        print(s)
    for t in t_list:
        print(t)


if __name__ == "__main__":
    main()
