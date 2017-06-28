#include <iostream>
#include<algorithm>
#include<stdexcept>
using namespace std;

template<typename T>
class Vector{
public:

class Constiterator;
class Iterator;
 using value_type = T;
 using size_type = size_t;
 using difference_type = ptrdiff_t;
 using reference = T&;
 using const_reference = const T&;
 using pointer = T*;
 using const_pointer = const T*;
 using iterator = Iterator;
 using const_iterator = Constiterator;


private:
size_t max_sz;
size_t sz;
T* values;
mutable int anz;

//Vergroesserung von Kapazitaet
void reserve(size_t new_len){
if(new_len<max_sz) throw runtime_error("Falsch");

T *new_array = new T [new_len];
for (size_t i{0}; i<sz; i++)
    new_array[i]=values[i];

    delete[]values;
    values=new_array;
    this->max_sz=new_len;
}

public:

 Vector(): max_sz {0}, sz {0},anz{0}, values {nullptr} {}

 Vector (size_t max_sz): max_sz{max_sz}, sz {0},anz{0}, values {max_sz>0?new T [max_sz]: nullptr} {}

/**  zweiter Konstruktor
Vector:: Vector (size_t max_sz) {
this->max_sz=max_sz;
this->sz=0;
if(max_sz>0)
    values = new T[max_sz];
else
    values= nullptr;

}
**/

 Vector (initializer_list <T> il) {
values=il.size()>0? new T [il.size ()]: nullptr;
max_sz=il.size();
sz=0;
anz=0;
for (const auto& elem : il) values [sz++]= elem;
}

//Kopierkonstruktor
 Vector(const Vector &right){
size_t i=0;
values = new T[right.max_sz];
for (i=0; i<right.sz; i++){
        this->values[i]=right.values[i];
}
sz=i;
this->max_sz=right.max_sz;
}

Vector(Vector&& src) { 
values=src.values;
sz=src.sz;
max_sz=src.max_sz;
src.values=nullptr;
src.sz=src.max_sz=0;
}


//Destruktor
 ~Vector (){
delete [] values;
}

//Liefert die Groesse des Vektors zurueck.
size_t  size()const{
return sz;
}

//Ueberpruef, ob ein Vektor leer ist oder nicht.
bool  empty(){
if(sz==0)
    return true;
else return false;
}


void  clear(){
sz=0;
}


//Verkleinerung der Kapazitaet
void shrink_to_fit(size_t new_size){
    try{
if(new_size>=0 && new_size<max_sz){

max_sz=new_size;

}else{
   throw runtime_error("Nicht passende Groesse");
}

if(sz>new_size) sz=new_size;

T* new_array=new T[max_sz];
for(size_t i=0; i<sz; i++){
    new_array[i]=values[i];
}
    delete[]values;
    values=new_array;
    }catch(...){
    cout << "Nicht passende Groesse" << endl;
    }

}

//Vergroesserung um eine Stelle
void push_back(T wert){
if(sz==max_sz){
    if(max_sz>0){
    reserve(max_sz*2);
        }else{
            max_sz=2;
            reserve(max_sz*2);
        }

    }
values[sz]=wert;
sz=sz+1;
}

//Verkuerzung um eine Stelle
void pop_back(){
    if(sz>0)
sz=sz-1;
}


T&  operator[](size_t index){
if (sz==0) throw runtime_error("Empty vector");
if (index>sz-1) throw runtime_error("Empty vector");
if(index%2==0) anz++;
return values[index];
}


const T&  operator[](size_t index)const{
if (sz==0) throw runtime_error("Empty vector");
if (index>sz-1) throw runtime_error("Empty vector");
anz--;
return values[index];
}

int count(){
if(anz>3||anz<(-3)) throw runtime_error("counter! normal");
return anz;
}

int count()const{
if(anz>3||anz<(-3)) throw runtime_error("counter! const");
return anz;
}


//Ueberladung vom Operatror =
Vector<T>&  operator= (const Vector& src){
if(this==&src)
    return *this;
delete[] this->values;
size_t i=0;
this->values = new T[src.max_sz];
for (i=0; i<src.sz; i++){
        this->values[i]=src.values[i];
}
this->sz=src.sz;
this->max_sz=src.max_sz;
return *this;
}
Vector& operator=(Vector&& rhs) {
delete[] values;
values=rhs.values;
sz=rhs.sz;
max_sz=rhs.max_sz;
rhs.values=nullptr;
rhs.sz=rhs.max_sz=0;
}



 class Iterator {
   T* ptr;
   Vector<T> *v;
	
