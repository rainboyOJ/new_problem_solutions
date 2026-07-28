#!/usr/bin/env python3
"""生成随机测试数据：第一行 n，第二行 n 个字符串。"""
import random
import string


def main():
    random.seed()
    n = random.randint(1, 10)
    strs = []
    # 生成若干组异位词
    base = ["".join(random.choices(string.ascii_lowercase, k=random.randint(1, 5)))
            for _ in range(random.randint(1, 4))]
    for _ in range(n):
        if base and random.random() < 0.5:
            src = random.choice(base)
            lst = list(src)
            random.shuffle(lst)
            strs.append("".join(lst))
        else:
            s = "".join(random.choices(string.ascii_lowercase, k=random.randint(1, 5)))
            strs.append(s)
            base.append(s)
    print(n)
    print(*strs)


if __name__ == "__main__":
    main()
