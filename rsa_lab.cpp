#include "splashkit.h"
#include <string>

using namespace std;

// Reads text input from the user.
string read_string(string prompt)
{
    write(prompt);
    return read_line();
}

// Reads integer input from the user.
int read_integer(string prompt)
{
    string line = read_string(prompt);

    while (!is_integer(line))
    {
        write_line("Please enter a whole number.");
        line = read_string(prompt);
    }

    return convert_to_integer(line);
}

// Reads an integer within a valid range.
int read_integer_range(string prompt, int minimum, int maximum)
{
    int value = read_integer(prompt);

    while (value < minimum or value > maximum)
    {
        write_line("Please enter a number between " + ::to_string(minimum) + " and " + ::to_string(maximum) + ".");
        value = read_integer(prompt);
    }

    return value;
}

// Checks whether a number is prime.
bool is_prime(int number)
{
    if (number < 2)
    {
        return false;
    }

    for (int divisor = 2; divisor * divisor <= number; divisor++)
    {
        if (number % divisor == 0)
        {
            return false;
        }
    }

    return true;
}

// Calculates the greatest common divisor using Euclid's algorithm.
int gcd(int a, int b)
{
    while (b != 0)
    {
        int remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

// Shows the steps of Euclid's algorithm.
void show_gcd_steps(int a, int b)
{
    write_line("");
    write_line("Euclidean Algorithm Steps:");

    while (b != 0)
    {
        int quotient = a / b;
        int remainder = a % b;

        write_line(::to_string(a) + " = " + ::to_string(quotient) + " x " + ::to_string(b) + " + " + ::to_string(remainder));

        a = b;
        b = remainder;
    }

    write_line("GCD = " + ::to_string(a));
}

// Lets the user test whether a number is prime.
void test_prime_checking()
{
    int number = read_integer("Enter a number to test if it is prime: ");

    if (is_prime(number))
    {
        write_line(::to_string(number) + " is prime.");
    }
    else
    {
        write_line(::to_string(number) + " is not prime.");
    }
}

// Lets the user test the GCD algorithm.
void test_gcd()
{
    int first = read_integer("Enter the first number: ");
    int second = read_integer("Enter the second number: ");

    int result = gcd(first, second);

    write_line("");
    write_line("The GCD of " + ::to_string(first) + " and " + ::to_string(second) + " is " + ::to_string(result) + ".");

    show_gcd_steps(first, second);
}

// Displays the main menu for the RSA Cryptography Lab.
void display_menu()
{
    write_line("");
    write_line("====================================");
    write_line("       RSA CRYPTOGRAPHY LAB");
    write_line("====================================");
    write_line("1. Generate RSA keys");
    write_line("2. View current keys");
    write_line("3. Encrypt a message");
    write_line("4. Decrypt current message");
    write_line("5. Save encrypted message to file");
    write_line("6. Load encrypted message from file");
    write_line("7. Show RSA maths explanation");
    write_line("8. Attempt simple RSA crack");
    write_line("9. Test prime and GCD functions");
    write_line("0. Exit");
}

// Runs the selected menu option.
void run_menu_option(int choice)
{
    switch (choice)
    {
    case 1:
        write_line("");
        write_line("Generate RSA keys feature coming soon.");
        break;

    case 2:
        write_line("");
        write_line("View current keys feature coming soon.");
        break;

    case 3:
        write_line("");
        write_line("Encrypt message feature coming soon.");
        break;

    case 4:
        write_line("");
        write_line("Decrypt message feature coming soon.");
        break;

    case 5:
        write_line("");
        write_line("Save encrypted message feature coming soon.");
        break;

    case 6:
        write_line("");
        write_line("Load encrypted message feature coming soon.");
        break;

    case 7:
        write_line("");
        write_line("RSA maths explanation feature coming soon.");
        break;

    case 8:
        write_line("");
        write_line("Simple RSA crack feature coming soon.");
        break;

    case 9:
        write_line("");
        write_line("--- Prime Test ---");
        test_prime_checking();

        write_line("");
        write_line("--- GCD Test ---");
        test_gcd();
        break;

    case 0:
        write_line("");
        write_line("Exiting RSA Cryptography Lab.");
        break;
    }
}

int main()
{
    int choice;

    write_line("Welcome to the RSA Cryptography Lab.");

    do
    {
        display_menu();
        choice = read_integer_range("Choose an option: ", 0, 9);
        run_menu_option(choice);

    } while (choice != 0);

    return 0;
}