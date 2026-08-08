#!/usr/bin/env python3

from __future__ import annotations

import sys
from pathlib import Path


def read_input(path: Path) -> tuple[int, int, int, int]:
    data = path.read_text(encoding="utf-8").split()
    if len(data) != 4:
        raise ValueError(f"输入文件 {path} 不是 4 个整数。")
    return tuple(map(int, data))  # type: ignore[return-value]


def read_output(path: Path) -> tuple[int, int, int, int, int]:
    data = path.read_text(encoding="utf-8").split()
    if len(data) != 5:
        raise ValueError(f"输出文件 {path} 不是 5 个整数。")
    return tuple(map(int, data))  # type: ignore[return-value]


def calc_value(a: int, b: int, c: int, d: int, p: int, q: int, r: int, s: int) -> int:
    real_part = a * p + b * q + c * r - d * s
    imag_part = b * p - a * q + c * s + d * r
    return real_part * real_part + imag_part * imag_part


def check_one(name: str, output_path: Path, a: int, b: int, c: int, d: int) -> int:
    p, q, r, s, m = read_output(output_path)
    if m <= 0:
        raise ValueError(f"{name} 输出的 M 必须是正数。")

    real_m = calc_value(a, b, c, d, p, q, r, s)
    if real_m != m:
        raise ValueError(f"{name} 输出不合法：声明 M={m}，实际算出来是 {real_m}。")
    return m


def main() -> int:
    if len(sys.argv) != 4:
        print("usage: checker.py input.txt user.out brute.out", file=sys.stderr)
        return 2

    input_path = Path(sys.argv[1])
    user_path = Path(sys.argv[2])
    brute_path = Path(sys.argv[3])

    a, b, c, d = read_input(input_path)

    try:
        user_m = check_one("user", user_path, a, b, c, d)
        brute_m = check_one("brute", brute_path, a, b, c, d)
    except ValueError as exc:
        print(str(exc), file=sys.stderr)
        return 1

    if user_m != brute_m:
        print(f"M 不一致：user={user_m}, brute={brute_m}", file=sys.stderr)
        return 1

    print(f"OK M={user_m}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
