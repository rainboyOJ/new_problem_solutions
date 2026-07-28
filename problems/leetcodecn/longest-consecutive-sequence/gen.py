#!/usr/bin/env python3
"""生成随机测试数据。"""
import random


def main():
    random.seed()
    n = random.randint(0, 12)
    if n == 0:
        print(0)
        return
    nums = random.sample(range(-20, 21), min(n, 30))
    # 可能插入重复值
    if random.random() < 0.3 and nums:
        nums.append(random.choice(nums))
    random.shuffle(nums)
    print(len(nums))
    print(*nums)


if __name__ == "__main__":
    main()
