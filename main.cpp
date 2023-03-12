#include <iostream>
#include <memory>
#include <new>
#include <cstring>
#include <stdlib.h>
using namespace std;

int sstrlen(const char *x){
    return (int)strlen(x);
}

class comanda{
    char *id;
    int suma;
    char *descriere;
public:
    comanda(){
        id = nullptr;
        descriere = nullptr;
        suma = 0;
    }
    comanda(const char *id_com, const int suma_com, const char *descriere_com) {
        id = new char[sstrlen(id_com) + 1];
        descriere = new char[sstrlen(descriere_com) + 1];
        suma = suma_com;
        for (int i = 0; i < sstrlen(id_com); i++) {
            id[i] = id_com[i];
        }
        id[sstrlen(id_com)] = '\0';
        for (int i = 0; i < sstrlen(descriere_com); i++) {
            descriere[i] = descriere_com[i];
        }
        descriere[sstrlen(descriere_com)] = '\0';
    }
    comanda(const comanda &aux){
        id = new char[sstrlen(aux.getId()) + 1];
        descriere = new char[sstrlen(aux.getDescriere()) + 1];
        suma = aux.getSuma();
        for (int i = 0; i < sstrlen(aux.getId()); i++) {
            id[i] = aux.getId()[i];
        }
        id[sstrlen(aux.getId())] = '\0';
        for (int i = 0; i < sstrlen(aux.getDescriere()); i++) {
            descriere[i] = aux.getDescriere()[i];
        }
    }
    friend std::ostream& operator<<(ostream& os, const comanda& a){
        if(a.getId() != nullptr)
            os << a.getId() << "\n" << a.getSuma() << "\n" << a.getDescriere() << "\n";
        return os;
    }

    friend std::istream& operator>>(istream& is, comanda &a){
        char *idd = new char [100];
        cout<<"Id:\n";
        is.getline(idd, 99);
        is.get();
        int s;
        cout<<"Suma:\n";
        is >> s;
        char *desc = new  char [500];
        cout<<"Descriere:\n";
        is.getline(desc, 499);
        is.get();
        a.act_id(idd);
        a.schimba_comanda(desc, s);
        return is;
    }
    ~comanda(){
        if(id)
            delete[] id;
        if(descriere)
            delete[] descriere;
    }
    comanda& operator =(const comanda &aux){
        this -> id = aux.getId();
        this -> descriere = aux.getDescriere();
        this -> suma = aux.getSuma();
        return *this;
    }
    void schimba_comanda(const char *descriere_schimb, const int suma_schimb){
        delete [] descriere;
        descriere = new char [sstrlen(descriere_schimb)+1];
        for(int i = 0; i < sstrlen(descriere_schimb); i++){
            descriere[i] = descriere_schimb[i];
        }
        suma = suma_schimb;
    }
    void schimba_suma(const int suma_schimb){
        suma = suma_schimb;
    }
    void act_id(const char *id_nou){
        delete [] id;
        id = new char [sstrlen(id_nou)+1];
        for(int i = 0;i < sstrlen(id_nou); i++){
            id[i]  = id_nou[i];
        }
    }
    char* getDescriere() const{
        return descriere;
    }
    char *getId() const{
        return id;
    }
    int getSuma() const{
        return suma;
    }
    bool operator ==(const comanda &aux) const{
        if(strcmp(aux.getId(), this -> id) == 0){
            return true;
        }
        return false;
    }
    comanda operator +(const comanda &aux){
        char * ndescriere = new char [sstrlen(this->getDescriere())+sstrlen(aux.getDescriere())+4];
        int k = 0;
        for(int i = 0;i < sstrlen(this -> getDescriere()); i++){
            ndescriere[i] = (this -> getDescriere())[i];
            k++;
        }
        ndescriere[k] = ' ';
        ndescriere[k+1] = '+';
        ndescriere[k+2] = ' ';
        k += 3;
        for(int i = 0;i < sstrlen(aux.getDescriere()); i++){
            ndescriere[k] = (aux.getDescriere())[i];
            k++;
        }
        int nsuma = this -> getSuma() + aux.getSuma();
        char * nid = new char [sstrlen(this->getId()) + sstrlen(aux.getId()) + 2];
        int idk = 0;
        for(int i = 0;i < sstrlen(this -> getId()); i++){
            nid[i] = (this -> getId())[i];
            idk++;
        }
        nid[idk] = ' ';
        nid[idk+1] = '+';
        nid[idk+2] = ' ';
        idk += 3;
        for(int i = 0;i < sstrlen(aux.getId()); i++) {
            ndescriere[idk] = (aux.getId())[i];
            idk++;
        }
        comanda rez(nid, nsuma, ndescriere);
        return rez;
    }
    bool operator >(const comanda &aux) const{
        return this->getSuma() > aux.getSuma();
    }
};

