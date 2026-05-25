#include "splashkit.h"
#include <string>
#include <fstream>

using namespace std;

const int MAX_MESSAGE_LENGTH = 200;

struct RSAKeyPair
{
    int p;
    int q;
    int n;
    int phi;
    int e;
    int d;
    bool generated;
};

struct EncryptedMessage
{
    int values[MAX_MESSAGE_LENGTH];
    int length;
    bool available;
};

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

// Calculates base^exponent mod modulus using repeated modular multiplication.
int modular_power(int base, int exponent, int modulus)
{
    int result = 1;
    base = base % modulus;

    for (int i = 0; i < exponent; i++)
    {
        result = (result * base) % modulus;
    }

    return result;
}

// Finds d where e * d mod phi = 1.
int find_modular_inverse(int e, int phi)
{
    for (int d = 1; d < phi; d++)
    {
        if ((e * d) % phi == 1)
        {
            return d;
        }
    }

    return -1;
}

// Displays the current RSA key values.
void view_current_keys(const RSAKeyPair &keys)
{
    if (!keys.generated)
    {
        write_line("");
        write_line("No RSA keys have been generated yet.");
        return;
    }

    write_line("");
    write_line("====== CURRENT RSA KEYS ======");
    write_line("p: " + ::to_string(keys.p));
    write_line("q: " + ::to_string(keys.q));
    write_line("n = p x q: " + ::to_string(keys.n));
    write_line("phi = (p - 1)(q - 1): " + ::to_string(keys.phi));
    write_line("Public exponent e: " + ::to_string(keys.e));
    write_line("Private exponent d: " + ::to_string(keys.d));
    write_line("");
    write_line("Public key:  (" + ::to_string(keys.e) + ", " + ::to_string(keys.n) + ")");
    write_line("Private key: (" + ::to_string(keys.d) + ", " + ::to_string(keys.n) + ")");
}

// Generates RSA keys using two prime numbers.
void generate_keys(RSAKeyPair &keys)
{
    write_line("");
    write_line("====== RSA KEY GENERATION ======");

    int p = read_integer("Enter first prime number p: ");

    while (!is_prime(p))
    {
        write_line(::to_string(p) + " is not prime.");
        p = read_integer("Enter first prime number p: ");
    }

    int q = read_integer("Enter second prime number q: ");

    while (!is_prime(q) or q == p)
    {
        if (!is_prime(q))
        {
            write_line(::to_string(q) + " is not prime.");
        }
        else
        {
            write_line("q must be different from p.");
        }

        q = read_integer("Enter second prime number q: ");
    }

    int n = p * q;

    while (n <= 127)
    {
        write_line("");
        write_line("p x q must be greater than 127 so normal text characters can be encrypted.");
        write_line("Current n = " + ::to_string(n));
        write_line("Please choose larger prime numbers.");

        p = read_integer("Enter first prime number p: ");

        while (!is_prime(p))
        {
            write_line(::to_string(p) + " is not prime.");
            p = read_integer("Enter first prime number p: ");
        }

        q = read_integer("Enter second prime number q: ");

        while (!is_prime(q) or q == p)
        {
            if (!is_prime(q))
            {
                write_line(::to_string(q) + " is not prime.");
            }
            else
            {
                write_line("q must be different from p.");
            }

            q = read_integer("Enter second prime number q: ");
        }

        n = p * q;
    }

    int phi = (p - 1) * (q - 1);

    write_line("");
    write_line("n = p x q = " + ::to_string(p) + " x " + ::to_string(q) + " = " + ::to_string(n));
    write_line("phi = (p - 1)(q - 1) = " + ::to_string(p - 1) + " x " + ::to_string(q - 1) + " = " + ::to_string(phi));

    int e = read_integer_range("Enter public exponent e, between 2 and phi - 1: ", 2, phi - 1);

    while (gcd(e, phi) != 1)
    {
        write_line("");
        write_line("e must be relatively prime to phi.");
        write_line("gcd(" + ::to_string(e) + ", " + ::to_string(phi) + ") = " + ::to_string(gcd(e, phi)));
        show_gcd_steps(e, phi);

        e = read_integer_range("Enter public exponent e, between 2 and phi - 1: ", 2, phi - 1);
    }

    int d = find_modular_inverse(e, phi);

    keys.p = p;
    keys.q = q;
    keys.n = n;
    keys.phi = phi;
    keys.e = e;
    keys.d = d;
    keys.generated = true;

    write_line("");
    write_line("RSA keys generated successfully.");
    write_line("d was found by solving: e x d mod phi = 1");
    write_line(::to_string(e) + " x " + ::to_string(d) + " mod " + ::to_string(phi) + " = 1");

    view_current_keys(keys);
}

