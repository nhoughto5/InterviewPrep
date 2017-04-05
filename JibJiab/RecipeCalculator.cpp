#include <iostream>
#include <vector>
#include <assert.h>
#include <string>
#include <sstream>
#include "Utilities.h"
#include "Ingredient.h"
#include "Money.h"
#include "Kitchen.h"
#include <algorithm>

Kitchen gKitchen;

void testUtilMethods() {
    float tolerance = 0.00001;
    assert(abs(roundUpUtil(0.06f, 0.07f) - 0.07f) < tolerance);
    assert(abs(roundUpUtil(0.22f, 0.07f) - 0.28f) < tolerance);

    std::cout << "PASS - All util tests passed\n";
}
void testMoneyClass() {
    Money m0(.7f);
    Money m1(0.67f);
    Money m2(1.56f);
    Money m3;

    // Test toString Method
    assert(m0.toString().compare("$0.70") == 0);
    assert(m1.toString().compare("$0.67") == 0);
    assert(m2.toString().compare("$1.56") == 0);

    m3 = m2;
    assert(m2.toString().compare("$1.56") == 0);
    assert(m3.toString().compare("$1.56") == 0);

    m3 += m2;
    assert(m3.toString().compare("$3.12") == 0);

    m3 -= m2;
    assert(m3.toString().compare("$1.56") == 0);

    m3 *= 2.f;
    assert(m3.toString().compare("$3.12") == 0);

    m3 /= 2.f;
    assert(m3.toString().compare("$1.56") == 0);

    std::cout << "PASS - All Money class test cases passed\n";
}

void testRecipeClass() {
    
    Kitchen kitchen;
    kitchen.initKitchen();

    // R1
    assert(kitchen.m_recipes()[0].printTotalCost().compare ("$4.45") == 0);
    assert(kitchen.m_recipes()[0].printSalesTax().compare ("$0.21") == 0);
    assert(kitchen.m_recipes()[0].printWellnessDiscount().compare ("$0.11") == 0);

    // R2
    assert(kitchen.m_recipes()[1].printTotalCost().compare("$11.84") == 0);
    assert(kitchen.m_recipes()[1].printSalesTax().compare("$0.91") == 0);
    assert(kitchen.m_recipes()[1].printWellnessDiscount().compare("$0.09") == 0);

    // R3
    assert(kitchen.m_recipes()[2].printTotalCost().compare("$8.91") == 0);
    assert(kitchen.m_recipes()[2].printSalesTax().compare("$0.42") == 0);
    assert(kitchen.m_recipes()[2].printWellnessDiscount().compare("$0.07") == 0);


    std::cout << "PASS - All Recipe class tests passed\n";
}

void testIngredientClass() {
    Ingredient garlic(Produce, 1, true, "Garlic", "clove", Money(0.67f));
    assert(garlic.toString().compare("1.00 clove of organic Garlic = $0.67") == 0);

    Ingredient chicken(Meat, 1, false, "Chicken Breast", "", Money(2.19f));
    assert(chicken.toString().compare("1.00 Chicken Breast = $2.19") == 0);

    garlic = chicken;
    assert(garlic.toString().compare("1.00 Chicken Breast = $2.19") == 0);

    std::cout << "PASS - All Ingredient test cases passed\n";
}
void runTestCases() {
    testMoneyClass();
    testIngredientClass();
    testUtilMethods();
    testRecipeClass();
}

void printHelp() {
    printf("=========== Help ===========\n");
    printf("-h                 Help menu\n");
    printf("-s          Start Calculator\n");
    printf("\n\n");
}
void printRecipes() {
    printf("==== This Kitchen has the following recipes =====\n");
    for(auto& i : gKitchen.m_recipes()) {
        i.printRecipe();
    }
}
void printIngredients() {
    auto ingredients = gKitchen.m_ingredients();
    printf ("---- List of Ingredients ----");
    for (Ingredient ingredient : ingredients) {
        std::cout << ingredient.toString() << "\n";
    }
    printf("\n\n");
}

void closingTasks() {
    printf("\n\nThanks for using the Recipe Calculator, Goodbye! \n\n");
    exit(0);
}