struct cnod{
    comanda el;
    cnod *next = nullptr;
};

class vcomanda{
    cnod *start;
    cnod *end;
public:
    vcomanda(){
        start = nullptr;
        end = nullptr;
    }
    explicit vcomanda(const comanda &nel){
        start = new cnod;
        start -> el = nel;
        start -> next = nullptr;
        end = start;
    }
    vcomanda(const vcomanda &i){
        start = i.getStart();
        end = i.getEnd();
    }
    ~vcomanda(){
        if(start != nullptr){
            cnod *i = start,*t = i -> next;
            while(i -> next != nullptr){
                delete i;
                i = t;
                t = i -> next;
            }
            start = nullptr;
        }
    }
    void append(comanda &nel)
    {
        if(start)///daca am alocat deja memorie pentru prima pozitie din lista, adica am inceputa lista
        {
            cnod *aux = new cnod;
            aux=new cnod; ///alocam memorie pentru un nod nou
            aux->el=nel;
            end->next=aux;
            end=aux;
            end->next=NULL;
        }
        else
        {
            start=new cnod;
            start->el=nel;
            start->next=NULL;
            end = start;
        }
    }
    /*void append(comanda &nel){
        cnod *aux = new cnod;
        if(end == nullptr){
            start = new cnod;
            start -> el = nel;
            start -> next = nullptr;
            end = start;
        }
        else
        {
            end -> next = aux;
            aux -> el = nel;
            aux -> next = nullptr;
            end = aux;
        }
    }*/
    cnod* getStart() const{
        return start;
    }
    cnod* getEnd() const{
        return end;
    }
    void setStart(const vcomanda &aux){
        start = aux.getStart();
    }
    void setEnd(const vcomanda &aux){
        end = aux.getEnd();
    }
    vcomanda& operator =(const vcomanda &aux){
        this -> start = aux.start;
        this -> end = aux.end;
        return *this;
    }
    vcomanda operator +(const vcomanda &aux) const{
        vcomanda rez;
        cnod *t = this -> getEnd();
        t -> next = aux.getStart();
        rez.setStart(*this);
        rez.setEnd(aux);
        return rez;
    }
    friend std::ostream& operator<<(ostream& os, const vcomanda& a){
        cnod *i = a.getStart();
        while(i != nullptr){
            os << i -> el << "\n";
            i = i -> next;
        }
        return os;
    }
    friend std::istream& operator>>(istream& is, vcomanda &a){
        cout<<"Numarul de elemente:\n";
        int n;
        is >> n;
        while(n){
            comanda aux;
            is >> aux;
            a.append(aux);
            n--;
        }
        return is;
    }
};


