#include <ostream>
#include <iostream> 
const int maxlegth=20;
typedef int elementtype;
typedef int position;
class Stos
{
int S[maxlegth] ;
position Top;//szczyt stosu
public:
Stos(){
    Top = -1;
}
void Push(elementtype x){
    if(Top < maxlegth-1){
        S[Top+1]=x;
        Top++;
    }
    else{
        std::cout<<"stos jest przepelniony"<<std::endl;
    }
}
void Pop(){
    if(Top != -1){
        Top--;
    }else{
        std::cout<<"stos jest pusty"<<std::endl;
    }
}
bool Empty(){
    if(Top == -1){
        std::cout<< "true" << std::endl;
        return true;
    }
    std::cout<< "false"<<std::endl;
    return false;
}
elementtype TopElem(){
    if(Top != -1){
        return S[Top];
    }
    return -1000000;
}
void Makenul(){
    Top = -1;
}
};

int main(){
    Stos stos;
    stos.Empty();
    stos.Push(5);
    std::cout<< stos.TopElem() << std::endl;
    stos.Empty();
    stos.Pop();
    stos.Empty();
    stos.Push(2);
    stos.Push(3);
    std::cout<< stos.TopElem() << std::endl;
    stos.Makenul();
    stos.Empty();

}