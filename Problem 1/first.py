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