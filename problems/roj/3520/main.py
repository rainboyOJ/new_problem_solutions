"""NOIP2003 普及组 乒乓球：11/21 分制逐球模拟。

一局结束条件：某方得分 >= n 且分差 >= 2；末尾未打完的一局也输出当前比分。
"""
import sys


def play(s: str, n: int) -> list[str]:
    """按 n 分制扫描比分序列，返回每局（含末尾未完成局）的 'a:b' 列表。"""
    res: list[str] = []
    a = b = 0
    for c in s:
        if c == 'W':
            a += 1
        elif c == 'L':
            b += 1
        if max(a, b) >= n and abs(a - b) >= 2:  # 达到 n 分且分差 >= 2，本局结束
            res.append(f"{a}:{b}")
            a = b = 0
    res.append(f"{a}:{b}")  # 最后一局可能未结束，输出当前比分（可能 0:0）
    return res


def main() -> None:
    s = sys.stdin.read().split('E')[0]  # 忽略 E 及之后的所有内容
    r11, r21 = play(s, 11), play(s, 21)
    sys.stdout.write('\n'.join(r11) + '\n\n' + '\n'.join(r21) + '\n')


if __name__ == '__main__':
    main()
