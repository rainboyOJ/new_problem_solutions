#!/usr/bin/env python3
import random


def main():
    random.seed()
    l = random.randint(1, 20)
    arr = [random.randint(-10, 10) for _ in range(l)]

    def count_ac(need: int) -> int:
        cur = 0
        cnt = 0
        for x in arr:
            cur += x
            if cur < 0:
                cur = 0
            if cur >= need:
                cnt += 1
                cur = 0
        return cnt

    sum_pos = sum(x for x in arr if x > 0)
    all_k = sorted({count_ac(n) for n in range(1, max(1, sum_pos) + 1) if count_ac(n) > 0})
    if not all_k:
        target_k = 1
    else:
        target_k = random.choice(all_k + [max(all_k) + 1])

    print(l, target_k)
    for x in arr:
        print(x)


if __name__ == "__main__":
    main()
