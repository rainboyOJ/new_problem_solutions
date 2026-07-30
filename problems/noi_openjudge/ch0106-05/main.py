patient_count = int(input())
ages = map(int, input().split())
groups = [0, 0, 0, 0]

for age in ages:
    if age <= 18:
        groups[0] += 1
    elif age <= 35:
        groups[1] += 1
    elif age <= 60:
        groups[2] += 1
    else:
        groups[3] += 1

for count in groups:
    print(f"{count * 100 / patient_count:.2f}%")
