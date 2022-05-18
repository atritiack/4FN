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

    elif x == 2:
        produto = N1 * N2
        print('O produto {} * {} é {}.'.format(N1, N2, produto))

    elif x == 3:
        if N1 > N2:
            maior = N1
        else:
            maior = N2
        print('O maior número é {}.'.format(maior))

    elif x == 4:
        N1 = int(input('Digite o primeiro número: '))
        N2 = int(input('Digite o segundo número: '))

    else:
        print('Opção inválida!!')

print('Fim do programa! Até breve!')

