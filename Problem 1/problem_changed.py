gir import operator
from itertools import permutations

'''def main():
    places = eval(input())
    coordinates_list=list()
    for i in range(places):
        coordinates_aux = input()
        coordinates = coordinates_aux.strip().split(' ')
        coordinates_list.append([int(coordinates[0]), int(coordinates[1])])

    new_input = input()
    aux = new_input.strip().split(' ')
    n_devices = int(aux[0])
    n_colliders = int(aux[1])
    pairs_list= list()
    for j in range(n_colliders):
        pairs_aux = input()
        pairs_split = pairs_aux.strip().split(' ')
        pairs_list.append([int(pairs_split[0]), int(pairs_split[1])])
    
    print("Cord list: ", coordinates_list)
    print("Pairs list: ", pairs_list)
    comb = permutations(coordinates_list, len(coordinates_list))
    for i in comb:
        print(i)
'''
def main():
    coordinates_list = list()
    pairs_list = list()
    f = open('testcases.txt', 'r')
    line = f.readline()
    line2 = line.strip().split()
    numb = int(line2[0])
    print(numb)
    for i in range(numb):
        line = f.readline()
        line2 = line.strip().split(" ")
        coordinates_list.append([int(line2[0]), int(line2[1])])
    line = f.readline()
    line2 = line.strip().split(" ")
    n_devices = int(line2[0])
    n_colliders = int(line2[1])

    for i in range(n_colliders):
        line = f.readline()
        line2 = line.strip().split(" ")
        pairs_list.append([int(line2[0]), int(line2[1])])
    
    print("Cord list: ", coordinates_list)
    print("Pairs list: ", pairs_list)
    comb = permutations(coordinates_list, len(coordinates_list))
    for i in comb:
        print(i)


main()
