//
// Created by Denisa on 06.04.2022.
//

#pragma once
#define INITIAL_CAPACITY 5
#include "Errors.h"
//template <typename Element>
//class IteratorVector;

template <typename Element>
class TemplateVector
{
private:
    int lg;//numar elemente
    int cap;//capacitate
    Element* elems;//elemente

    void ensureCapacity();

public:
    /*
    Constructor default
    Alocam loc pentru 5 elemente
    */
    TemplateVector();

    /*
    Constructor de copiere
    */
    TemplateVector(const TemplateVector& ot);

    /*
    Eliberam memoria
    */
    ~TemplateVector();

    /*
     * Operator assignment
     */
    void operator=(const TemplateVector& ot);


    void add(const Element& el);

    void erase(int poz);

    void exchange(int poz1, int poz2);

    Element& get(int poz) const;

    void set(int poz, const Element& el);

    int size() const noexcept;

    //friend class IteratorVectorT<ElementT>;
    //functii care creaza iteratori
    //IteratorVectorT<ElementT> begin();
    //IteratorVectorT<ElementT> end();
};

/*
Constructor default
Alocam loc pentru 5 elemente
*/
template<typename Element>
TemplateVector<Element>::TemplateVector() :elems{ new Element[INITIAL_CAPACITY] }, cap{ INITIAL_CAPACITY }, lg{ 0 } {}

/*
Constructor de copiere
Obiectul current (this) acum se creaza
aloca spatiu pentru elemente
copiaza elementele din ot in this
*/
template<typename Element>
TemplateVector<Element>::TemplateVector(const TemplateVector<Element>& ot) {
    elems = new Element[ot.cap];
    //copiez elementele
    for (int i = 0; i < ot.lg; i++) {
        elems[i] = ot.elems[i];  //assignment din Book
    }
    lg = ot.lg;
    cap = ot.cap;
}

/*
Operator assignment
elibereaza ce era in obiectul curent (this)
aloca spatiu pentru elemente
copieaza elementele din ot in this
*/
template<typename Element>
void TemplateVector<Element>::operator=(const TemplateVector& ot) {
    delete[] elems;
    cap = ot.cap;
    lg = ot.lg;
    elems = new Element[cap];
    for(int i=0; i<lg; i++)
        elems[i] = ot.elems[i];
}

/*
Eliberam memoria
*/
template<typename Element>
TemplateVector<Element>::~TemplateVector() {
    delete[] elems;
}

template<typename Element>
void TemplateVector<Element>::add(const Element& el) {
    ensureCapacity();//daca e nevoie mai alocam memorie
    elems[lg++] = el;
}

/*
 * Returnam elementul de pe pozitia poz
 */
template<typename Element>
Element& TemplateVector<Element>::get(int poz) const {
    return elems[poz];
}

/*
 * Seteaza elementul de pe pozitia poz cu el
 */
template<typename Element>
void TemplateVector<Element>::set(int poz, const Element& el) {
    elems[poz] = el;
}

template<typename Element>
int TemplateVector<Element>::size() const noexcept {
    return lg;
}

template<typename Element>
void TemplateVector<Element>::ensureCapacity() {
    if (lg < cap) {
        return; //mai avem loc
    }
    cap *= 2;
    Element* aux = new Element[cap];
    for (int i = 0; i < lg; i++) {
        aux[i] = elems[i];
    }
    delete[] elems;
    elems = aux;
}

template<typename Element>
void TemplateVector<Element>::erase(int poz) {
    if(poz < 0 || poz >= lg) throw Exception("In afara limitelor!\n");
    for(int i=poz; i<lg-1; i++) {
        elems[i] = elems[i+1];
    }
    lg--;
}

template<typename Element>
void TemplateVector<Element>::exchange(int poz1, int poz2) {
    if(poz1 < 0 || poz1 >= lg) throw Exception("In afara limitelor!\n");
    if(poz2 < 0 || poz2 >= lg) throw Exception("In afara limitelor!\n");
    swap(elems[poz1], elems[poz2]);
}
/*
template<typename ElementT>
IteratorVectorT<ElementT> VectDinNewDeleteT<ElementT>::begin()
{
    return IteratorVectorT<ElementT>(*this);
}

template<typename ElementT>
IteratorVectorT<ElementT> VectDinNewDeleteT<ElementT>::end()
{
    return IteratorVectorT<ElementT>(*this, lg);
}


template<typename ElementT>
class IteratorVectorT {
private:
    const VectDinNewDeleteT<ElementT>& v;
    int poz = 0;
public:
    IteratorVectorT(const VectDinNewDeleteT<ElementT>& v) noexcept;
    IteratorVectorT(const VectDinNewDeleteT<ElementT>& v, int poz)noexcept;
    bool valid()const;
    ElementT& element() const;
    void next();
    ElementT& operator*();
    IteratorVectorT& operator++();
    bool operator==(const IteratorVectorT& ot)noexcept;
    bool operator!=(const IteratorVectorT& ot)noexcept;
};

template<typename ElementT>
IteratorVectorT<ElementT>::IteratorVectorT(const VectDinNewDeleteT<ElementT>& v) noexcept:v{ v } {}

template<typename ElementT>
IteratorVectorT<ElementT>::IteratorVectorT(const VectDinNewDeleteT<ElementT>& v, int poz)noexcept : v{ v }, poz{ poz } {}

template<typename ElementT>
bool IteratorVectorT<ElementT>::valid()const {
    return poz < v.lg;
}

template<typename ElementT>
ElementT& IteratorVectorT<ElementT>::element() const {
    return v.elems[poz];
}

template<typename ElementT>
void IteratorVectorT<ElementT>::next() {
    poz++;
}

template<typename ElementT>
ElementT& IteratorVectorT<ElementT>::operator*() {
    return element();
}

template<typename ElementT>
IteratorVectorT<ElementT>& IteratorVectorT<ElementT>::operator++() {
    next();
    return *this;
}

template<typename ElementT>
bool IteratorVectorT<ElementT>::operator==(const IteratorVectorT<ElementT>& ot) noexcept {
    return poz == ot.poz;
}

template<typename ElementT>
bool IteratorVectorT<ElementT>::operator!=(const IteratorVectorT<ElementT>& ot)noexcept {
    return *this != ot;
}*/

void test_dynamic_vector();
