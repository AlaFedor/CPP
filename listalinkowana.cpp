
#include <iostream>
typedef int elementtype;
struct celltype {
elementtype element;
celltype * next;
};
typedef celltype * position;
class Lista
{
protected :
position l; // wskaźnik do głowy listy
public:
Lista(){
	l = new celltype;
	l->next=nullptr;//tworzymy glowe
} //konstruktor
~Lista(){
    auto current = l;
    while(current != nullptr){
		auto tmp = current;
		current = current->next;
		delete tmp;
	}

} //destruktor
void Insert(elementtype x, position p){
	if(p != nullptr){
    auto tmp = p->next;
    p->next = new celltype;
    p->next->element = x;
    p->next->next = tmp;}
}
void Delete(position p){
	if(p != nullptr && p->next !=nullptr){
    auto tmp = p-> next;
    p->next = tmp -> next;
    delete tmp;}
}
elementtype Retrieve(position p){
	if(p!=nullptr && p->next != nullptr){
		return p->next->element;
	}
	return -1;
}
position Locate(elementtype x){
	auto current = l;
	while(current->next != nullptr){
		if(current->next->element == x){
				return current;
			}
		current = current->next;
	}
	return nullptr;
}
position First(){
    return l;
}
position Next(position p){
	if(p != nullptr){
    return p->next;}
	return nullptr;
}
position Previous(position p){
    auto it = First();
    while(it->next != p){
		  if(it->next == nullptr){return nullptr;}
        it = it -> next;
    }
    return it;
}
position END(){
    auto it = l;
    while(it->next != nullptr){
        it = it->next;
    }
    return it;
}
void PrintList(){
	auto current = l->next;
	while (current != nullptr){
		std::cout<< current->element<<" ";
		current = current->next;
	}
	std::cout<<std::endl;
}
};

int main() {
    Lista list;

    //  Wstaw 5 na poczatek
    list.Insert(5, list.First());
    std::cout << "Pierwszy element: " << list.Retrieve(list.First()) << std::endl;

    //  Wstaw 2 na poczatek
    list.Insert(2, list.First());
    std::cout << "Pierwszy element po wstawieniu: " << list.Retrieve(list.First()) << std::endl;
    std::cout << "Drugi element: " << list.Retrieve(list.Next(list.First())) << std::endl;

    //  Wstaw 1 za pierwszym elementem
    list.Insert(1, list.Next(list.First()));
    std::cout << "Lista po wstawieniach: ";
    list.PrintList();

    //  Wstaw 100 na koniec listy
    list.Insert(100, list.END());
    std::cout << "Lista po wstawieniu 100 na koniec: ";
    list.PrintList();

    //  Usun element znajdujacy sie przed wartoscia 100
    celltype* pos100 = list.Locate(100);
    if (pos100 != nullptr) {
        list.Delete(list.Previous(pos100));
    }
    std::cout << "Lista po usuni�ciu elementu przed 100: ";
    list.PrintList();

    return 0;
}
