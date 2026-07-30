experiment_count = int(input())
base_total, base_effective = map(int, input().split())

for _ in range(experiment_count - 1):
    total, effective = map(int, input().split())
    difference_numerator = effective * base_total - base_effective * total
    denominator = total * base_total
    if difference_numerator * 100 > denominator * 5:
        print("better")
    elif difference_numerator * 100 < -denominator * 5:
        print("worse")
    else:
        print("same")
