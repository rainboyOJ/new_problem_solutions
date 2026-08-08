#!/usr/bin/env python3
import random


def gen_valid_case(n: int):
    perm = list(range(1, n + 1))
    random.shuffle(perm)
    want = [[0, 0] for _ in range(n + 1)]

    for i, u in enumerate(perm):
        left_student = perm[(i - 1) % n]
        right_student = perm[(i + 1) % n]
        if random.randint(0, 1) == 0:
            want[u] = [left_student, right_student]
        else:
            want[u] = [right_student, left_student]
    return want


def gen_random_case(n: int):
    want = [[0, 0] for _ in range(n + 1)]
    for i in range(1, n + 1):
        cand = list(range(1, n + 1))
        cand.remove(i)
        a, b = random.sample(cand, 2)
        want[i] = [a, b]
    return want


def main():
    random.seed()
    n = random.randint(3, 8)

    if random.randint(0, 1) == 0:
        want = gen_valid_case(n)
    else:
        want = gen_random_case(n)

    print(n)
    for i in range(1, n + 1):
        print(want[i][0], want[i][1])


if __name__ == "__main__":
    main()