class masina{
    char *culoare;
    char *vin;
    int capacitate_motor;
    char *firma;
    int impozit;
    vcomanda comenzi;

public:
    masina(char *cul, char *v, int mot, char *firm, int imp, vcomanda &ncomenzi){
        culoare = new char [sstrlen(cul)+1];
        vin = new char [sstrlen(vin)+1];
        firma = new char [sstrlen(firm)+1];
        for(int i = 0;i < sstrlen(cul); i++){
            culoare[i] = cul[i];
        }
        for(int i = 0;i < sstrlen(v); i++){
            vin[i] = v[i];
        }
        for(int i = 0;i < sstrlen(firm); i++){
            firma[i] = firm[i];
        }
        capacitate_motor = mot;
        impozit = imp;
        comenzi = ncomenzi;
    }
    masina(){
        culoare = nullptr;
        vin = nullptr;
        firma = nullptr;
        capacitate_motor = 0;
        impozit = 0;
    }
    masina(masina &aux){
        culoare = aux.getCuloare();
        vin = aux.getVin();
        firma = aux.getFirma();
        capacitate_motor = aux.getCapacitate();
        impozit = aux.getImpozit();
        comenzi = aux.getComenzi();
    }
    ~masina(){
        if(culoare)
            delete [] culoare;
        if(vin)
            delete [] vin;
        if(firma)
            delete [] firma;
        ///cum pot dealoca comenzi doar daca am comenzi.getStart() != nullptr ??
    }
    masina& operator =(masina &aux){
        this -> culoare = aux.getCuloare();
        this -> vin = aux.getVin();
        this -> firma = aux.getFirma();
        this -> capacitate_motor = aux.getCapacitate();
        this -> impozit = aux.getImpozit();
        this -> comenzi = aux.getComenzi();
        return *this;
    }
    char* getCuloare() const{
        return culoare;
    }
    char* getVin() const{
        return vin;
    }
    char* getFirma() const{
        return firma;
    }
    int getCapacitate() const{
        return capacitate_motor;
    }
    int getImpozit() const{
        return impozit;
    }
    vcomanda getComenzi(){
        return comenzi;
    }
    void setCuloare(const char *ncolor){
        delete [] culoare;
        culoare = new char [sstrlen(ncolor) + 1];
        for(int i = 0; i < sstrlen(ncolor); i++){
            culoare[i] = ncolor[i];
        }
        culoare[sstrlen(ncolor)] = '\0';
    }
    void setVin(const char *nvin){
        delete [] vin;
        vin = new char [sstrlen(nvin) + 1];
        for(int i = 0;i < sstrlen(nvin); i++){
            vin[i] = nvin[i];
        }
        vin[sstrlen(nvin) + 1] = '\0';
    }
    void setFirma(const char *nfirm){
        delete [] firma;
        firma = new char [sstrlen(nfirm) + 1];
        for(int i = 0;i < sstrlen(nfirm); i++){
            firma[i] = nfirm[i];
        }
        firma[sstrlen(nfirm) + 1] = '\0';
    }
    void setCapacitate(const int ncap){
        capacitate_motor = ncap;
    }
    void setComenzi(const vcomanda ncom){
        comenzi = ncom;
    }
    void setImpozit(const int nimp){
        impozit = nimp;
    }
    friend std::ostream& operator<<(ostream& os, masina& a){
        os << a.getVin() << "\n" << a.getFirma() << "\n" << a.getCuloare() << "\n" << a.getCapacitate()
           << "\n"<< a.getImpozit() << "\n" << a.getComenzi() << "\n";
        return os;
    }
    friend std::istream& operator>>(istream& is, masina &a){
        cout << "Vin:\n";
        char *v = new char[100];
        is.getline(v, 99);
        is.get();
        cout<<"Firma:\n";
        char *f = new char[100];
        is.getline(f, 99);
        is.get();
        char *cul = new char [100];
        cout<<"Culoare:\n";
        is.getline(cul, 99);
        is.get();
        cout<<"Capacitate motor:\n";
        int cap;
        is >> cap;
        int nimp;
        cout<<"Impozit:\n";
        is >> nimp;
        cout<<"Comenzi:\n";
        vcomanda aux;
        is >> aux;
        masina tp(cul, v, cap, f, nimp, aux);
        a = tp;
        return is;
    }

};

masina m[5];
vcomanda c[5];
int im = 0, ic = 0;

