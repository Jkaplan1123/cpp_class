// Section 19
// Challenge 1
// Formatting output
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

struct City {
    std::string name;
    long population;
    double cost;
};

// Assume each country has at least 1 city
struct Country {
    std::string name;
    std::vector<City> cities;
};

struct Tours {
    std::string title;
    std::vector<Country> countries;
};

void generate_header(std::string title, const int total_width, const int country_width, const int city_name_width, const int population_width, const int price_width){

    std::cout << std::endl;
    // Create Centered Header
    const int title_length = title.size();
    std::string title_left = title.substr(0, title_length/2);
    std::string title_right = title.substr(title_length/2 + 1, title_length);

    std::cout << std::setw(total_width/2) << std::right << title_left;
    std::cout << std::setw(total_width/2) << std::left << title_right;
    std::cout << std::endl;

    // Category Titles
    std::cout << std::setw(country_width) << std::left << "Country";
    std::cout << std::setw(city_name_width) << std::left << "City";
    std::cout << std::setw(population_width) << std::left << "Population";
    std::cout << std::setw(price_width) << std::right << "Price";
    std::cout << std::endl;

    // Dashed Line
    std::cout << std::setw(total_width) << std::setfill('-') << "";
    std::cout << std::setfill(' ');
}

int main()
{
    Tours tours
        { "Tour Ticket Prices from Miami",
            {
                { // vector of countries
                    "Colombia", { // vector of cities in country: Colombia
                        { "Bogota", 8778000, 400.98 }, // city
                        { "Cali", 2401000, 424.12 }, // city
                        { "Medellin", 2464000, 350.98 }, // city
                        { "Cartagena", 972000, 345.34 }  // city
                    },
                },
                {
                    "Brazil", { 
                        { "Rio De Janiero", 13500000, 567.45 },
                        { "Sao Paulo", 11310000, 975.45 },
                        { "Salvador", 18234000, 855.99 }
                    },
                },
                {
                    "Chile", { 
                        { "Valdivia", 260000, 569.12 }, 
                        { "Santiago", 7040000, 520.00 }
                },
            },
                { "Argentina", { 
                    { "Buenos Aires", 3010000, 723.77 } 
                } 
            },
        }
    };

    const int country_width = 20;
    const int city_name_width = 20;
    const int population_width = 15;
    const int price_width = 15;

    const int total_width = country_width + city_name_width + population_width + price_width;

    generate_header(tours.title, total_width, country_width, city_name_width, population_width, price_width);
    
    for (auto country : tours.countries){
        std::cout << std::endl;
        std::cout << std::setw(country_width) << std::left << country.name;
        for (size_t idx = 0; idx < country.cities.size(); idx++){
            City city = country.cities[idx];
            if (idx != 0){
                std::cout << std::setw(country_width) << "";
            }
            std::cout << std::setw(city_name_width) << std::left << city.name;
            std::cout << std::setw(population_width) << std::right << city.population;
            std::cout << std::setw(price_width) << std::right << city.cost;
            std::cout << std::endl;
        }
    }
    


    return 0;
}