 public:
 using value_type = Vector::value_type;
 using difference_type = Vector::difference_type;
 using reference = Vector::reference;
 using pointer = Vector::pointer;
 using iterator_category = std::forward_iterator_tag;

//Konstruktor eines Iterators 2
Iterator(T* new_iterator, Vector* new_vector) {
this->ptr=new_iterator;
this->v=new_vector;
}


//Ueberladung von operator ++
const Iterator& operator++() {
        if(ptr>=((*v).end()).ptr) throw runtime_error ("Out of bounds");
        this->ptr=this->ptr+1;
    return *this;
}

//Ueberladung von operator !=
bool operator!=(const Iterator& src)const{
if(this->ptr==src.ptr)
    return false;
else
    return true;
}

//Ueberladung von operator *
T& operator*(){
    if(ptr>=((*v).end()).ptr) throw runtime_error ("Out of bounds");
return *ptr;
}

//Ueberladung von operator *
const T& operator*() const{
    if(ptr>=((*v).end()).ptr) throw runtime_error ("Out of bounds");
return *ptr;
}


bool operator==(const Iterator& src)const{
if(this->ptr==src.ptr)
    return true;
else
    return false;
}

Iterator operator++(int){
Iterator old{*this};
++*this;
return old;
}

//Retouniert den Poniter, wohin Iterator zeigt.

const T* operator->(){
    return ptr;
}

operator Constiterator(){
            return Constiterator(ptr, v);
        }


 };



 class Constiterator {
   T* ptr;
   const Vector<T> *v;
 public:
 using value_type = Vector::value_type;
 using difference_type = Vector::difference_type;
 using reference = Vector::reference;
 using pointer = Vector::pointer;
 using iterator_category = std::forward_iterator_tag;

Constiterator(T* new_iterator, const Vector* new_vector){
this->ptr=new_iterator;
this->v=new_vector;
}


Constiterator& operator++() {
    if(ptr>=((*v).end()).ptr) throw runtime_error ("Out of bounds");
    this->ptr=this->ptr+1;      //aufg1: ptr-1
    return *this;
}

bool operator!=(const Constiterator& src)const{
if(this->ptr==src.ptr)
    return false;
else
    return true;
}


const T&  operator*() const{
    if(ptr>=((*v).end()).ptr) throw runtime_error ("Out of bounds");
return *ptr;
}


const T& operator*() {
    if(ptr>=((*v).end()).ptr) throw runtime_error ("Out of bounds");
return *ptr;
}


bool operator==(const Constiterator& src)const{
if(this->ptr==src.ptr)
    return true;
else
    return false;
}

//Operator ++
Constiterator operator++(int){
Constiterator old{*this};
++*this;
return old;
}


const T* operator->(){
    return ptr;
}

friend difference_type operator-(const Vector::Constiterator& lop,
 const Vector::Constiterator& rop) {
 return lop.ptr-rop.ptr;
}

};



/** Iterator **/

//Vektor+Iterator
Iterator begin() {return Iterator(values, this);}
Iterator end(){return Iterator (values+sz,this);}
Constiterator begin() const {return Constiterator(values, this);}
Constiterator end() const {return Constiterator (values+sz, this);}

//Position loeschen
iterator erase(const_iterator pos) {
 auto diff = pos-begin();
 if (diff<0 || static_cast<size_type>(diff)>=sz)
 throw runtime_error("Iterator out of bounds");
 size_type current{static_cast<size_type>(diff)};
 for (; current<sz-1; ++current)
 values[current]=values[current+1];
 --sz;
 return iterator{values+current, this};
}

/*
*/
//Insert (Zahl einfuegen)

iterator insert(const_iterator pos,
 Vector<T>::const_reference val) {
 auto diff = pos-begin();
 if (diff<0 || static_cast<size_type>(diff)>sz)
 throw runtime_error("Iterator out of bounds");
 size_type current{static_cast<size_type>(diff)};
 if (sz>=max_sz)
 reserve(max_sz*2+10);
for (size_type i{sz}; i-->current; )
  values[i+1] = values[i];
 values[current]=val;
 ++sz;
 return iterator{values+current, this};
 }






ostream& print(ostream& o)const {
    o<<"[";
    for(size_t i=0; i<sz; i++)
    if(i==sz-1){
    o << values[i];
    }else{
	o << values[i] << ",";
    }
    o<<"]";

	return o;
}



};



template<typename T>
ostream& operator<<(ostream& o, const Vector<T>& t) {
	return t.print(o);
}

























/** Aufgaben:




**/
