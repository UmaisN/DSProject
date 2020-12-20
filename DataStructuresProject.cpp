#include <iostream>
//#include"AVLTree.h"
//#include"Hashing.h"
#include"DHT.h"
using namespace std;

int main()
{
    cout << string_ascii("i192002") << endl;
    cout << string_ascii("i192020") << endl;

    //Int to Hex testing
    //InfInt x = 124134;
    //cout << int_to_hex(x)<<endl;

    ////Hash function testing

    ////Result first char should be 2, rest should match with online Hasher -- RESULT PASSED
    //string key = hash_value("abcdefgh", 30);
    //cout << key << endl;

    ////Result first char should be 0 (NULL), rest should match with online Hasher -- RESULT PASSED (3608bca)
    //key = hash_value("xyz",29);
    //cout << key << endl;

    ////Result first char should be 4, rest should match with online Hasher -- RESULT PASSED (9baf34a4)
    //key = hash_value("max", 31);
    //cout << key << endl;

    ////Result first char should be 0, rest should match with online Hasher -- RESULT PASSED (d93473b8)
    //key = hash_value("ibrahimis", 32);
    //cout << key << endl;


    //Testing AVL
    AVL<int, string> obj;
    obj.insert("ibrahim", "Aamer");
    obj.insert("Noveen", "Fatima");
    obj.insert("Omais", "Nisar");
    obj.display();
    obj.deleteNode("ibrahim");
    obj.display();
    obj.searchNode("Noveen");

    InfInt x = 2;
    InfInt y = 2;
    cout << InfIntpow(x, y) << endl;
    //Menu
 /*   int choice = 0;
    while (choice != 10) {
        cout << "---------Menu-----------" << endl;
        cout << "1) Specify the number of machines " << endl;
        cout << "2) Specify the size of identifier space" << endl;
        cout << "3) Manually assign Id to each machine" << endl;
        cout << "4) Insert data in the form of key" << endl;
        cout << "5) Remove data by specifying the key from any machine" << endl;
        cout << "6) Print the routing table of any machine" << endl;
        cout << "7) Print the AVL tree on any machine" << endl;
        cout << "8) Add new machines" << endl;
        cout << "9) Remove any machine" << endl;
        cout << "10) Exit" << endl;
        cout << endl;
        cout << "Please select an option: ";
        cin >> choice;
        if (choice == 1) {

        }
        else if (choice == 2) {

        }
        else if (choice == 3) {

        }
        else if (choice == 4) {

        }
        else if (choice == 5) {

        }
        else if (choice == 6) {

        }
        else if (choice == 7) {

        }
        else if (choice == 8) {

        }
        else if (choice == 9) {

        }
        else if (choice == 10) {
            break;
        }
        else {
            cout << "Invalid option selected." << endl;
        }
    }*/
}


