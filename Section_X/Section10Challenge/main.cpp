// Section 10
// Challenge - 
// Substitution Cipher

/*
A simple and very old method of sending secret messages is the substitution cipher.
You might have used this cipher with your friends when you were a kid.
Basically, each letter of the alphabet gets replaced by another letter of the alphabet.
For example, every 'a' get replaced with an 'X', and every 'b' gets replaced with a 'Z', etc.

Write a program thats ask a user to enter a secret message.

Encrypt this message using the substitution cipher and display the encrypted message.
Then decryped the encrypted message back to the original message.

You may use the 2 strings below for  your subsitition.
For example, to encrypt you can replace the character at position n in alphabet 
with the character at position n in key.

To decrypt you can replace the character at position n in key
with the character at position n in alphabet.

Have fun! And make the cipher stronger if you wish!
Currently the cipher only substitutes letters - you could easily add digits, puncuation, whitespace and so
forth. Also, currently the cipher always substitues a lowercase letter with an uppercase letter and vice-versa.
This could also be improved.

Remember, the less code you write the less code you have to test!
Reuse existing functionality in libraries and in the std::string class!
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    
    string alphabet {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    string key  {"XZNLWEBGJHQDYVTKFUOMPCIASRxznlwebgjhqdyvtkfuompciasr"};
    
    
    cout << endl;

    string message;
    cout << "Input message to be encoded: ";
    getline(cin, message);

    string origional_message = message;

    // string encoded_message;
    for (int idx = 0; idx < message.length(); idx++){

        char character = message.at(idx);
        int cypher_idx = alphabet.find(character);
        
        char encoded_character = key.at(cypher_idx);

        // encoded_message += encoded_character;
        message.at(idx) = encoded_character;
    }

    // cout << "Encoded Message (appended): " << encoded_message << endl; // Test code
    cout << "Encoded Message: " << message << endl; 
    cout << boolalpha; // Test Code
    // cout << "Messages the same: " << (encoded_message == message) << endl; // test code

    // string decoded_message; // Test Code
    for (int idx = 0; idx < message.length(); idx++){
        char encoded_character = message.at(idx);
        int decypher_idx = key.find(encoded_character);

        char decoded_character = alphabet.at(decypher_idx);

        // decoded_message += decoded_character; // test code
        message.at(idx) = decoded_character;
    }

    // cout << "Copy of origional message: " << origional_message << endl;
    // cout << "Decoded Message (appended): " << decoded_message << endl; // test code
    cout << "Decoded Message: " << message << endl;
    cout << "Messages the same: " << (origional_message == message) << endl;


    return 0;
}

