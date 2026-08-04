#!/usr/bin/env python3
"""P4375 Out of Sorts G 的暴力验证程序：直接模拟双向冒泡，数 "moo" 次数。"""

import sys


def main():
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    a = [next(data) for _ in range(n)]

    moo = 0
    while True:
        moo += 1  # 每次进入循环输出一次 moo

        # 正向扫描：把大的往右推
        for i in range(n - 1):
            if a[i] > a[i + 1]:
                a[i], a[i + 1] = a[i + 1], a[i]

        # 逆向扫描：把小的往左拉
        for i in range(n - 2, -1, -1):
            if a[i] > a[i + 1]:
                a[i], a[i + 1] = a[i + 1], a[i]

        # 第三遍检查是否仍有序（无逆序对则退出）
        if all(a[i] <= a[i + 1] for i in range(n - 1)):
            break

    print(moo)


if __name__ == "__main__":
    main()
