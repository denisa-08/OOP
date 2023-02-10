#include <stdlib.h>

#include "agentie.h"
#include "oferta.h"

agentie_t* init_agentie(DestroyFct f) {
    agentie_t* ag= malloc(sizeof(agentie_t));
    ag->len = 0;
    ag->cap = 2;
    //ag->elem = malloc(200 * sizeof(ElemType));
    //for (int i = 0; i < 200; i++) {
       // ag->elem[i] = init_oferta(" ", 0, " ", 0);
   // }
    ag->elem = malloc(sizeof(oferta_t)*ag->cap);
    ag->dfnc = f;
    return ag;
}

void resize(agentie_t* ag) {
    int nCap = 2 * ag->cap;
    ElemType* nElems = malloc(nCap * sizeof(ElemType));
    //copiez din vectorul existent
    int i;
    for (i = 0; i < ag->len; i++) {
        nElems[i] = ag->elem[i];
    }
    //dealocam memoria ocupata de vector
    free(ag->elem);
    ag->elem = nElems;
    ag->cap = nCap;
}

/*void resize(agentie_t* ag){
    if(ag->len < ag->cap)
        return; //we have room
    //alocate more memory
    ElemType* nElems = malloc(sizeof(ElemType)*(ag->cap + 2));
    //copy elems
    for(int i = 0; i< ag->len; i++) {
        nElems[i] = ag->elem[i];
    }
    //dealocate old vector
    free(ag->elem);
    ag->elem = nElems;
    ag->cap += 2;
}*/

int get_len(agentie_t* ag) {
    return ag->len;
}

ElemType get_elem_at(agentie_t* ag, int poz) {
    return ag->elem[poz];
}

/*void set_len(agentie_t* ag, int len) {
    ag->len = len;
}*/

void set_elem_at(agentie_t* ag, ElemType off, int poz) {
    set_oferta(ag->elem[poz], off);
}

int find_elem(agentie_t* ag, ElemType off) {
    for (int i = 0; i < ag->len; i++) {
        if (cmp_oferta(off, get_elem_at(ag, i)) == 1) {
            return i;
        }
    }
    return -1;
}

/*void add_elem(agentie_t* ag, ElemType off) {
    if (ag->len == ag->cap) {
        resize(ag);
    }
    set_elem_at(ag, off, ag->len);
    set_len(ag, ag->len + 1);
}*/

void add_elem(agentie_t* ag, ElemType off) {
    resize(ag);
    ag->elem[ag->len] = off;
    ag->len++;
}

void update_elem(agentie_t* ag, ElemType off, ElemType new_of)
{
    int poz = find_elem(ag, off);
    if (poz != -1)
        set_elem_at(ag, new_of, poz);
}

/*void delete_elem_at(agentie_t* ag, int poz) {
    for (int i = poz; i < ag->len - 1; i++) {
        set_elem_at(ag, ag->elem[i + 1], i);
    }
    set_len(ag, ag->len - 1);
}*/
void delete_elem_at(agentie_t* ag, int poz) {
    for (int i = poz; i < ag->len - 1; i++) {
        ag->elem[i] = ag->elem[i+1];
    }
    ag->len--;
}

void destroy_agentie(agentie_t* ag) {
    for (int i = 0; i < ag->len; i++) {
        //destroy_oferta(ag->elem[i]);
        ag->dfnc(ag->elem[i]);
    }
    free(ag->elem);
    free(ag);
}

/*agentie_t* copyList(agentie_t* ag)
{
    agentie_t* copyl = init_agentie(ag->dfnc);
    for (int i = 0; i < get_len(ag); i++) {
        oferta of=get_elem_at(ag, i);
        add_elem(copyl, of);
    }
    return copyl;
}*/

agentie_t* copylist(agentie_t* ag, CopyFct cf){
    agentie_t* rez = init_agentie(ag->dfnc);
    for(int i = 0; i < get_len(ag); i++){
        ElemType off = get_elem_at(ag, i);
        add_elem(rez, cf(off));
    }
    return rez;
}

ElemType removeLast(agentie_t* ag){
    ElemType rez = ag->elem[ag->len - 1];
    ag->len -= 1;
    return rez;
}


