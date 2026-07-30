wire_count, required_count = map(int, input().split())
wires = [int(round(float(input()) * 100)) for _ in range(wire_count)]


def can_cut(length: int) -> bool:
    return sum(wire // length for wire in wires) >= required_count


low, high = 1, max(wires)
answer = 0
while low <= high:
    middle = (low + high) // 2
    if can_cut(middle):
        answer = middle
        low = middle + 1
    else:
        high = middle - 1

print(f"{answer / 100:.2f}")
