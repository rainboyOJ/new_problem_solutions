"""ROJ 2026 序言页码：统计 1..N 的罗马数字中每个字符出现次数。"""
import sys
from collections import Counter

# 各数位 0~9 对应的罗马片段（千/百/十/个位），每行即标准罗马记数法
DIGITS = [
    ["", "M", "MM", "MMM"],                                    # 千位：1000~3000
    ["", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"],  # 百位
    ["", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"],  # 十位
    ["", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"],  # 个位
]


def roman(n: int) -> str:
    """把 1..3499 的整数转成标准罗马数字。"""
    return DIGITS[0][n // 1000] + DIGITS[1][n // 100 % 10] + DIGITS[2][n // 10 % 10] + DIGITS[3][n % 10]


def main() -> None:
    n: int = int(sys.stdin.read())
    cnt: Counter[str] = Counter(ch for i in range(1, n + 1) for ch in roman(i))
    # 字符按数字表从小到大输出，跳过未出现的字符
    print("\n".join(f"{c} {cnt[c]}" for c in "IVXLCDM" if cnt[c]))


main()
