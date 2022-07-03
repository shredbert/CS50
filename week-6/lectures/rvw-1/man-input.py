try:
    x = int(input("X: "))
except ValueError:
    print("Wrong data type!")
    exit(1)

try:
    y = int(input("Y: "))
except ValueError:
    print("Wrong data type!")
    exit(1)

print(f"{x} + {y} = {x + y}")
