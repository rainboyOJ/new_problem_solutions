#!/usr/bin/env python3
"""P9717 随机数据生成器（输出到 stdout）。

题面约束：1 <= T <= 1e6，sum(len) <= 1e7，串由 0/1 组成。

对拍时暴力是 O(答案 * n^2) 的朴素模拟，所以默认模式只生成 n <= 12 的小串，
并刻意覆盖各种结构：

  * 全 0 / 全 1 / 单字符；
  * 0 与 1 个数均衡（接近 1:1）的串，这类串答案接近 n，最容易暴露周期算法的错；
  * 少数派很少（0 很少或 1 很少）的串，考验 Raney 切点与栈合并；
  * 只有一段连续 0 后面跟一段连续 1 的「块状」串。

`--big` 模式生成贴满约束的大数据（sum(len) 逼近 1e7），用于检查正解不崩。
可选参数是「轮次」，用来在同一次对拍里生成不同批次的数据。
"""
import random
import sys


def gen_small(rng):
    cases = []
    # 固定边界：单字符、全 0、全 1、两种两位串
    cases += ["0", "1", "00", "11", "01", "10"]
    # 随机长度 2..12 的串，风格上分四类
    for _ in range(rng.randint(8, 14)):
        n = rng.randint(2, 12)
        style = rng.randrange(4)
        if style == 0:
            s = "".join(rng.choice("01") for _ in range(n))
        elif style == 1:  # 接近 1:1
            half = n // 2
            bits = ["0"] * half + ["1"] * (n - half)
            rng.shuffle(bits)
            s = "".join(bits)
        elif style == 2:  # 少数派很少
            ones = rng.randint(1, max(1, n // 4))
            bits = ["1"] * ones + ["0"] * (n - ones)
            rng.shuffle(bits)
            s = "".join(bits)
        else:  # 块状：一段 0 接一段 1
            a = rng.randint(1, n - 1)
            s = "0" * a + "1" * (n - a)
            if rng.random() < 0.5:
                s = s[::-1]
        cases.append(s)
    rng.shuffle(cases)
    return cases


def gen_big(rng):
    """大数据：sum(len) 逼近 1e7，长度分布覆盖 1、2、3 与长串。"""
    cases = []
    total = 0
    LIMIT = 10 ** 7
    while total < LIMIT:
        style = rng.randrange(5)
        if style == 0:
            n = rng.randint(1, 3)
        elif style == 1:
            n = rng.randint(4, 100)
        elif style == 2:
            n = rng.randint(100, 10000)
        elif style == 3:
            n = rng.randint(10000, 200000)
        else:
            n = rng.randint(200000, 1000000)
        n = min(n, LIMIT - total)
        if n <= 0:
            break
        k = rng.randrange(n + 1)          # 1 的个数，覆盖 0 到 n
        bits = ["1"] * k + ["0"] * (n - k)
        rng.shuffle(bits)
        cases.append("".join(bits))
        total += n
        if len(cases) >= 1000:
            break
    return cases


def main():
    args = [a for a in sys.argv[1:] if a != "--big"]
    big = "--big" in sys.argv
    round_no = int(args[0]) if args else 0
    rng = random.Random(20221003 + round_no * 1000003)

    cases = gen_big(rng) if big else gen_small(rng)

    out = [str(len(cases))]
    out.extend(cases)
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
