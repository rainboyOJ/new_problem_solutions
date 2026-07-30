people_count = int(input())
boys = []
girls = []

for _ in range(people_count):
    gender, height = input().split()
    if gender == "male":
        boys.append(float(height))
    else:
        girls.append(float(height))

ordered_heights = sorted(boys) + sorted(girls, reverse=True)
print(" ".join(f"{height:.2f}" for height in ordered_heights))
