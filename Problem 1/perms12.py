

places=[1,2,3,4,5]
places_used=[]
new_list=[]
d_places=[]
n_devices=4


def recursive(device):
    if d_places[device]!=0:
        print(d_places)
        recursive(device+1)
        
    else:
        for i in range(len(places)):
            if places_used[i]==False:
                places_used[i]=True
                print("Entra aqui")
                d_places[device]=places[i]
               
              
                
        


def main():


    for k in range(len(places)):
        places_used.append(False)
        d_places.append(0)

    for i in range(len(places)):
        
            for j in range(n_devices):
                places_used[i]= True
                d_places[j] = places[i]
                recursive(j)
                places_used[i]= False
                d_places[j]=0


main()