A = 5
B = 4
C = 2
D = 1
E = 0
F = 6
G = 7

symbol = input("Enter a symbol letter makeup: ")
symbol = symbol.upper()
number = 0

if "A" in symbol:
    number |= 1 << A
if "B" in symbol:
    number |= 1 << B
if "C" in symbol:
    number |= 1 << C
if "D" in symbol:
    number |= 1 << D
if "E" in symbol:
    number |= 1 << E
if "F" in symbol:
    number |= 1 << F
if "G" in symbol:
    number |= 1 << G

#print the number in binary and a c define
print("0b{:08b}".format(number))