"""数位统计 DP：cnt(n, d) 统计 1..n 中数字 d 的出现次数，答案作前缀差。"""
import sys


def cnt(n: int, d: int) -> int:
    """统计 1..n 中数字 d 出现的总次数，逐位贡献法 O(log n)。"""
    res, p = 0, 1  # p 为当前统计的位权（个位、十位、……）
    while p <= n:
        high, cur, low = n // (p * 10), n // p % 10, n % p  # 高位 / 当前位 / 低位
        if d == 0:
            # 0 不能作前导：前缀（高位部分）必须 >= 1
            if high:
                res += (high - 1) * p + (p if cur else low + 1)
        else:
            # 前缀取 0..high-1 时低位任意；前缀等于 high 时按当前位与 d 比大小
            res += high * p + (p if cur > d else low + 1 if cur == d else 0)
        p *= 10
    return res


for line in sys.stdin:
    a, b = map(int, line.split())
    if a == b == 0:  # 终止行不处理
        break
    if a > b:
        a, b = b, a  # a 可能大于 b，先交换
    print(*[cnt(b, d) - cnt(a - 1, d) for d in range(10)])
