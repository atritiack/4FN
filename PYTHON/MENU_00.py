N1 = int(input('Digite o primeiro número: '))
N2 = int(input('Digite o segundo número: '))

x = 0

while x != 5:
    print('''
    [ 1 ] Somar
    [ 2 ] Multiplicar
    [ 3 ] Maior
    [ 4 ] Novos números
    [ 5 ] Sair do programa
    ''')
    print('>>>>>>>> Qual é a sua opção?')
    x = int(input())

    if x == 1:
        soma = N1 + N2
        print('A soma {} + {} é {}.'.format(N1, N2, soma))


print('Fim do programa! Até breve!')

