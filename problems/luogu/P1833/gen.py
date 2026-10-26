#!/usr/bin/env python3
import os
import sys
from cyaron import IO, randint


def format_time(minutes: int) -> str:
    hour = minutes // 60
    minute = minutes % 60
    return f"{hour}:{minute:02d}"


def main() -> None:
    case = os.getenv("P1833_CASE", "random")
    n = int(os.getenv("P1833_N", "8"))
    duration = int(os.getenv("P1833_T", "30"))
    max_count = int(os.getenv("P1833_P", "12"))
    max_item_time = int(os.getenv("P1833_ITEM_T", "12"))
    max_beauty = int(os.getenv("P1833_C", "20"))
    start = int(os.getenv("P1833_START", "400"))

    forced_item: tuple[int, int, int] | None = None
    if case == "min":
        n, duration, forced_item = 1, 1, (1, 1, 1)
    elif case == "zero":
        n, duration, forced_item = 1, 0, (1, 1, 0)
    elif case == "one":
        n, duration, forced_item = 1, 1, (1, 1, 0)
    elif case == "too_long":
        n, duration, forced_item = 1, 1, (2, 100, 1)
    elif case == "p_zero":
        n, duration, forced_item = 1, 10, (2, 3, 0)
    elif case == "p_one":
        n, duration, forced_item = 1, 10, (2, 3, 1)
    elif case == "p_large":
        n, duration, forced_item = 1, 1000, (1, 200, 100)
    elif case == "count100":
        n, duration, forced_item = 1, 1000, (1, 200, 100)
    elif case == "full":
        n, duration, max_count, max_item_time = 10000, 1000, 100, 100

    if n < 1 or duration < 0 or duration > 1000:
        raise ValueError("n must be positive and duration must be in [0, 1000]")
    if start < 0 or start + duration > 23 * 60 + 59:
        start = 0

    io = IO(input_file=sys.stdout, disable_output=True)
    io.input_writeln(format_time(start), format_time(start + duration), n)

    if forced_item is not None:
        io.input_writeln(*forced_item)
        return

    for _ in range(n):
        tree_time = randint(1, max(1, max_item_time))
        beauty = randint(1, max(1, max_beauty))
        count_limit = 0 if randint(1, 4) == 1 else randint(1, max(1, max_count))
        io.input_writeln(tree_time, beauty, count_limit)


if __name__ == "__main__":
    main()
