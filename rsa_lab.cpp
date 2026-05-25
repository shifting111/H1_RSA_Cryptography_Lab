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
    write_line("9. Run sample demonstration");
    write_line("0. Exit");
}

// Runs the selected menu option.
// At this stage, each option is a placeholder.
// Later iterations will replace these placeholders with working features.
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
        write_line("Sample demonstration feature coming soon.");
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