# TODO
import cs50

while True:
    height = cs50.get_int("Height: ")
    if not 1 <= height <= 8:
        print("input should be between 1 and 8")
    else:
        break


for j in range(1, height + 1):
    print(" " * (height - j), end="")
    print("#" * j + "  " + "#" * j)

