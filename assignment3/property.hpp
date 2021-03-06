#ifndef PROPERTY
#define PROPERTY

#include <assert.h>
#include <math.h>
#include <stdlib.h>

#include "event.hpp"
#include "list.hpp"
#include "tenant.hpp"

#define PROPERTY_TAX 0.015

class Property {
public:
    Property();
    virtual ~Property();

    enum Location {
        kSoutheast,
        kNortheast,
        kMidwest,
        kSouthwest,
        kNorthwest
    };
    
    virtual int collect_rent();
    int pay_mortgage();
    int get_mortgage() const;
    int get_value() const;
    void update_tenants();
    virtual void print();
    void do_event(Event);
    void do_gentrification(Location);
    virtual void update_rent();
    int get_total_rent();

protected:
    static const int max_mortgage = 5000;
    static const int max_value = 600000;

    Location location;
    List<Tenant*> tenants;
    int num_tenants, value, mortgage_amount, mortgage_duration, mortgage_amount_paid, mortgage_months_remaining;
    
    virtual void set_rents();
};

#endif