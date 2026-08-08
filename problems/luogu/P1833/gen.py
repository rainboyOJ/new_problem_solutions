#!/usr/bin/env python3
import random


def fmt_time(minutes: int) -> str:
    hour = minutes // 60
    minute = minutes % 60
    return f"{hour}:{minute:02d}"


def main() -> None:
    random.seed()

    start = random.randint(0, 23 * 60)
    duration = random.randint(0, min(120, 24 * 60 - 1 - start))
    end = start + duration
    n = random.randint(1, 8)

    print(fmt_time(start), fmt_time(end), n)
    for _ in range(n):
        t = random.randint(1, 12)
        c = random.randint(1, 20)
        if random.random() < 0.35:
            p = 0
        else:
            p = random.randint(1, 6)
        print(t, c, p)


if __name__ == "__main__":
    main()