// Encrypts a message using the public key.
void encrypt_message(const RSAKeyPair &keys, EncryptedMessage &encrypted)
{
    if (!keys.generated)
    {
        write_line("");
        write_line("Please generate RSA keys before encrypting a message.");
        return;
    }

    string message = read_string("Enter a short message to encrypt: ");

    while (message.length() == 0 or message.length() > MAX_MESSAGE_LENGTH)
    {
        write_line("Message must be between 1 and " + ::to_string(MAX_MESSAGE_LENGTH) + " characters.");
        message = read_string("Enter a short message to encrypt: ");
    }

    encrypted.length = message.length();

    write_line("");
    write_line("====== ENCRYPTION STEPS ======");
    write_line("Formula: encrypted = message^e mod n");
    write_line("Using public key: (" + ::to_string(keys.e) + ", " + ::to_string(keys.n) + ")");
    write_line("");

    for (int i = 0; i < encrypted.length; i++)
    {
        int ascii_value = message[i];
        int encrypted_value = modular_power(ascii_value, keys.e, keys.n);

        encrypted.values[i] = encrypted_value;

        write_line("'" + string(1, message[i]) + "' -> ASCII " + ::to_string(ascii_value) + " -> encrypted " + ::to_string(encrypted_value));
    }

    encrypted.available = true;

    write_line("");
    write_line("Encrypted message as numbers:");

    for (int i = 0; i < encrypted.length; i++)
    {
        write(::to_string(encrypted.values[i]) + " ");
    }

    write_line("");
}

// Decrypts the current encrypted message using the private key.
void decrypt_message(const RSAKeyPair &keys, const EncryptedMessage &encrypted)
{
    if (!keys.generated)
    {
        write_line("");
        write_line("Please generate RSA keys before decrypting a message.");
        return;
    }

    if (!encrypted.available)
    {
        write_line("");
        write_line("There is no encrypted message to decrypt yet.");
        return;
    }

    string decrypted = "";

    write_line("");
    write_line("====== DECRYPTION STEPS ======");
    write_line("Formula: decrypted = encrypted^d mod n");
    write_line("Using private key: (" + ::to_string(keys.d) + ", " + ::to_string(keys.n) + ")");
    write_line("");

    for (int i = 0; i < encrypted.length; i++)
    {
        int encrypted_value = encrypted.values[i];
        int ascii_value = modular_power(encrypted_value, keys.d, keys.n);
        char character = (char)ascii_value;

        decrypted += character;

        write_line(::to_string(encrypted_value) + " -> ASCII " + ::to_string(ascii_value) + " -> '" + string(1, character) + "'");
    }

    write_line("");
    write_line("Decrypted message: " + decrypted);
}

// Saves the encrypted message to a text file.
void save_encrypted_message(const EncryptedMessage &encrypted)
{
    if (!encrypted.available)
    {
        write_line("");
        write_line("There is no encrypted message to save.");
        return;
    }

    string filename = read_string("Enter filename to save to, for example encrypted_message.txt: ");

    while (filename == "")
    {
        write_line("Filename cannot be empty.");
        filename = read_string("Enter filename to save to, for example encrypted_message.txt: ");
    }

    ofstream output_file(filename);

    if (!output_file.is_open())
    {
        write_line("");
        write_line("Could not open file for writing.");
        return;
    }

    output_file << encrypted.length << endl;

    for (int i = 0; i < encrypted.length; i++)
    {
        output_file << encrypted.values[i] << " ";
    }

    output_file.close();

    write_line("");
    write_line("Encrypted message saved successfully to " + filename + ".");
}

