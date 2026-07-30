day_count, month_count = map(int, input().split())
expenses = [int(input()) for _ in range(day_count)]


def can_arrange(limit: int) -> bool:
    used_months = 1
    current_sum = 0
    for expense in expenses:
        if current_sum + expense > limit:
            used_months += 1
            current_sum = expense
        else:
            current_sum += expense
    return used_months <= month_count


low, high = max(expenses), sum(expenses)
while low < high:
    middle = (low + high) // 2
    if can_arrange(middle):
        high = middle
    else:
        low = middle + 1

print(low)