void handleNewIngredient() {
    printf("\n\n Add a new ingredient to the kitchen!\n\n");
    printf("\nWhat's the name of the ingredient: ");
    std::string name;
    std::cin >> name;
    printf("\nIs it organic? (Y/N): ");
    char c;
    std::cin >> c;
    bool organic = c == 'Y' ? true : false;
    printf("\nWhat is it's unit of measurement? (cup, ounce, slice...etc): ");
    std::string um;
    std::cin >> um;
    bool g{true};
    float quantity{0.0f};
    do {
        std::cout << "\nHow many " << um << " do you have: ";
        std::string q;
        std::cin >> q;
        try {
            quantity = std::stof(q);
            g = false;
        }
        catch (std::invalid_argument e) {
            printf("That is not a valid number, try again.\n");
        }
    } while (g);
    printf("\nIs it: Produce (0), Meat (1), or from the Pantry (2): ");
    int typeInt;
    std::cin >> typeInt;
    IngredientType type = static_cast<IngredientType> (typeInt);

    std::cout << "\nHow much does it cost per " << um << ": ";
    std::string costStr;
    std::cin >> costStr;
    float cost = std::stof(costStr);
    Ingredient temp(type, quantity, organic, name, um, Money(cost));
    std::cout << "New Ingredient: " << temp.toString();

    gKitchen.addIngredient(temp);
    printf("\n\nIngredient Added!\n\n");
}

void handleRecipes() {
    printRecipes();
    printf("\n\n Choose a Recipe to Calculate by name: ");
    std::string chosenRecipe;
    std::cin >> chosenRecipe;
    auto v = gKitchen.m_recipes();
    auto it = std::find_if(v.begin(), v.end(), [&chosenRecipe](const Recipe& obj) {return obj.m_name() == chosenRecipe; });

    if (it != v.end())
    {
        //Found the recipe
        std::cout << "Tax: " << it->printSalesTax() << "\n";
        std::cout << "Discount: " << it->printWellnessDiscount() << "\n";
        std::cout << "Total: " << it->printTotalCost() << "\n\n\n\n";
    }
    else {
        printf("There is no recipe by that name\n");
    }
}

int main(int argc, char* argv[]) {

    // Allow for visual studio debug flag
    // or gcc debug flag
#if defined(_DEBUG) || defined(DEBUG)
    std::cout << "\n============= Tests ===============\n";
    std::cout << "===================================\n\n";
    runTestCases();
    std::cout << "\n===================================\n\n";
#endif
    std::vector<std::string> commandLineArgs;
    for (int i = 1; i < argc; ++i) {
        std::stringstream ss(argv[i]);
        commandLineArgs.push_back(ss.str());
        ss.str("");
    }

    // The help flag was included
    if (std::find(commandLineArgs.begin(), commandLineArgs.end(), "-h") != commandLineArgs.end()) {
        printHelp();
        return 0;
    }

    //Start the recipe calculator
    if (argc == 2 && std::find(commandLineArgs.begin(), commandLineArgs.end(), "-s") != commandLineArgs.end()) {
        bool running{ true }, madeMistake{ false };
        printf("\n ============= Welcome to Recipe Calculator ============= \n");
        gKitchen.initKitchen();
        printf("\n ======= Kitchen Created ======== \n");
        while(true){

            //The madeMistake flag is used to set what output to print
            if(!madeMistake) {
                printf("**** What would you like to do: **** \n1.) Choose from a pre-made recipe (R)\n2.) Make your own recipe from a list of ingredients (I)\n3.) Add a new ingredient (A)\n4.) Print the list of available ingredients (L)\n5.) Exit (Q)\n");
                printf("Enter Your Choice (R, I, A, L, Q):");
            }
            else {
                printf("Please enter your choice (R, I, A, L, Q): ");
            }
            char resp;
            
            std::cin >> resp;
            printf("\n");
            switch (resp) {
            case 'Q':
                closingTasks();
                break;
            case 'L':
                printIngredients();
                break;
            case 'I':
                handleNewIngredient();
                madeMistake = false;
                break;
            case 'R':
                handleRecipes();
                madeMistake = false;
                break;
            default:
                printf("There are only three options to choose from: \n");
                printf("        1.) Choose from existing recipes -> Use: R\n");
                printf("        2.) Make a recipe from a list of ingredients -> Use: I\n");
                printf("        3.) Exit the program -> Use: Q\n");
                madeMistake = true;
                break;
            }
        }
    }
    return 0;
}
