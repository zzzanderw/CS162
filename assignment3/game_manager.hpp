#ifndef GAME_MANAGER
#define GAME_MANAGER

#include "property.hpp"

class GameManager {
private:
    Property* available_properties;
    int num_available_properties;
    Property* owned_properties;
    int num_owned_properties;
    // events
    int bank_account;

public:
    GameManager();
    GameManager(const GameManager&);
    ~GameManager();

    const GameManager& operator=(const GameManager&);

    int get_bank_account() const;

    bool is_game_over();
    void pay_debts();
    void pay_taxes();
    void update_tenants();
    void buy_property();
    void sell_property();
    void event();
};

#endif