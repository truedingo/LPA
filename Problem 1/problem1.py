import operator

class Coordinates:
    def __init__(self,x,y):
        self.x=x
        self.y=y


class pairs_source_and_target:
    def __init__(self,source,target):
        self.source=source
        self.target=target





def main():
    places = eval(input())
    coordinates_list=list()
    for i in range(places):
        coordinates_aux = input()
        coordinates = coordinates_aux.strip().split(' ')
        coordinates1 = Coordinates(int(coordinates[0]),int(coordinates[1]))
        coordinates_list.append(coordinates1)

    new_input = input()
    aux = new_input.strip().split(' ')
    n_devices = int(aux[0])
    n_colliders = int(aux[1])
    pairs_list= list()
    for j in range(n_colliders):
        pairs_aux = input()
        pairs_split = pairs_aux.strip().split(' ')
        pairs= pairs_source_and_target(int(pairs_split[0]),int(pairs_split[1]))
        print(pairs.source,pairs.target)
        pairs_list.append(pairs)
    
    for i in range(len(coordinates_list)):
        print("cord x: ", coordinates_list[i].x, "coord y: ", coordinates_list[i].y)




main()
