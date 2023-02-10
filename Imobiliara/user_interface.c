#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "user_interface.h"

void adauga(RealEstate * re) {
    printf("Type:");
    char type[30];
    scanf("%s", type);

    printf("Surface:");
    int surface;
    scanf("%d", &surface);

    printf("Address:");
    char address[50];
    scanf("%s", address);

    printf("Price:");
    int price;
    scanf("%d", &price);

    int error = AddElem(re, type, surface, address, price);
    if (error != 0) {
        printf("Invalid offer.\n");
    }
    else {
        printf("Offer added.\n");
    }
}

void update_of(RealEstate* re)
{
    printf("The offer to modify has:\n");
    printf("Type:");
    char type[30];
    scanf("%s", type);

    printf("Surface:");
    int surface;
    scanf("%d", &surface);

    printf("Address:");
    char address[50];
    scanf("%s", address);

    printf("Price:");
    int price;
    scanf("%d", &price);

    oferta of = init_oferta(type, surface, address, price);
    printf("The new parameters are:\n");
    printf("Type:");
    char tip[30];
    scanf("%s", tip);

    printf("Surface:");
    int suprafata;
    scanf("%d", &suprafata);

    printf("Address:");
    char adresa[50];
    scanf("%s", adresa);

    printf("Price:");
    int pret;
    scanf("%d", &pret);

    oferta new_of = init_oferta(tip, suprafata, adresa, pret);
    printf("%s", new_of->tip);
    int errors = Update(re, of, new_of);
    if (errors == -2) printf("The new offer is not valid.\n");
    else if (errors == -1) printf("Offer not found.\n");
    else printf("Offer modified.\n");
}

void deleteEl(RealEstate* re) {
    printf("The offer to delete has:\n");
    printf("Type:");
    char type[30];
    scanf("%s", type);

    printf("Surface:");
    int surface;
    scanf("%d", &surface);

    printf("Address:");
    char address[50];
    scanf("%s", address);

    printf("Price:");
    int price;
    scanf("%d", &price);

    int errors = DelElem(re, type, surface, address, price);
    if (errors != 0) {
        printf("Offer not found.\n");
    }
    else {
        printf("Offer deleted.\n");
    }
}

void printAllOfferts(agentie_t* ag) {
    printf("Offerts:\n");
    for (int i = 0; i < get_len(ag); i++) {
        oferta_t* of = get_elem_at(ag,i);
        printf("Type:%s Surface:%d Address:%s Price:%d\n", of->tip, of->suprafata, of->adresa, of->pret);
    }
}

void showAll(RealEstate* re){
    agentie_t* ag = getAllOfferts(re, NULL);
    printAllOfferts(ag);
    destroy_agentie(ag);
}

void filterOfferts(RealEstate* re) {
    printf("Type filter substring:");
    char filterStr[30];
    scanf("%s", filterStr);

    agentie_t* filteredL = getAllOfferts(re,filterStr);
    printAllOfferts(filteredL);
    if (get_len(filteredL) == 0)
        printf("There are none of this type.");

    destroy_agentie(filteredL);
    
}

void filterOffersPrice(RealEstate* re){
    printf("Price lower than:");
    int price;
    scanf("%d", &price);

    agentie_t* filteredList = lowerPrice(re, price);
    printAllOfferts(filteredList);
    if(get_len(filteredList) == 0)
        printf("There are none.");

    destroy_agentie(filteredList);
}

void print_menu() {
    printf("1. Add\n");
    printf("2. Update\n");
    printf("3. Delete\n");
    printf("4. Filter by type\n");
    printf("5. Sort ascending by price\n");
    printf("6. Sort descending by type\n");
    printf("7. Show all\n");
    printf("8. Undo\n");
    printf("9. Filter by price lower than\n");
    printf("10. Exit\n");

}

void sort_price(agentie_t* ag) {
    agentie_t* sortedL = sort_by_price(ag);
    printAllOfferts(sortedL);
    destroy_agentie(sortedL);
}

void sort_type(agentie_t* ag) {
    agentie_t* sortedL = sort_by_type(ag);
    printAllOfferts(sortedL);
    destroy_agentie(sortedL);
}

void run() {
    RealEstate re = createRealEstate();
    int ruleaza = 1;
    while (ruleaza) {
        print_menu();
        int cmd = 0;
        scanf("%d", &cmd);
        switch (cmd) {
            case 1:
                adauga(&re);
                break;
            case 2:
                update_of(&re);
                break;
            case 3:
                deleteEl(&re);
                break;
            case 4:
                filterOfferts(&re);
                break;
            case 5:
                sort_price(re.allOffers);
                break;
            case 6:
                sort_type(re.allOffers);
                break;
            case 7:
                showAll(&re);
                break;
            case 8:
                if (undo(&re) != 0){
                    printf("No more undo!!!\n");
                }
                break;
            case 9:
                filterOffersPrice(&re);
                break;
            case 10:
                ruleaza = 0;
                destroyRealEstate(&re);
                break;
            default:
                printf("Comanda invalida!!!\n");
        }
    }
}