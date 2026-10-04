"""ROJ 1660 网格：不越过对角线的路径计数（卡特兰数推广，精确大整数）。"""
import sys
from math import comb

def main() -> None:
    n, m = map(int, sys.stdin.read().split())
    # 反射法：全部路径 C(n+m, m) 减去接触直线 y = x+1 的坏路径 C(n+m, m-1)
    print(comb(n + m, m) - comb(n + m, m - 1))

main()
