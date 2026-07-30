size = int(input())
source = [input().split() for _ in range(size)]
target = [input().split() for _ in range(size)]

clockwise = [[source[size - 1 - column][row] for column in range(size)] for row in range(size)]
counterclockwise = [[source[column][size - 1 - row] for column in range(size)] for row in range(size)]
central = [row[::-1] for row in source[::-1]]

if target == source:
    print(4)
elif target == clockwise:
    print(1)
elif target == counterclockwise:
    print(2)
elif target == central:
    print(3)
else:
    print(5)
