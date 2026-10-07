#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 7)
    print(n)

    prev_cnt = 1
    for _ in range(1, n + 1):
        k = random.randint(1, 4)
        print(k)

        for _planet in range(k):
            choose = random.randint(1, min(3, prev_cnt))
            preds = random.sample(range(1, prev_cnt + 1), choose)

            line = []
            for from_id in preds:
                cost = random.randint(-20, 20)
                line.append(str(from_id))
                line.append(str(cost))

            line.append("0")
            print(" ".join(line))

        prev_cnt = k


if __name__ == "__main__":
    main()
