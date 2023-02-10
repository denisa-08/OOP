#include <string.h>
#include "service.h"

/*int AddElem2(agentie_t* ag, char* tip, int suprafata, char* adresa, int pret)
{
    oferta off = init_oferta(tip, suprafata, adresa, pret);
    int succ = validate_oferta(off);
    if (succ != 0) {
        destroy_oferta(off);
        return succ;
    }
    add_elem(ag, off);
    return 0; // all ok

}*/

RealEstate createRealEstate(){
    RealEstate rez;
    rez.allOffers = init_agentie((DestroyFct) destroy_oferta);
    rez.undoList = init_agentie((DestroyFct) destroy_agentie);
    return rez;
}

void destroyRealEstate(RealEstate* re){
    destroy_agentie(re->allOffers);
    destroy_agentie(re->undoList);
}

int AddElem(RealEstate* re, char* tip, int suprafata, char* adresa, int pret)
{
    oferta off = init_oferta(tip, suprafata, adresa, pret);
    int succ = validate_oferta(off);
    if (succ != 0) {
        destroy_oferta(off);
        return succ;
    }
    agentie_t* toUndo = copylist(re->allOffers, (CopyFct) copyelem);
    add_elem(re->allOffers, off);
    //add to undo list
    add_elem(re->undoList, toUndo);
    return 0; // all ok
}

/*
 * Restore previous offer list
 * return 0 on ok, 1 if there is no more available undo
 */
int undo(RealEstate* re) {
    if (get_len(re->undoList) == 0) {
        return 1; //no more undo
    }
    agentie ag = removeLast(re->undoList);
    destroy_agentie(re->allOffers);
    re->allOffers = ag;
    return 0;
}

/*int DelElem(agentie_t* ag, char* tip, int suprafata, char* adresa, int pret)
{
    oferta off = init_oferta(tip, suprafata, adresa, pret);
    int poz = find_elem(ag, off);
    if (poz == -1) return poz;

    delete_elem_at(ag, poz);
    return 0; //all ok
}*/

int DelElem(RealEstate* re, char* tip, int suprafata, char* adresa, int pret)
{
    oferta off = init_oferta(tip, suprafata, adresa, pret);
    int poz = find_elem(re->allOffers, off);
    if (poz == -1) return poz;

    agentie_t* toUndo = copylist(re->allOffers, (CopyFct) copyelem);
    delete_elem_at(re->allOffers, poz);
    add_elem(re->undoList, toUndo);
    return 0; //all ok
}

/*int Update(agentie_t* ag, oferta of, oferta new_of)
{
    int succ = validate_oferta(new_of);
    if (succ != 0) {
        destroy_oferta(of);
        return -2;
    }
    int poz = find_elem(ag, of);
    if (poz == -1) return poz;

    update_elem(ag, of, new_of);
    return 0; //all ok
}*/

int Update(RealEstate* re, oferta of, oferta new_of)
{
    int succ = validate_oferta(new_of);
    if (succ != 0) {
        destroy_oferta(of);
        return -2;
    }
    agentie_t* toUndo = copylist(re->allOffers, (CopyFct) copyelem);
    int poz = find_elem(re->allOffers, of);
    if (poz == -1) return poz;

    update_elem(re->allOffers, of, new_of);
    add_elem(re->undoList, toUndo);

    return 0; //all ok
}

agentie_t* getAllOfferts(RealEstate* re, char* typeSubstring) {
    if (typeSubstring == NULL || strlen(typeSubstring) == 0) {
        return copylist(re->allOffers, (CopyFct) copyelem);
    }
    agentie_t* rez = init_agentie((DestroyFct) destroy_oferta);
    for (int i = 0; i < get_len(re->allOffers); i++) {
        oferta_t* of = get_elem_at(re->allOffers, i);
        if (strstr(of->tip, typeSubstring) != NULL) {
            add_elem(rez, copyelem(of));
        }
    }
    return rez;
}

agentie_t* lowerPrice(RealEstate* re, int price){
    agentie_t* rez = init_agentie((DestroyFct) destroy_oferta);
    for(int i = 0; i < get_len(re->allOffers); i++){
        oferta_t* of = get_elem_at(re->allOffers, i);
        if(of->pret < price)
            add_elem(rez, copyelem(of));
    }
    return rez;
}

int cmpPrice(oferta o1, oferta o2) {
    if (o1->pret > o2->pret)
        return 1;
    else if (o1->pret == o2->pret)
        return 0;
    else return -1;
}

int cmpType(oferta o1, oferta o2) {
    return strcmp(o1->tip, o2->tip);
}

void sort_asc(agentie_t* ag, FunctieCompara cmpF) {
    int i, j;
    for (i = 0; i < get_len(ag); i++) {
        for (j = i + 1; j < get_len(ag); j++) {
            oferta o1 = get_elem_at(ag, i);
            oferta o2 = get_elem_at(ag, j);
            oferta aux =copyelem(o1);
            if (cmpF(o1,o2) > 0) {
                //interschimbam
                set_elem_at(ag, o2, i);
                set_elem_at(ag, aux, j);
            }
        }
    }
}

void sort_des(agentie_t* ag, FunctieCompara cmpF) {
    int i, j;
    for (i = 0; i < get_len(ag); i++) {
        for (j = i + 1; j < get_len(ag); j++) {
            oferta o1 = get_elem_at(ag, i);
            oferta o2 = get_elem_at(ag, j);
            oferta aux =copyelem(o1);
            if (cmpF(o1,o2) < 0) {
                //interschimbam
                set_elem_at(ag, o2, i);
                set_elem_at(ag, aux, j);
            }
        }
    }
}

/*void sort_des2(agentie_t* ag, FunctieCompara cmpF) {
    int i, j, imax;
    oferta maxim;
    for (i = 0; i < get_len(ag) - 1; i++) {
        maxim = ag->elem[i];
        imax = i;
        for (j = i + 1; j < get_len(ag); j++)
        {
            oferta o1 = get_elem_at(ag, imax);
            oferta o2 = get_elem_at(ag, j);
            if (cmpF(o1, o2) < 0) {
                maxim = ag->elem[j];
                imax = j;
            }
        }
        oferta o1 = get_elem_at(ag, i);
        oferta aux = copyelem(o1);
        set_elem_at(ag, maxim, i);
        set_elem_at(ag, aux, imax);
    }
}*/

agentie_t* sort_by_price(agentie_t* ag) {
    agentie_t* l = copylist(ag, (CopyFct) copyelem);
    sort_asc(l, cmpPrice);
    return l;
}

agentie_t* sort_by_type(agentie_t* ag) {
    agentie_t* l = copylist(ag, (CopyFct) copyelem);
    sort_des(l, cmpType);
    return l;
}

agentie_t* sort_price_des(agentie_t* ag){
    agentie_t* l = copylist(ag, (CopyFct) copyelem);
    sort_des(l, cmpPrice);
    return l;
}