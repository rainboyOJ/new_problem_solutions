#!/usr/bin/env python3
"""生成消息解码的样例数据。"""

from pathlib import Path


def main():
    print((Path(__file__).parent / "in1").read_text(encoding="utf-8"), end="")


if __name__ == "__main__":
    main()
