def rotate(pattern):
    n = len(pattern)
    return ["".join(pattern[n - 1 - row][col] for row in range(n)) for col in range(n)]


def reflect(pattern):
    return [row[::-1] for row in pattern]


n = int(input())
before = [input().strip() for _ in range(n)]
after = [input().strip() for _ in range(n)]

rot90 = rotate(before)
rot180 = rotate(rot90)
rot270 = rotate(rot180)
reflected = reflect(before)

if rot90 == after:
    print(1)
elif rot180 == after:
    print(2)
elif rot270 == after:
    print(3)
elif reflected == after:
    print(4)
elif rotate(reflected) == after or rotate(rotate(reflected)) == after or rotate(rotate(rotate(reflected))) == after:
    print(5)
elif before == after:
    print(6)
else:
    print(7)