void nwin(){
    cout<<"\nProiect realizat de Gherca Darius\n\n";
}
void mmodifica(masina &a, int index){
    system("cls");
    nwin();
    int n = 1;
    do{
        cout<<"Optiuni masina numarul "<<index<<"\n";
        cout<<"1. Afisare culoare\n";
        cout<<"2. Modificare culoare\n";
        cout<<"3. Afisare VIN\n";
        cout<<"4. Modificare VIN\n";
        cout<<"5. Afisare firma\n";
        cout<<"6. Modificare firma\n";
        cout<<"7. Afisare capacitate motor\n";
        cout<<"8. Modificare capacitate motor\n";
        cout<<"9. Afisare impozit\n";
        cout<<"10. Modificare impozit\n";
        cout<<"11. Afisare comenzi\n";
        cout<<"12. Modificare comenzi\n";
        cout<<"13. Inapoi\n";
        cin>>n;
        switch(n){
            case 1:
                cout<<a.getCuloare()<<"\n";
                break;
            case 2:
                cout<<"Culoare noua\n";
                char nc[200];
                cin.getline(nc, 199);
                cin.get();
                a.setCuloare(nc);
                break;
            case 3:
                cout<<a.getVin()<<"\n";
                break;
            case 4:
                cout<<"VIN Nou\n";
                char nv[200];
                cin.getline(nv, 199);
                cin.get();
                a.setVin(nv);
                break;
            case 5:
                cout<<a.getFirma()<<"\n";
                break;
            case 6:
                cout<<"Firma noua\n";
                char nf[200];
                cin.getline(nf, 199);
                cin.get();
                a.setFirma(nf);
                break;
            case 7:
                cout<<a.getCapacitate()<<"\n";
                break;
            case 8:
                cout<<"Capacitate noua\n";
                int ncap;
                cin>>ncap;
                a.setCapacitate(ncap);
                break;
            case 9:
                cout<<a.getImpozit()<<"\n";
                break;
            case 10:
                cout<<"Impozit nou\n";
                int nimp;
                cin>>nimp;
                a.setImpozit(nimp);
                break;
            case 11:
                cout<<a.getComenzi()<<"\n";
                break;
            case 12:
                cout<<"Comenzi noi\n";
                vcomanda ncom;
                cin>>ncom;
                a.setComenzi(ncom);
                break;
        }
    }while(n >= 1 && n <= 12);
}
void mmas() {
    system("cls");
    nwin();
    int n = 1, nm = 1;
    do{
        cout<<" Masini\n";
        cout<<"1. Citire masina\n";
        cout<<"2. Afisare masina\n";
        cout<<"3. Stergere masina - Nu merge\n";
        cout<<"4. Optiuni masina\n";
        cout<<"5. Inapoi\n";
        cin>>n;
        switch(n){
            case 1:
                cin>>m[im];
                im++;
                break;
            case 2:
                cout<<"Numar total masini: "<<im<<"\n";
                cout<<"Numarul masinii:\n";
                cin>>nm;
                cout<<m[nm];
                break;
            case 3:
                cout<<"Numar total masini: "<<im<<"\n";
                cout<<"Numarul masinii:\n";
                cin>>nm;
                ///NU MERGE - stergerea m[nm]
                break;
            case 4:
                cout<<"Numar total masini: "<<im<<"\n";
                cout<<"Numarul masinii:\n";
                cin>>nm;
                mmodifica(m[nm], nm);
        }
    }while(n >= 1 && n <= 4);
}
void commod(comanda a){
    system("cls");
    nwin();
    int n = 1;
    char nd[100];
    int ns = 1;
    char nid[100];
    do{
        cout<<"Modificare comanda\n";
        cout<<"1. Schimbare comanda - Descriere si suma\n";
        cout<<"2. Schimba suma\n";
        cout<<"3. Actualizare ID\n";
        cout<<"4. Afisare descriere\n";
        cout<<"5. Afisare ID\n";
        cout<<"6. Afisare suma\n";
        cin>>n;
        switch(n){
            case 1:
                cout<<"Noua descriere:\n";
                cin.getline(nd, 99);
                cin.get();
                cout<<"Noua suma:\n";
                cin>>ns;
                a.schimba_comanda(nd, ns);
                break;
            case 2:
                cout<<"Noua suma:\n";
                cin>>ns;
                a.schimba_suma(ns);
                break;
            case 3:
                cout<<"Noul ID:\n";
                cin.getline(nid, 99);
                cin.get();
                a.act_id(nid);
                break;
            case 4:
                cout<<a.getDescriere()<<"\n";
                break;
            case 5:
                cout<<a.getId()<<"\n";
                break;
            case 6:
                cout<<a.getSuma()<<"\n";
                break;
        }
    }while(n >= 1 && n <= 6);
}
void parcurgere(vcomanda &a){
    system("cls");
    nwin();
    cnod *i = a.getStart();
    int n = 1;
    comanda primul;
    comanda doi;
    while(i != nullptr && n >= 1 && n <= 6){
        cout<<i->el<<"\n";
        cout<<"1. Modificare comanda\n";
        cout<<"2. Combinare cu urmatoarea comanda\n";
        cout<<"3. Egalarea comenzii cu urmatoarea comanda\n";
        cout<<"4. Afisarea comenzii\n";
        cout<<"5. Comparare cu urmatoarea comanda\n";
        cout<<"6. Urmatoarea comanda\n";
        cout<<"7. Iesire\n";
        cin>>n;
        switch(n){
            case 1:
                commod(i->el);
                break;
            case 2:
                primul = (i -> el);
                doi = (i -> next -> el);
                primul = primul + doi;
                i -> el = primul;
                break;
            case 3:
                i -> el = i -> next -> el;
                break;
            case 4:
                cout<<i->el<<"\n";
                break;
            case 5:
                if(i -> el == i -> next -> el){
                    cout<<"Sunt egale\n";
                }
                else if(i -> el > i -> next -> el){
                    cout<<"Mai mare\n";
                }
                else cout<<"Mai mica\n";
                break;
            case 6:
                i++;
                break;
        }
    }
}
void cmodifica(vcomanda &a, int index){
    system("cls");
    nwin();
    int n = 1;
    do{
        cout<<"Modificare comanda "<<index<<"\n";
        cout<<"1. Parcurgere comenzi\n";
        cout<<"2. Afisare prima comanda\n";
        cout<<"3. Afisare ultima comanda\n";
        cout<<"4. Inapoi\n";
        cin>>n;
        switch(n){
            case 1:
                parcurgere(a);
                break;
            case 2:
                cout<<a.getStart()->el<<"\n";
                break;
            case 3:
                cout<<a.getEnd()->el<<"\n";
                break;
        }
    }while(n >= 1 && n <= 3);
}

