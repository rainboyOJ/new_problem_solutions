#!/usr/bin/env python3
import random


def build_queues(n):
    return [[i] for i in range(1, n + 1)]


def main():
    random.seed()
    n = random.randint(1, 8)
    m = random.randint(1, 30)
    lengths = [random.randint(1, 6) for _ in range(n)]

    queues = build_queues(n)
    print(n, m)
    print(*lengths)

    for _ in range(m):
        can_merge = len(queues) >= 2
        split_indices = [idx for idx, q in enumerate(queues) if len(q) >= 2]
        can_split = len(split_indices) > 0

        typ = random.randint(1, 3)
        if typ == 1 and can_merge:
            a = random.randrange(len(queues))
            b = random.randrange(len(queues) - 1)
            if b >= a:
                b += 1
            qa = queues[a]
            qb = queues[b]
            i = qa[-1]
            j = qb[0]
            print(1, i, j)
            queues[a] = qa + qb
            if a < b:
                queues.pop(b)
            else:
                queues.pop(a)
                queues[b] = qa + qb
        elif typ == 2 and can_split:
            idx = random.choice(split_indices)
            q = queues[idx]
            p = random.randint(0, len(q) - 2)
            i = q[p]
            print(2, i)
            left = q[: p + 1]
            right = q[p + 1 :]
            queues[idx] = left
            queues.insert(idx + 1, right)
        else:
            k = random.randint(1, 5)
            s_len = random.randint(k, 10)
            s = "".join(str(random.randint(1, 6)) for _ in range(s_len))
            print(3, s, k)


if __name__ == "__main__":
    main()
