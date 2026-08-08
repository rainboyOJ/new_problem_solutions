year = int(input())

match year:
    case y if (y % 4 == 0 and y % 100 != 0) or (y % 400 == 0):
        print(1, end="")
    case _:
        print(0, end="")
