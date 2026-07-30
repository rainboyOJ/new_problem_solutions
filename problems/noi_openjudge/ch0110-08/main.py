patient_count = int(input())
patients = []

for order in range(patient_count):
    patient_id, age = input().split()
    age = int(age)
    patients.append((patient_id, age, order))

# 年龄不足 60 的人排在后面；同龄老人和所有非老人按登记次序保持稳定。
patients.sort(
    key=lambda patient: (
        patient[1] < 60,
        -patient[1] if patient[1] >= 60 else 0,
        patient[2],
    )
)
for patient_id, _, _ in patients:
    print(patient_id)
