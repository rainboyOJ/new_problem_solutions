#!/usr/bin/env python3
import random


def rand_string(length):
    return "".join(random.choice("abc") for _ in range(length))


def main():
    random.seed()
    n = random.randint(1, 30)
    q = random.randint(1, 40)

    pairs = []
    print(n, q)
    for _ in range(n):
        length = random.randint(1, 6)
        a = rand_string(length)
        b = rand_string(length)
        pairs.append((a, b))
        print(a, b)

    for _ in range(q):
        if random.randint(1, 3) == 1:
            base_len = random.randint(1, 8)
            base = rand_string(base_len)
            p, r = random.choice(pairs)
            if len(p) <= base_len:
                start = random.randint(0, base_len - len(p))
                a = base[:start] + p + base[start + len(p):]
                b = base[:start] + r + base[start + len(p):]
                if a != b:
                    print(a, b)
                    continue

        len_a = random.randint(1, 8)
        len_b = len_a if random.randint(1, 5) != 1 else random.randint(1, 8)
        a = rand_string(len_a)
        b = rand_string(len_b)
        if a == b:
            pos = random.randint(0, len_b - 1)
            ch = random.choice("abc")
            while ch == b[pos]:
                ch = random.choice("abc")
            b = b[:pos] + ch + b[pos + 1:]
        print(a, b)


if __name__ == "__main__":
    main()
