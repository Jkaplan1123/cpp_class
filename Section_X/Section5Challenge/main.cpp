#include <iostream>

using namespace std;

double cleaning_cost(unsigned int num_rooms, double price_room);


int main()
{
    const unsigned int estimate_validity {30}; //How long the estimate is good for
    
    cout<<"Welcome to Jack's Carpert Cleaning Service" << endl;
    
    unsigned int num_small_rooms {0};
    const double small_room_price {25};
    cout << "Enter the number of small rooms to be cleaned: ";
    cin >> num_small_rooms;
    
    unsigned int num_large_rooms{0};
    const int large_room_price {35};
    cout << "Enter the number of large rooms to be cleaned: ";
    cin >> num_large_rooms;
    
    cout << endl;
    cout << "Cleaning Estimate" << endl;
    cout << "-----------------" << endl;
    cout << "Number of small rooms: " << num_small_rooms << endl;
    cout << "Number of large rooms: " << num_large_rooms << endl;

    cout << endl;
    cout << "Price per small room: $" << small_room_price << endl;
    cout << "Price per large room: $" << large_room_price << endl;
    
    double small_room_cost {cleaning_cost(num_small_rooms, small_room_price)};
    double large_room_cost {cleaning_cost(num_large_rooms, large_room_price)};
    double pretax_cost {small_room_cost + large_room_cost};
    
    cout << "Pretax Cost: $" << pretax_cost << endl;
    
    const double tax_rate {0.06};
    double tax {pretax_cost * tax_rate};
    
    cout << "Tax: $" << tax << endl;
    cout <<"===========================\n";
    cout << "Total Cost: " << pretax_cost + tax << endl;
    
    cout << endl << "This estimate is valid for " << estimate_validity << " days." << endl;
    
    return 0;
}


double cleaning_cost(unsigned int num_rooms, double price_room) {
    return num_rooms * price_room;
}