#include <iostream>
#include <vector>
#include <assert.h>
#include <string>
#include <sstream>
#include "Utilities.h"
#include "Ingredient.h"
#include "Money.h"
#include "Recipe.h"


std::vector<Ingredient> getIngredientList() {
    std::vector<Ingredient> ret;

    //Produce
    ret.push_back(Ingredient(Produce, 1, true, "Garlic", "clove", Money(0.67f)));
    ret.push_back(Ingredient(Produce, 1, false, "Lemon", "", Money(2.03f)));
    ret.push_back(Ingredient(Produce, 1, false, "Corn", "cup", Money(0.87f)));

    // Meat/Poultry
    ret.push_back(Ingredient(Meat, 1, false, "Chicken Breast", "", Money(2.19f)));
    ret.push_back(Ingredient(Meat, 1, false, "Bacon", "slice", Money(0.24f)));

    // Pantry
    ret.push_back(Ingredient(Pantry, 1, false, "Pasta", "ounce", Money(0.31f)));
    ret.push_back(Ingredient(Pantry, 1, true, "Olive Oil", "cup", Money(1.92f)));
    ret.push_back(Ingredient(Pantry, 1, false, "Vinegar", "cup", Money(1.26f)));
    ret.push_back(Ingredient(Pantry, 1, false, "Salt", "teaspoon", Money(0.16f)));
    ret.push_back(Ingredient(Pantry, 1, false, "pepper", "teaspoon", Money(0.17f)));

    return ret;
}
std::vector<Recipe> initRecipes() {
    std::vector<Recipe> ret;
    Recipe r1;
    r1.addIngredient(Ingredient(Produce, 1, true, "Garlic", "clove", Money(0.67f)));
    r1.addIngredient(Ingredient(Produce, 1, false, "Lemon", "", Money(2.03f)));
    r1.addIngredient(Ingredient(Pantry, 0.75f, true, "Olive Oil", "cup", Money(1.92f)));
    r1.addIngredient(Ingredient(Pantry, 0.75f, false, "Salt", "teaspoon", Money(0.16f)));
    r1.addIngredient(Ingredient(Pantry, 0.5f, false, "pepper", "teaspoon", Money(0.17f)));
    ret.push_back(r1);

    Recipe r2;
    r2.addIngredient(Ingredient(Produce, 1, true, "Garlic", "clove", Money(0.67f)));
    r2.addIngredient(Ingredient(Meat, 4, false, "Chicken Breast", "", Money(2.19f)));
    r2.addIngredient(Ingredient(Pantry, 0.5f, true, "Olive Oil", "cup", Money(1.92f)));
    r2.addIngredient(Ingredient(Pantry, 0.5f, false, "Vinegar", "cup", Money(1.26f)));
    ret.push_back(r2);

    Recipe r3;
    r3.addIngredient(Ingredient(Produce, 1, true, "Garlic", "clove", Money(0.67f)));
    r3.addIngredient(Ingredient(Produce, 4, false, "Corn", "cup", Money(0.87f)));
    r3.addIngredient(Ingredient(Meat, 4, false, "Bacon", "slices", Money(0.24f)));
    r3.addIngredient(Ingredient(Pantry, 8, false, "Pasta", "ounce", Money(0.31f)));
    r3.addIngredient(Ingredient(Pantry, 0.3333f, true, "Olive Oil", "cup", Money(1.92f)));
    r3.addIngredient(Ingredient(Pantry, 1.25, false, "Salt", "teaspoon", Money(0.16f)));
    r3.addIngredient(Ingredient(Pantry, 0.75, false, "pepper", "teaspoon", Money(0.17f)));
    ret.push_back(r3);
    return ret;
}
void testUtilMethods() {
    float tolerance = 0.00001;
    assert(abs(roundUtil(0.06f) - 0.07f) < tolerance);
    assert(abs(roundUtil(0.22f) - 0.21f) < tolerance);

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
}

void printHelp() {
    printf("=========== Help ===========\n");
    printf("-h                 Help menu\n");
    printf("-s          Start Calculator\n");
    printf("\n\n");
}
void printRecipes() {
    
}
void printIngredients() {
    auto i = getIngredientList();
    printf("---- List of Ingredients ----");
    for (Ingredient ingredient : i) {
        std::cout << ingredient.toString() << "\n";
    }
}

void closingTasks() {
    printf("\n\nThanks for using the Recipe Calculator, Goodbye! \n\n");
    exit(0);
}


void handleRecipes() {
    printRecipes();
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
        while(1){
            if(!madeMistake) {
                printf("Would you like to choose from a pre-made recipe (R), make your own from a list of ingredients (I) or Exit (Q): ");
            }
            else {
                printf("Please enter your choice (R, I, Q): ");
            }
            char resp;
            std::cin >> resp;
            printf("\n");
            switch (resp) {
            case 'Q':
                closingTasks();
                break;
            case 'I':
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
