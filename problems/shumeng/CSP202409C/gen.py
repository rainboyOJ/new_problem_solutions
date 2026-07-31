#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    n = random.randint(8, 20)
    original = ["line_{}".format(i) for i in range(1, n + 1)]
    print(n)
    for line in original:
        print(line)

    print("ignored text before the first block")
    block_count = random.randint(1, 3)
    starts = []
    current = random.randint(1, 2)
    for _ in range(block_count):
        if current > n - 1:
            break
        old_count = random.randint(1, min(2, n - current + 1))
        starts.append((current, old_count))
        current += old_count + random.randint(1, 3)

    if not starts:
        starts.append((1, 1))
    for block_id, (start, old_count) in enumerate(starts):
        print("@@ -{},{} +{},{} @@".format(start, old_count, start, old_count))
        for offset in range(old_count):
            print("-" + original[start - 1 + offset])
            print("+changed_{}_{}".format(block_id, offset))
        if block_id + 1 < len(starts):
            print("# comment between blocks")


if __name__ == "__main__":
    main()