void mcom(){
    system("cls");
    nwin();
    int n = 1, nc = 1;
    do{
        cout<<"Comenzi\n";
        cout<<"1. Citire comanda\n";
        cout<<"2. Afisare comanda\n";
        cout<<"3. Stergere comanda - Nu merge\n";
        cout<<"4. Modificare comanda\n";
        cout<<"5. Inapoi\n";
        cin>>n;
        switch(n){
            case 1:
                ic++;
                cin >> c[ic];
                break;
            case 2:
                cout<<"Numar total comenzi "<<ic<<"\n";
                cout<<"Numar comanda\n";
                cin>>nc;
                cout<<c[nc];
                break;
            case 3:
                cout<<"Numar total comenzi "<<ic<<"\n";
                cout<<"Numar comanda\n";
                cin>>nc;
                ///NU MERGE - Stergerea lui c[nc]
                /*if(nc >= ic)
                    std::destroy_at(std::addressof(c[nc]));*/
                break;
            case 4:
                cout<<"Numar total comenzi "<<ic<<"\n";
                cout<<"Numar comanda\n";
                cin>>nc;
                cmodifica(c[nc], nc);
                break;
        }

    }while(n >= 1 && n <= 4);
}

int main() {
    ///initializare meniu
    system("cls");
    int n = 1;
    do
    {
        cout<<"Proiect realizat de Gherca Darius"<<"\n\n";
        cout<<"1. Masina"<<"\n";
        cout<<"2. Comanda"<<"\n";
        cin>>n;
        if(n==1)
            mmas();
        else
        if(n==2)
            mcom();
    }while(n<=2 && n>=1);
    return 0;
}
