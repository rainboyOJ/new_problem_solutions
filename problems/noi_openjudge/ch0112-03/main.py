patient_count = int(input())
selected_names = []

for _ in range(patient_count):
    name, temperature, cough = input().split()
    if float(temperature) >= 37.5 and cough == "1":
        selected_names.append(name)

print(*selected_names, sep="\n")
print(len(selected_names))
