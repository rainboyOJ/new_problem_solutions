#!/usr/bin/env python3
import random


def random_word():
    length = random.randint(1, 6)
    chars = []
    for _ in range(length):
        chars.append(random.choice("abc"))
    return "".join(chars)


def main():
    random.seed()
    n = random.randint(1, 8)
    words = set()

    while len(words) < n:
        # 一部分数据刻意从已有单词继续扩展，增加词链出现概率。
        if words and random.random() < 0.6:
            base = random.choice(list(words))
            if len(base) < 6:
                words.add(base + random.choice("abc"))
                continue
        words.add(random_word())

    words = sorted(words)
    print(len(words))
    for word in words:
        print(word)


if __name__ == "__main__":
    main()
