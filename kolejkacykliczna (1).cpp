#include <iostream>
const int maxlength=50;
typedef int elementtype;
typedef int position;
class Kolejka
{
protected :
elementtype Queue[maxlength];
position Front; // Indeks elementu czołowego
position Rear; // Indeks ostatniego elementu
public:
Kolejka(){
    Rear = 0;
    Front = 1;
}

bool Empty(){
    if(AddOne(Rear)==Front){
        std::cout<<"pusta"<<std::endl;
        return true;
    } else{
        std::cout<<"nie pusta"<<std::endl;
        return false;
    }
}

void Dequeue(){
    if (AddOne(Rear)!=Front)
    {
        Front = AddOne(Front);
    }
}

elementtype FrontElem(){
    if (AddOne(Rear)!=Front){
        return Queue[Front];
    }
    std::cout << "kolejka pusta - brak pierwszego elementu" << std::endl;
    return -10000000;
}

void Makenul(){
    Front = 1;
    Rear = 0;
}


int AddOne(int i){
    return (i+1) % maxlength;
}

void Enqueue(elementtype x){
    if(AddOne(AddOne(Rear))==Front){
        std::cout<<"kolejka jest pelna"<<std::endl;
    } else{
        Rear = AddOne(Rear);
        Queue[Rear] = x;
    }
}
};

int main(){

    Kolejka kolejka;

    kolejka.Empty();
    kolejka.Enqueue(5);
    kolejka.Empty();
    std::cout<<kolejka.FrontElem()<<std::endl;
    kolejka.Dequeue();
    kolejka.Empty();
    kolejka.Enqueue(4);
    kolejka.Enqueue(3);
    kolejka.Enqueue(2);
    std::cout<<kolejka.FrontElem()<<std::endl;
    kolejka.Enqueue(1);
    std::cout<<kolejka.FrontElem()<<std::endl;
    kolejka.Dequeue();
    std::cout<<kolejka.FrontElem()<<std::endl;
    kolejka.Enqueue(6);
    std::cout<<kolejka.FrontElem()<<std::endl;
    kolejka.Dequeue();
    kolejka.Dequeue();
    std::cout<<kolejka.FrontElem()<<std::endl;
    kolejka.Makenul();
    kolejka.Empty();
}