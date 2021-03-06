#ifndef BUSINESS_COMPLEX
#define BUSINESS_COMPLEX

#include <stdlib.h>

#include "property.hpp"
#include "business.hpp"

#ifdef MAKE
#include "helper.hpp"
#else
#include "O:\cpphelper\helper.hpp"
#endif

#define PROPERTY_VALUE_INCREASE 1.01

class BusinessComplex : public Property {
private:  
    static const int min_value = 400000;
    static const int max_tenants = 5;

    void set_rents();

public:
    BusinessComplex();

    int collect_rent();
    void update_rent();
    void print();
};

#endif
