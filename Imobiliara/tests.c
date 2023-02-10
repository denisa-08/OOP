//
// Created by Denisa on 23.03.2022.
//

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "tests.h"

void test_all() {
    test_oferta();
    test_agentie();
    test_service();
    printf("Testele au trecut!\n");
}

void test_oferta() {
    oferta off1 = init_oferta("teren", 2000, "E123", 100000);
    oferta off2 = init_oferta("casa", 1000, "E124", 50000);
    oferta off3 = init_oferta("apartament", 300, "E125", 20000);
    oferta off4 = init_oferta("teren", 2000, "E128", -5);
    oferta off5 = init_oferta("hotel", 500, "E127", 200000);
    oferta off6 = init_oferta("casa", -1000, "E126", 50000);
    oferta off7 = init_oferta("casa", 1500, "", 40000);

    assert(validate_oferta(off1) == 0);
    assert(validate_oferta(off2) == 0);
    assert(validate_oferta(off3) == 0);
    assert(validate_oferta(off4) == -1);
    assert(validate_oferta(off5) == -2);
    assert(validate_oferta(off6) == -3);
    assert(validate_oferta(off7) == -4);

    assert(strcmp(get_tip(off2), "casa") == 0);
    assert(get_suprafata(off2) == 1000);
    assert(strcmp(get_adresa(off2), "E124") == 0);
    assert(get_pret(off2) == 50000);

    set_oferta(off2, off1);
    assert(strcmp(get_tip(off2), "teren") == 0);
    assert(get_suprafata(off2) == 2000);
    assert(strcmp(get_adresa(off2), "E123") == 0);
    assert(get_pret(off2) == 100000);

    assert(cmp_oferta(off1, off2) == 1);
    assert(cmp_oferta(off1, off3) == 0);

    oferta aux = copyelem(off1);
    assert(cmp_oferta(off1, aux) == 1);

    destroy_oferta(off1);
    destroy_oferta(off2);
    destroy_oferta(off3);
    destroy_oferta(off4);
    destroy_oferta(off5);
    destroy_oferta(off6);
    destroy_oferta(off7);
    destroy_oferta(aux);
}

void test_agentie() {
    agentie_t* ag = init_agentie((DestroyFct) destroy_oferta);
    oferta off1 = init_oferta("teren", 2000, "E123", 100000);
    oferta off2 = init_oferta("casa", 1000, "E124", 50000);
    oferta off3 = init_oferta("apartament", 300, "E125", 20000);

    add_elem(ag, off1);
    add_elem(ag, off2);
    add_elem(ag, off3);

    assert(get_len(ag) == 3);
    assert(cmp_oferta(get_elem_at(ag, 1), off2) == 1);

    delete_elem_at(ag, 1);
    assert(get_len(ag) == 2);
    assert(cmp_oferta(get_elem_at(ag, 1), off3) == 1);

    assert(find_elem(ag, off3) == 1);
    assert(find_elem(ag, off2) == -1);

    update_elem(ag, off1, off2);
    assert(cmp_oferta(get_elem_at(ag,0), off2) == 1);


    destroy_oferta(off1);
    destroy_oferta(off2);
    destroy_oferta(off3);


    agentie_t* list = init_agentie((DestroyFct) destroy_oferta);
    add_elem(list, init_oferta("casa", 1000, "E124", 50000));
    add_elem(list, init_oferta("apartament", 300, "E125", 20000));
    assert(get_len(list) == 2);
    oferta_t* el = removeLast(list);
    assert(get_len(list) == 1);
    destroy_oferta(el);

    el = removeLast(list);
    assert(get_len(list) == 0);
    destroy_oferta(el);

    destroy_agentie(list);


    agentie_t* l = init_agentie((DestroyFct) destroy_oferta);
    add_elem(l, init_oferta("casa", 1000, "E124", 50000));
    add_elem(l, init_oferta("apartament", 300, "E125", 20000));
    agentie_t* l2 = copylist(l, (CopyFct) copyelem);
    assert(get_len(l2) == 2);
    oferta_t* o = get_elem_at(l2, 0);
    assert(strcmp(o->tip, "casa") == 0);
    destroy_agentie(l);
    destroy_agentie(l2);
}

