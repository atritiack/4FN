import math

# a = float(input('Insira o valor de a: '))
# b = float(input('Insira o valor de b: '))
# c = float(input('Insira o valor de c: '))

a, b, c = input().split()
a = float(a)
b = float(b)
c = float(c)

delta = b**2 - 4*a*c

rdelta = math.sqrt(delta)
print

if rdelta < 0:
    print('Impossível calcular, mf!!')

else:
    r1 = (- b + rdelta)/(2*a)
    r2 = (- b - rdelta)/(2*a)
    print(f'R1 = {r1:.5f}\nR2 = {r2:.5f}')

    


    
