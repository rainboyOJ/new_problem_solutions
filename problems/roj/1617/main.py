"""转圈游戏：每轮所有人位置顺时针平移 m，共 10^k 轮。"""
import sys

def main() -> None:
    n, m, k, x = map(int, sys.stdin.read().split())
    # 每轮位置编号 +m (mod n)，10^k 轮即快速幂求 m * 10^k mod n
    print((x + m * pow(10, k, n)) % n)

main()
