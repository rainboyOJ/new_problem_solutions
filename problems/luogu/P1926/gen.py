#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    m = random.randint(1, 8)
    k = random.randint(1, 20)
    like = [random.randint(1, 30) for _ in range(n)]
    homework_time = [random.randint(1, 30) for _ in range(m)]
    homework_score = [random.randint(1, 15) for _ in range(m)]

    # 保证存在及格方案，并留出随机的总时间。
    r = sum(homework_time) + random.randint(0, 40)
    if sum(homework_score) < k:
        homework_score[random.randrange(m)] += k - sum(homework_score)

    print(n, m, k, r)
    print(*like)
    print(*homework_time)
    print(*homework_score)


if __name__ == "__main__":
    main()
