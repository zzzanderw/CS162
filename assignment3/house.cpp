#include "house.hpp"

/*********************************************************************
** Function: main
** Description: Entry point for the program
** Parameters: int argc, char** argv
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/
House::House() {
    this->value = (rand() % ((this->max_value - this->min_value) / 100) * 100);
    this->mortgage_duration = ceil((float)this->value/(float)this->mortgage_amount);
    this->mortgage_months_remaining = this->mortgage_months_remaining;

    this->num_tenants = 1;
    Citizen* t = new Citizen;
    this->tenants.push_back(t);
    
    this->set_rents();
}

/*********************************************************************
** Function: main
** Description: Entry point for the program
** Parameters: int argc, char** argv
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/
void House::update_rent() {
    int rent;
    do {
        rent = get_int("Please enter a new rent: ");
    } while (rent < 0);

    this->tenants[0]->set_rent(rent);
}

/*********************************************************************
** Function: main
** Description: Entry point for the program
** Parameters: int argc, char** argv
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/
void House::print() {
    printf("Property type: House\n");

    Property::print();
}