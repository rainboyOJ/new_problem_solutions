#!/usr/bin/env python3
import sys


def multiply(p: list[int], q: list[int]) -> list[int]:
    """
    计算两个排列的乘积 r = p * q
    根据题意定义：r_k = q[p_k] (1-based)
    直接遍历 p 中的每个数字 x，取 q 对应位置的元素 q[x - 1]
    """
    return [q[x - 1] for x in p]


def beauty(r: list[int]) -> int:
    """
    计算排列 r 的美丽值：最长连续前缀满足 r_1 = 1, r_2 = 2, ..., r_k = k
    """
    k = 0
    for idx, val in enumerate(r, 1):
        if idx != val:
            break
        k += 1
    return k


def main():
    default_input = """\
3 4
2 4 1 3
1 2 4 3
2 1 3 4
"""
    raw = sys.stdin.read().strip()
    if not raw:
        print("[提示] 未检测到输入，运行默认探究样例：\n" + default_input)
        raw = default_input

    # 使用 iter 构建统一的数据流迭代器，彻底告别下标游标追踪
    it = iter(raw.split())

    n = int(next(it))
    m = int(next(it))
    # 借助迭代器优雅切分每一个排列
    perms = [[int(next(it)) for _ in range(m)] for _ in range(n)]

    print("=" * 60)
    print(f"输入排列 (n={n}, m={m}):")
    for i, p in enumerate(perms, 1):
        print(f"  a[{i}] = {p}")
    print("=" * 60)

    print("\n两两相乘与美丽值矩阵 (a_i * a_j):")
    best_results = []
    for i, pi in enumerate(perms, 1):
        best_k = 0
        best_j = -1
        best_r = []
        print(f"\n--- 固定 a[{i}] = {pi} ---")
        for j, pj in enumerate(perms, 1):
            prod = multiply(pi, pj)
            b_val = beauty(prod)
            print(f"  a[{i}] * a[{j}] = {prod}  --> 美丽值 = {b_val}")
            if b_val > best_k or best_j == -1:
                best_k = b_val
                best_j = j
                best_r = prod
        best_results.append((best_k, best_j, best_r))

    print("\n" + "=" * 60)
    print("每个 a[i] 的最大美丽值及对应结果:")
    for i, (k_val, j_idx, r_list) in enumerate(best_results, 1):
        print(f"  a[{i}] 的最大美丽值 = {k_val} (来自 a[{i}] * a[{j_idx}] = {r_list})")

    print("\n最终题目输出答案:")
    print(*(res[0] for res in best_results))
    print("=" * 60)


if __name__ == "__main__":
    main()
