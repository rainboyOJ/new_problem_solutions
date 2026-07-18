y, m = map(int, input().split())
is_leap = (y % 4 == 0 and y % 100 != 0) or (y % 400 == 0)

match m:
    case 1 | 3 | 5 | 7 | 8 | 10 | 12:
        print(31, end="")
    case 4 | 6 | 9 | 11:
        print(30, end="")
    case 2:
        print(29 if is_leap else 28, end="")