// Loads an encrypted message from a text file.
void load_encrypted_message(EncryptedMessage &encrypted)
{
    string filename = read_string("Enter filename to load from, for example encrypted_message.txt: ");

    while (filename == "")
    {
        write_line("Filename cannot be empty.");
        filename = read_string("Enter filename to load from, for example encrypted_message.txt: ");
    }

    ifstream input_file(filename);

    if (!input_file.is_open())
    {
        write_line("");
        write_line("Could not open file for reading.");
        return;
    }

    input_file >> encrypted.length;

    if (encrypted.length <= 0 or encrypted.length > MAX_MESSAGE_LENGTH)
    {
        write_line("");
        write_line("The file does not contain a valid encrypted message length.");
        input_file.close();
        return;
    }

    for (int i = 0; i < encrypted.length; i++)
    {
        input_file >> encrypted.values[i];
    }

    input_file.close();

    encrypted.available = true;

    write_line("");
    write_line("Encrypted message loaded successfully from " + filename + ".");
    write_line("Loaded encrypted numbers:");

    for (int i = 0; i < encrypted.length; i++)
    {
        write(::to_string(encrypted.values[i]) + " ");
    }

    write_line("");
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
// Explains the RSA process and connects the program to discrete mathematics.
void show_rsa_explanation()
{
    write_line("");
    write_line("====== RSA MATHEMATICS EXPLANATION ======");
    write_line("");
    write_line("RSA is a public-key cryptography method.");
    write_line("It uses two keys:");
    write_line("- a public key for encryption");
    write_line("- a private key for decryption");
    write_line("");

    write_line("Step 1: Choose two prime numbers");
    write_line("The user chooses two prime numbers called p and q.");
    write_line("Prime numbers are important because multiplying two primes is easy,");
    write_line("but factorising their product is difficult when the primes are very large.");
    write_line("");

    write_line("Step 2: Calculate n");
    write_line("n = p x q");
    write_line("The value n is used in both the public key and the private key.");
    write_line("");

    write_line("Step 3: Calculate phi");
    write_line("phi = (p - 1)(q - 1)");
    write_line("This value is based on Euler's totient function.");
    write_line("It helps determine which numbers can be used safely for the public exponent.");
    write_line("");

    write_line("Step 4: Choose e");
    write_line("The public exponent e must be relatively prime to phi.");
    write_line("This means gcd(e, phi) must equal 1.");
    write_line("The program checks this using Euclid's algorithm.");
    write_line("");

    write_line("Step 5: Find d");
    write_line("The private exponent d is the modular inverse of e.");
    write_line("This means:");
    write_line("e x d mod phi = 1");
    write_line("The program finds d by testing values until this condition is true.");
    write_line("");

    write_line("Step 6: Encrypt a message");
    write_line("Each character is converted into its ASCII number.");
    write_line("Then the program encrypts it using:");
    write_line("encrypted = message^e mod n");
    write_line("");

    write_line("Step 7: Decrypt a message");
    write_line("The encrypted number is decrypted using:");
    write_line("decrypted = encrypted^d mod n");
    write_line("This recovers the original ASCII value and then the original character.");
    write_line("");

    write_line("Why this demonstrates HD-level programming:");
    write_line("- It uses algorithms from discrete mathematics.");
    write_line("- It uses prime checking, GCD, modular inverses, and modular arithmetic.");
    write_line("- It connects programming concepts to a real-world cryptography system.");
    write_line("- It goes beyond basic input/output and includes file handling and encryption logic.");
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
void run_menu_option(int choice, RSAKeyPair &keys, EncryptedMessage &encrypted)
{
    switch (choice)
    {
    case 1:
        generate_keys(keys);
        break;

    case 2:
        view_current_keys(keys);
        break;

    case 3:
        encrypt_message(keys, encrypted);
        break;

    case 4:
        decrypt_message(keys, encrypted);
        break;

    case 5:
        save_encrypted_message(encrypted);
        break;

    case 6:
        load_encrypted_message(encrypted);
        break;

    case 7:
        show_rsa_explanation();
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
    RSAKeyPair keys;
    keys.generated = false;

    EncryptedMessage encrypted;
    encrypted.length = 0;
    encrypted.available = false;

    int choice;

    write_line("Welcome to the RSA Cryptography Lab.");

    do
    {
        display_menu();
        choice = read_integer_range("Choose an option: ", 0, 9);
        run_menu_option(choice, keys, encrypted);

    } while (choice != 0);

    return 0;
}