void test_service() {
    RealEstate re = createRealEstate();
    oferta off1 = init_oferta("teren", 2000, "E123", 100000);
    oferta off2 = init_oferta("casa", 1000, "E124", 50000);
    oferta off3 = init_oferta("apartament", 300, "E125", 20000);
    oferta off4 = init_oferta("casa", 900, "E543", 29000);
    oferta off5 = init_oferta("orice", 900, "erhe", 89000);
    oferta off6 = init_oferta("casa", 890, "E45", 20000);

    assert(AddElem(&re, "teren", 2000, "E123", 100000) == 0);
    assert(AddElem(&re, "casa", 1000, "E124", 50000) == 0);
    assert(AddElem(&re, "apartament", 300, "E125", 20000) == 0);
    assert(AddElem(&re, "hotel", 500, "E127", 200000) == -2);

    assert(get_len(re.allOffers) == 3);
    assert(cmp_oferta(get_elem_at(re.allOffers, 1), off2) == 1);

    assert(DelElem(&re, "casa", 1000, "E124", 50000) == 0);
    assert(get_len(re.allOffers) == 2);
    assert(cmp_oferta(get_elem_at(re.allOffers, 1), off3) == 1);
    assert(DelElem(&re, "hotel", 500, "E127", 200000) == -1);

    int up, up2, up3;
    up = Update(&re, off1, off2);
    assert(up == 0);
    assert(cmp_oferta(get_elem_at(re.allOffers,0), off2) == 1);
    up2 = Update(&re, off4, off2);
    assert(up2 == -1);
    up3 = Update(&re, off1, off5);
    assert(up3 == -2);


    assert(cmpPrice(off1, off2) == 1);
    assert(cmpPrice(off3, off2) == -1);
    assert(cmpPrice(off3, off6) == 0);

    assert(cmpType(off2, off6) == 0);


    agentie filtred = getAllOfferts(&re, "casa");
    assert(get_len(filtred) == 1);

    assert(AddElem(&re, "casa", 1000, "E126", 55000) == 0);
    assert(get_len(re.allOffers) == 3);
    agentie filtred1 = getAllOfferts(&re, "casa");
    assert(get_len(filtred1) == 2);
    destroy_agentie(filtred1);
    destroy_agentie(filtred);


    RealEstate re2 = createRealEstate();
    AddElem(&re2, "teren", 2000, "E123", 100000);
    AddElem(&re2, "casa", 1000, "E124", 50000);
    undo(&re2);
    agentie_t* l = getAllOfferts(&re2, NULL);
    assert(get_len(l) == 1);
    destroy_agentie(l);

    undo(&re2);
    l = getAllOfferts(&re2, NULL);
    assert(get_len(l) == 0);
    destroy_agentie(l);

    assert(undo(&re2) != 0);
    assert(undo(&re2) != 0);
    assert(undo(&re2) != 0);

    destroyRealEstate(&re2);



    RealEstate re3 = createRealEstate();
    AddElem(&re3, "teren", 2000, "E123", 100000);
    AddElem(&re3, "casa", 1000, "E124", 50000);
    AddElem(&re3, "apartament", 900, "E453", 200000);
    agentie_t* l2 = lowerPrice(&re3, 60000);
    assert(get_len(l2) == 1);
    destroy_agentie(l2);


    agentie_t* sorted = sort_by_price(re.allOffers);
    oferta of_s = get_elem_at(sorted, 0);
    assert(get_pret(of_s) == 20000);
    destroy_agentie(sorted);

    agentie_t* sorted2 = sort_by_type(re3.allOffers);
    oferta of_s2 = get_elem_at(sorted2, 0);
    assert(strcmp(get_tip(of_s2), "teren") == 0);
    destroy_agentie(sorted2);

    agentie_t* sorted3 = sort_price_des(re3.allOffers);
    oferta of_s3 = get_elem_at(sorted3, 0);
    assert(get_pret(of_s3) == 200000);
    destroy_agentie(sorted3);


    destroy_oferta(off1);
    destroy_oferta(off2);
    destroy_oferta(off3);
    destroy_oferta(off4);
    destroy_oferta(off5);
    destroy_oferta(off6);

}
