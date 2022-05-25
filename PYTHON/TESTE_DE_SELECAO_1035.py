A, B, C, D = input().split()

A = int(A)
B = int(B)
C = int(C)
D = int(D)

resto = A % 2

if((B > C) and (D > A) and ((C + D) > (A + B)) and (C > 0) and (D > 0) and (resto == 0)):
    print('Valores aceitos')
else:
    print('Valores não aceitos')
