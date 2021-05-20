#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

class Nodo{
public:
    int valore;
    Nodo* succ;
    Nodo* prec;
};

class Lista{
Nodo* testa;
public:
    Lista() {testa=nullptr;}
    ~Lista();
    Nodo* getTesta() {return testa;}

    // inserimento in testa
    void inserisci(int val);
    void inserisci(Nodo* precedente, int val);
    void inserisci_in_coda(int val);

    Nodo* ricerca(int val);
    void rimuovi(int val);

    friend ostream& operator<<(ostream& out, const Lista& ls);
};

Lista::~Lista(){
    Nodo* iter = this->testa;

    while(iter!=nullptr){
        Nodo* temp = iter->succ;
        delete iter;
        iter = temp;
    }
}

ostream& operator<<(ostream& out, const Lista& ls){
    Nodo* iter=ls.testa; //get testa
    while(iter!=nullptr){
        if(iter->prec==nullptr)
            out << "NULL <-- ";
        else
            out << iter->prec->valore << " <-- ";
        out << iter->valore << endl;
      /*  if(iter->succ)
            out<< iter->succ->valore << endl;*/
        iter = iter->succ;
    }
    out << "NULL" << endl;
    return out;
}

void Lista::inserisci(int val){
    Nodo* nuovo = new Nodo;
    nuovo->valore = val;
    nuovo->prec=nullptr;
    nuovo->succ = this->testa;
    if(this->testa)
        this->testa->prec=nuovo;

    this->testa = nuovo;
}

void Lista::inserisci(Nodo* precedente, int val){
    Nodo* nuovo = new Nodo;
    nuovo->valore = val;
    nuovo->succ=precedente->succ;
    precedente->succ->prec = nuovo;
    precedente->succ = nuovo;
    nuovo->prec = precedente;
}

void Lista::inserisci_in_coda(int val){
    
    if(this->testa == nullptr){
        inserisci(val);
        return;
        /*nuovo->succ = nullptr;
        this->testa = nuovo;*/
    }

    Nodo* nuovo = new Nodo;
    Nodo* iter = this->testa;
    nuovo->valore = val;
    while(iter->succ!=nullptr)
        iter = iter->succ;
    iter->succ=nuovo;
    nuovo->succ=nullptr;
    nuovo->prec=iter;

}

Nodo* Lista::ricerca(int val){
    Nodo *p;

    for(p=this->testa;p!=nullptr;p = p->succ)
        if(p->valore==val)
            return p;

    return nullptr;
}

void Lista::rimuovi(int val){

    Nodo* nd;

    if(this->testa == nullptr)
        cout << "Lista vuota: impossibile rimuovere elementi."<<endl;
    else if(this->testa->valore == val){
        nd = this->testa;
        this->testa = this->testa->succ;
        this->testa->prec=nullptr;
        delete nd;
    }
    else{
        
        nd = this->testa->succ;
        while((nd!=nullptr)&&(nd->valore!= val)){
            nd = nd->succ;
        }

        if(nd!=nullptr){
            if(nd->succ==nullptr)
                nd->prec->succ = nullptr;
            else {
                nd->prec->succ = nd->succ;
                nd->succ->prec = nd->prec;
            }
            
            delete nd;
        }
        else
            cout << "Elemento non presente nella lista." << endl;

    }
}

int main(){

    Lista lista;

return 0;
}
