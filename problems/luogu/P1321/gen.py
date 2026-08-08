#!/usr/bin/env python3
import random


def visible_for_all(ops):
    for idx, (word, pos) in enumerate(ops):
        ok = False
        for i in range(len(word)):
            covered = False
            for j in range(idx + 1, len(ops)):
                word2, pos2 = ops[j]
                if pos2 <= pos + i < pos2 + len(word2):
                    covered = True
                    break
            if not covered:
                ok = True
                break
        if not ok:
            return False
    return True


def main():
    random.seed()
    words = ["boy", "girl"]
    while True:
        n = random.randint(10, 40)
        s = ["."] * n
        ops = []
        for _ in range(random.randint(1, 8)):
            word = random.choice(words)
            pos = random.randint(0, n - len(word))
            ops.append((word, pos))
        if not visible_for_all(ops):
            continue
        for word, pos in ops:
            for i, ch in enumerate(word):
                s[pos + i] = ch
        print("".join(s))
        return


if __name__ == "__main__":
    main()
