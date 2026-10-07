#!/usr/bin/env python3
"""gen.py：D. 食堂(Meal) 的小数据对拍生成器。

数据规模 N<=8（全排列暴力最多可承受的规模），a,b 取 [1,10]。
输出格式与题目一致：第一行 N，随后 N 行每行 a_i b_i。
"""
import random
import sys

def main():
    # 支持外部传入种子（如对拍脚本 DUPAI_SEED），否则随机
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
    rng = random.Random(seed)

    n = rng.randint(1, 8)
    print(n)
    for _ in range(n):
        a = rng.randint(1, 10)
        b = rng.randint(1, 10)
        print(a, b)

if __name__ == "__main__":
    main()
