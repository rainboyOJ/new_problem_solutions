#!/usr/bin/env python3
"""Interactive wrapper around duipai.py."""

from __future__ import annotations

import argparse
from pathlib import Path
import subprocess
import sys


SCRIPT_DIR = Path(__file__).resolve().parent
DUI_PAI = SCRIPT_DIR / "duipai.py"


def ask(prompt: str, default: str) -> str:
    value = input(f"{prompt} [{default}]: ").strip()
    return value or default


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Interactive wrapper around duipai.py",
        epilog="""示例:
  cd problems/luogu/P1001
  python3 ../../../scripts/problem-analysis-tools/duipai-human.py""",
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    parser.parse_args()

    cwd = Path.cwd()
    default_gen = "gen.py" if (cwd / "gen.py").exists() else ""
    default_user = "main.cpp" if (cwd / "main.cpp").exists() else ""
    default_brute = "brute.cpp" if (cwd / "brute.cpp").exists() else ""

    gen = ask("generator", default_gen)
    user = ask("user solution", default_user)
    brute = ask("brute solution", default_brute)
    count = ask("test count", "200")
    timeout = ask("timeout seconds", "2")

    if not gen or not user or not brute:
        print("gen, user, and brute are required", file=sys.stderr)
        return 2

    cmd = [
        sys.executable,
        str(DUI_PAI),
        "--gen",
        gen,
        "--user",
        user,
        "--brute",
        brute,
        "-n",
        count,
        "--timeout",
        timeout,
    ]
    print("Running:", " ".join(cmd))
    return subprocess.call(cmd)


if __name__ == "__main__":
    raise SystemExit(main())
