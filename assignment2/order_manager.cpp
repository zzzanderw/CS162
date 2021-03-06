/*********************************************************************
** Program Filename: order_manager.cpp
** Author: Alexander Nead-Work
** Date: 04/27/2018
** Description: Immplementation for the OrderManager class
** Input: n/a
** Output: n/a
*********************************************************************/

#include "order_manager.hpp"

/*********************************************************************
** Function: OrderManager
** Description: Default constructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/
OrderManager::OrderManager() {
    this->num_orders = 0;
    this->orders = NULL;
    this->next_order_num = 1;
}

/*********************************************************************
** Function: ~OrderManager
** Description: Destructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/
OrderManager::~OrderManager() {
    if (this->orders != NULL) {
        for (int i = 0; i < this->num_orders; i++) {
            delete[] this->orders[i].pizzas;
        }

        delete[] this->orders;
    }
}

/*********************************************************************
** Function: OrderManager
** Description: Copy construtor
** Parameters: const OrderManager&
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/
OrderManager::OrderManager(const OrderManager& copy) {
    this->num_orders = copy.num_orders;
    if (this->num_orders > 0) {
        this->orders = new Order[this->num_orders];
        for (int i = 0; i < this->num_orders; i++) {
            this->orders[i] = copy.orders[i];
        }
    }
    this->next_order_num = copy.next_order_num;
}

/*********************************************************************
** Function: operator=
** Description: Assignment operator overload
** Parameters: const OrderManager&
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/
const OrderManager& OrderManager::operator=(const OrderManager& copy) {
    this->num_orders = copy.num_orders;
    if (this->num_orders > 0) {
        this->orders = new Order[this->num_orders];
        for (int i = 0; i < this->num_orders; i++) {
            this->orders[i] = copy.orders[i];
        }
    }
    this->next_order_num = copy.next_order_num;
    return *this;
}

/*********************************************************************
** Function: add_order
** Description: Adds a new order to the array
** Parameters: Order*
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/
int OrderManager::add_order(Order* new_order) {
    this->num_orders++;
    Order* new_arr = new Order[this->num_orders];
    for (int i = 0; i < this->num_orders-1; i++) {
        new_arr[i] = this->orders[i];
    }
    if (new_order->order_num == -1)
        new_order->order_num = this->next_order_num;
    new_arr[this->num_orders-1] = *new_order;
    if (this->orders != NULL) delete[] this->orders;
    this->orders = new_arr;
    return this->next_order_num++;
}

/*********************************************************************
** Function: create_order
** Description: Creates a new order
** Parameters: std::string, std::string, std::string, std::string
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/
int OrderManager::create_order(std::string name, std::string credit_card, std::string address, std::string phone_number) {
    Order order;
    order.order_num = -1;
    order.customer_name = name;
    order.credit_card = credit_card;
    order.address = address;
    order.phone_number = phone_number;
    order.num_distinct_pizzas = 0;
    order.pizzas = new PizzaOrder[10];

    return this->add_order(&order);
}

/*********************************************************************
** Function: create_order
** Description: Creates a new order
** Parameters: int, std::string, std::string, std::string, std::string
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/
void OrderManager::create_order(int order_num, std::string name, std::string credit_card, std::string address, std::string phone_number) {
    Order order;
    order.order_num = order_num;
    order.customer_name = name;
    order.credit_card = credit_card;
    order.address = address;
    order.phone_number = phone_number;
    order.num_distinct_pizzas = 0;
    order.pizzas = new PizzaOrder[10];

    this->add_order(&order);
}

void OrderManager::add_pizza_to_order(int order_num, std::string name, int quantity, Size size) {
    PizzaOrder pizza;
    pizza.name = name;
    pizza.quantity = quantity;
    pizza.size = size;
    
    Order* order;
    for (int i = 0; i < this->num_orders; i++) {
        if (this->orders[i].order_num == order_num) {
            order = &this->orders[i];
            break;
        }
    }

    order->num_distinct_pizzas++;
    PizzaOrder* new_arr = new PizzaOrder[order->num_distinct_pizzas];
    for (int i = 0; i < order->num_distinct_pizzas-1; i++) {
        new_arr[i] = order->pizzas[i];
    }
    new_arr[order->num_distinct_pizzas-1] = pizza;
    // if (order->pizzas != NULL) delete[] order->pizzas;
    order->pizzas = new_arr;
}

void OrderManager::remove_order(int order_num) {
    for (int i = 0; i < this->num_orders; i++) {
        if (this->orders[i].order_num == order_num) {
            this->orders[i].order_num = -1;
        }
    }
    Order* new_arr = new Order[this->num_orders-1];
    int counter = 0;
    for (int i = 0; i < this->num_orders; i++) {
        if (this->orders[i].order_num != -1) {
            new_arr[counter] = this->orders[i];
            counter++;
        }
    }
    if (this->orders != NULL) delete[] this->orders;
    this->orders = new_arr;
    this->num_orders--;
}

bool OrderManager::order_exists(int order_num) {
    if (order_num >= this->next_order_num) return false;
    for (int i = 0; i < this->num_orders; i++) {
        if (this->orders[i].order_num == order_num) return true;
    }
    return false;
}

void OrderManager::print() {
    printf("Order #\tCustomer Name\tCustomer CC#\tCustomer Address\tCustomer Phone #\n");
    for (int i = 0; i < this->num_orders; i++) {
        printf("%d\t%s\t%s\t%s\t%s\n", this->orders[i].order_num, this->orders[i].customer_name.c_str(), this->orders[i].credit_card.c_str(), this->orders[i].address.c_str(), this->orders[i].phone_number.c_str());

        std::cout << "Pizzas on Order:" << std::endl;
        printf("\tPizza\tSize\tQuantity\n");
        for (int j = 0; j < this->orders[i].num_distinct_pizzas; j++) {
            printf("\t%s\t%c\t%d\n", this->orders[i].pizzas[j].name.c_str(), this->orders[i].pizzas[j].size, this->orders[i].pizzas[j].quantity);
        }
        std::cout << std::endl;
    }
}

void OrderManager::load_from_file() {
    if (!is_file_empty(ORDER_DATA)) {
        // file exists and has data

        std::string name, credit_card, address, phone, pname, temp;
        int order_number, quantity, num_distinct_pizzas;
        Size size;
        std::stringstream ss;

        std::ifstream file;
        file.open(ORDER_DATA);

        int lines = 0;
        while (!file.eof()) {
            getline(file, temp);
            if (temp != "") {
                lines++;
            }
        }
        file.close();
        file.open(ORDER_DATA);

        for (int i = 0; i < lines; i++) {
            if (file.eof()) break;

            ss.str(std::string());

            file >> order_number;
            file >> name;
            file >> temp; // last name
            name.append(" ");
            name.append(temp);
            file >> credit_card;
            file >> address;
            file >> phone;

            this->create_order(order_number, name, credit_card, address, phone);

            getline(file, temp);

            ss << temp;
            num_distinct_pizzas = word_count(temp) / 3;

            for (int j = 0; j < num_distinct_pizzas; j++) {
                ss >> pname;
                ss >> temp; // size, to be parsed later
                ss >> quantity;

                size = Pizza::parse_size(temp);

                this->add_pizza_to_order(order_number, pname, quantity, size);
            }
        }
    }    
}

void OrderManager::serialize() {
    std::ofstream file;
    file.open(ORDER_DATA);
    for (int i = 0; i < this->num_orders; i++) {
        file << this->orders[i].order_num << " " << this->orders[i].customer_name << " " << this->orders[i].credit_card << " " << this->orders[i].address << " " << this->orders[i].phone_number;
        for (int j = 0; j < this->orders[i].num_distinct_pizzas; j++) {
            file << " " << this->orders[i].pizzas[j].name << " " << (char)this->orders[i].pizzas[j].size << " " << this->orders[i].pizzas[j].quantity;
        }
        file << std::endl;
    }
    file.flush();
    file.close();
}
