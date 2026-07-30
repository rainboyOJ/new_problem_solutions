weekday = int(input())
month_lengths = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

for month, length in enumerate(month_lengths, start=1):
    if (weekday + 11) % 7 + 1 == 5:
        print(month)
    weekday = (weekday + length - 1) % 7 + 1
