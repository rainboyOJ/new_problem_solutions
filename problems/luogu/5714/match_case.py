m, h = map(float, input().split())
bmi = m / (h * h)

match bmi:
    case x if x < 18.5:
        print("Underweight", end="")
    case x if x < 24:
        print("Normal", end="")
    case _:
        print(f"{bmi:.6g}\nOverweight", end="")
