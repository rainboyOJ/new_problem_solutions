m, h = map(float, input().split())
bmi = m / (h * h)

if bmi < 18.5:
    print("Underweight", end="")
elif bmi < 24:
    print("Normal", end="")
else:
    print(f"{bmi:.6g}\nOverweight", end="")
