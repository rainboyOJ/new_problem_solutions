#!/usr/bin/env python3
"""生成 HPACK 题目的样例数据。"""

from pathlib import Path
import random


def main():
    print((Path(__file__).parent / "in1").read_text(encoding="utf-8"), end="")


if __name__ == "__main__":
    main()
