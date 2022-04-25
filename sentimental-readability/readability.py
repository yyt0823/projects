# TODO
import cs50
import math
# formula = 0.0588 * L - 0.296 * S - 15.8

input = cs50.get_string("Text: ")

letters = 0
words = 0
sentences = 0

for char in input:
    if char.isalpha():
        letters += 1
    elif char.isspace():
        words += 1
    elif char == "?" or char == "." or char == "!":
        sentences += 1
if words != 0:
    words += 1
L = (letters / words) * 100
S = (sentences / words) * 100

final = round(0.0588 * L - 0.296 * S - 15.8)
if final < 1:
    print("Before Grade 1")
elif final > 16:
    print("Grade 16+")
else:
    print("Grade " + str(final))