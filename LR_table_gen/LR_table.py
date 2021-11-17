#!/usr/bin/env python3

from Grammar import Grammar
import argparse


def first_follow(G):
    def union(set_1, set_2):
        set_1_len = len(set_1)
        set_1 |= set_2

        return set_1_len != len(set_1)

    first = {symbol: set() for symbol in G.symbols}
    first.update((terminal, {terminal}) for terminal in G.terminals)
    follow = {symbol: set() for symbol in G.nonterminals}
    follow[G.start].add('$')

    while True:
        updated = False

        for head, bodies in G.grammar.items():
            for body in bodies:
                for symbol in body:
                    if symbol != '^':
                        updated |= union(first[head], first[symbol] - set('^'))

                        if '^' not in first[symbol]:
                            break
                    else:
                        updated |= union(first[head], set('^'))
                else:
                    updated |= union(first[head], set('^'))

                aux = follow[head]
                for symbol in reversed(body):
                    if symbol == '^':
                        continue
                    if symbol in follow:
                        updated |= union(follow[symbol], aux - set('^'))
                    if '^' in first[symbol]:
                        aux = aux | first[symbol]
                    else:
                        aux = first[symbol]

        if not updated:
            return first, follow


class SLRParser:
    def __init__(self, G):
        self.G_prime = Grammar(f"{G.start}' -> {G.start}\n{G.grammar_str}")
        self.max_G_prime_len = len(max(self.G_prime.grammar, key=len))
        self.G_indexed = []

        for head, bodies in self.G_prime.grammar.items():
            for body in bodies:
                self.G_indexed.append([head, body])

        self.first, self.follow = first_follow(self.G_prime)
        self.C = self.items(self.G_prime)
        self.action = list(self.G_prime.terminals) + ['$']
        self.goto = list(self.G_prime.nonterminals - {self.G_prime.start})
        self.parse_table_symbols = self.action + self.goto
        self.parse_table = self.construct_table()

    def CLOSURE(self, I):
        J = I

        while True:
            item_len = len(J)

            for head, bodies in J.copy().items():
                for body in bodies.copy():
                    if '.' in body[:-1]:
                        symbol_after_dot = body[body.index('.') + 1]

                        if symbol_after_dot in self.G_prime.nonterminals:
                            for G_body in self.G_prime.grammar[symbol_after_dot]:
                                J.setdefault(symbol_after_dot, set()).add(
                                    ('.',) if G_body == ('^',) else ('.',) + G_body)

            if item_len == len(J):
                return J

    def GOTO(self, I, X):
        goto = {}

        for head, bodies in I.items():
            for body in bodies:
                if '.' in body[:-1]:
                    dot_pos = body.index('.')

                    if body[dot_pos + 1] == X:
                        replaced_dot_body = body[:dot_pos] + (X, '.') + body[dot_pos + 2:]

                        for C_head, C_bodies in self.CLOSURE({head: {replaced_dot_body}}).items():
                            goto.setdefault(C_head, set()).update(C_bodies)

        return goto

    def items(self, G_prime):
        C = [self.CLOSURE({G_prime.start: {('.', G_prime.start[:-1])}})]

        while True:
            item_len = len(C)

            for I in C.copy():
                for X in G_prime.symbols:
                    goto = self.GOTO(I, X)

                    if goto and goto not in C:
                        C.append(goto)

            if item_len == len(C):
                return C

    def construct_table(self):
        parse_table = {r: {c: '' for c in self.parse_table_symbols} for r in range(len(self.C))}

        for i, I in enumerate(self.C):
            for head, bodies in I.items():
                for body in bodies:
                    if '.' in body[:-1]:  # CASE 2 a
                        symbol_after_dot = body[body.index('.') + 1]

                        if symbol_after_dot in self.G_prime.terminals:
                            s = f's{self.C.index(self.GOTO(I, symbol_after_dot))}'

                            if s not in parse_table[i][symbol_after_dot]:
                                if 'r' in parse_table[i][symbol_after_dot]:
                                    parse_table[i][symbol_after_dot] += '/'

                                parse_table[i][symbol_after_dot] += s

                    elif body[-1] == '.' and head != self.G_prime.start:  # CASE 2 b
                        for j, (G_head, G_body) in enumerate(self.G_indexed):
                            if G_head == head and (G_body == body[:-1] or G_body == ('^',) and body == ('.',)):
                                for f in self.follow[head]:
                                    if parse_table[i][f]:
                                        parse_table[i][f] += '/'

                                    parse_table[i][f] += f'r{j}'

                                break

                    else:  # CASE 2 c
                        parse_table[i]['$'] = 'acc'

            for A in self.G_prime.nonterminals:  # CASE 3
                j = self.GOTO(I, A)

                if j in self.C:
                    parse_table[i][A] = self.C.index(j)

        return parse_table

    def print_info(self):

        print(len(self.C), ' ', len(self.parse_table_symbols))

        for r in range(len(self.C)):
            # print(f'{r:^{3}}', end=' ')

            for c in self.parse_table_symbols:
                # print(f'{self.parse_table[r][c]:^{3 - 1}}', end=' ')
                if self.parse_table[r][c] == 'acc':
                    print(len(self.C) + 100, end=' ')
                elif self.parse_table[r][c] == "":
                    print('0', end=' ')
                elif str(self.parse_table[r][c])[0] == 'r':
                    print(f'-{self.parse_table[r][c][1:]}', end=' ')
                elif str(self.parse_table[r][c])[0] == 's' :
                    print(f'{self.parse_table[r][c][1:]}', end=' ')
                else:
                    print(f'{self.parse_table[r][c]}', end=' ')
            print()

        print()
        print(len(self.G_indexed))


        for i, (head, body) in enumerate(self.G_indexed):
            if body == ('^',): 
                print(0)
            else:
                print(len(body))

        print()    

        print(len(self.action))

        for sym in self.action:
            print(sym)

        print()

        for head, body in self.G_indexed:
            if head == self.G_prime.start:
                print("-1")
                continue
            for i in range(len(self.goto)):
                if self.goto[i] == head:
                    print(i)
                    break

        print("========")

        print(len(self.action), self.action)
        print("========")

        print(len(self.goto), self.goto)
        print("========")

        def fprint(text, variable):
            print(f'{text:>12}: {", ".join(variable)}')

        print('AUGMENTED GRAMMAR:')

        for i, (head, body) in enumerate(self.G_indexed):
            print(f'{i:>{len(str(len(self.G_indexed) - 1))}}: {head:>{self.max_G_prime_len}} -> {" ".join(body)}')

        print()
        fprint('TERMINALS', self.G_prime.terminals)
        print()
        fprint('NONTERMINALS', self.G_prime.nonterminals)
        print()
        fprint('SYMBOLS', self.G_prime.symbols)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('grammar_file', type=argparse.FileType('r'), help='text file to be used as grammar')
    args = parser.parse_args()
    # grammar_file = open("grammar", "r")
    # G = Grammar(grammar_file.read())
    G = Grammar(args.grammar_file.read())

    slr_parser = SLRParser(G)
    slr_parser.print_info()
    

if __name__ == "__main__":
    main()