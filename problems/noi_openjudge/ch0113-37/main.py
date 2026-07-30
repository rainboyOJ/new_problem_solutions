import sys

records = "".join(sys.stdin.read().split()).split("E", 1)[0]


def scores(limit: int) -> list[tuple[int, int]]:
    result = []
    left = right = 0
    for record in records:
        if record == "W":
            left += 1
        else:
            right += 1
        if max(left, right) >= limit and abs(left - right) >= 2:
            result.append((left, right))
            left = right = 0
    result.append((left, right))
    return result


for left, right in scores(11):
    print(f"{left}:{right}")
print()
for left, right in scores(21):
    print(f"{left}:{right}")
