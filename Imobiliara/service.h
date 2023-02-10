#pragma once
#include "agentie.h"
#include "oferta.h"

typedef struct {
    agentie_t* allOffers;
    agentie_t* undoList; //list of list of offers
}RealEstate;

/*Create a RealEstate*/
RealEstate createRealEstate();

/*
 Destroy a RealEstate
 */
void destroyRealEstate(RealEstate* re);

/*
   Tipul functie de comparare pentru 2 elemente
   returneaza 0 daca sunt egale, 1 daca o1>o2, -1 altfel
*/
typedef int(*FunctieCompara)(oferta o1, oferta o2);

/*
	add a new element to the list
	ag- the list
	tip, suprafata, adresa, pret- parameters for the new element
*/
int AddElem2(agentie_t* ag, char* tip, int suprafata, char* adresa, int pret);


int AddElem(RealEstate* re, char* tip, int suprafata, char* adresa, int pret);

//Realize the undo operation
int undo(RealEstate* re);



/*
	delete an element from the list
	ag- the list
	tip, suprafata, adresa, pret- parameters for the element to delete
*/
//int DelElem(agentie_t* ag, char* tip, int suprafata, char* adresa, int pret);
int DelElem(RealEstate* re, char* tip, int suprafata, char* adresa, int pret);
/*
	modify an element
	ag- the list
	of- the element to modify
	new_of- the new value for the given element
*/
//int Update(agentie_t* ag, oferta of, oferta new_of);
int Update(RealEstate* re, oferta of, oferta new_of);
/*
	filter the list by the type
	typeSubstring- the type we filter by
*/
//agentie_t* getAllOfferts(agentie_t* ag, char* typeSubstring);
agentie_t* getAllOfferts(RealEstate* re, char* typeSubstring);

/*
 * Filter the list by the price
 * the prices of the offers must be lower than the given price
 */
agentie_t* lowerPrice(RealEstate* re, int price);

/*
* Sort in place
* cmpf - the relationship according to which it is sorted
*/
void sort_asc(agentie_t* ag, FunctieCompara cmpF);

/*
* Sort in place descendent
* cmpf - the relationship according to which it is sorted
*/
void sort_des(agentie_t* ag, FunctieCompara cmpF);

/*
	sort ascending by price
*/
agentie_t* sort_by_price(agentie_t* ag);

/*
	sort descending by type
*/
agentie_t* sort_by_type(agentie_t* ag);

/*
 * Return 1 if the price of o1 > price of o2, 0 if they are eqaul, otherwise -1
 */
int cmpPrice(oferta o1, oferta o2);

/*
 * Compare two strings
 */
int cmpType(oferta o1, oferta o2);

agentie_t* sort_price_des(agentie_t* ag);