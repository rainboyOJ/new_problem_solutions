def is_leap(year: int) -> bool:
    return year % 400 == 0 or year % 4 == 0 and year % 100 != 0


case_count = int(input())
for _ in range(case_count):
    year, first_month, second_month = map(int, input().split())
    month_lengths = [31, 28 + is_leap(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    starts = [0]
    for length in month_lengths:
        starts.append(starts[-1] + length)
    print("YES" if (starts[first_month - 1] - starts[second_month - 1]) % 7 == 0 else "NO")
