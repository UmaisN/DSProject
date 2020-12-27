#include <iostream>
#include"AVLTree.h"
#include"Hashing.h"
#include"DHT.h"
#include<cmath>
using namespace std;

int main()
{
    cout << gen_random(10) << endl;

    //DHT<int, string> mach;

    /////Testing Convert Hex Function///////

    //cout << convert_hex("1E0F4") << endl;
    //cout << convert_hex("1EF4") << endl;
    //cout << convert_hex("1F4") << endl;
    //cout << string_ascii("i192002") << endl;
    //cout << string_ascii("i192020") << endl;

    //Int to Hex testing
    //InfInt x = 124134;
    //cout << int_to_hex(x)<<endl;

    ////Hash function testing

    ////Result first char should be 2, rest should match with online Hasher -- RESULT PASSED
    //string key = "a";
    ////cout << key << endl;
    //cout << hash_value("ibrahi", 7) << endl;
    //cout << hash_value("sfsf1ab", 7) << endl;
    //cout << hash_value("facvvc", 7) << endl;
    //cout << hash_value("skfhba", 7) << endl;
    //cout << hash_value("vbuybihe", 7) << endl;
    //cout << hash_value("afkhbvf", 7) << endl;
    //cout << hash_value("giucbe", 7) << endl;
    //cout << hash_value("hnmdvhj", 7) << endl;

    ////Result first char should be 0 (NULL), rest should match with online Hasher -- RESULT PASSED (3608bca)
    //key = hash_value("xyz",29);
    //cout << key << endl;

    ////Result first char should be 4, rest should match with online Hasher -- RESULT PASSED (9baf34a4)
    //key = hash_value("max", 31);
    //cout << key << endl;

    ////Result first char should be 0, rest should match with online Hasher -- RESULT PASSED (d93473b8)
    //key = hash_value("ibrahimis", 32);
    //cout << key << endl;

    //cout << hash_value("Ibrahim", 4) << endl;
    //cout << hash_value("Noveen", 4) << endl;
    //cout << hash_value("Jaan", 4) << endl;
    //cout << hash_value("Omais", 4) << endl;
    //cout << hash_value("Momin", 4) << endl;

    //Testing AVL
    //AVL<int, string> obj;
    //obj.set_AVL_specs("exfile.txt",4);     //ALWAYS SET ID SPACE OF AVL BEFORE USING IT

    //obj.insert("Ibrahim", "Aamer");
    //obj.insert("Noveen", "Fatima");
    //obj.insert("Omais", "Nisar");
    //obj.insert("Momin", "Tariq");
    //obj.insert("Noveen", "hello");
    //obj.insert("Momin1", "Tariq");

    //obj.display();
    //obj.deleteNode("Omais");
    //obj.display();
    //Node<int, string>* nd;
    //nd = obj.searchNode("Ibrahim");
    //cout << nd->hashed_key << endl;
    //cout <<nd->original_key<<" "<< nd->line_no << endl;
    //nd = obj.searchNode("Noveen");
    //cout << nd->hashed_key << endl;
    //cout << nd->original_key << " " << nd->line_no << endl;
    //nd = obj.searchNode("Omais");
    //cout<<nd->hashed_key<<endl;
    //cout << nd->original_key << " " << nd->line_no << endl;
    //nd = obj.searchNode("Momin");
    //cout << nd->hashed_key << endl;
    //cout << nd->original_key << " " << nd->line_no << endl;
    //nd = obj.searchNode("Momin1");
    //cout << nd->hashed_key << endl;
   // cout << nd->original_key << " " << nd->line_no << endl;
   // cout<<"search"<<nd->next->original_key << endl;

    //Machine_node<int, string> nod("machine1",5, 4);

    //nod.insert("ibrahim", "aamer");
    //nod.insert("umais", "nisar");
    //nod.insert("noveen", "fatima");
    //nod.insert("noveen", "fatima");

    //nod.display_data();

    //InfInt y = 1024;
    //cout << log2(y) << endl;

    DHT<int, string> obj(8);

    cout << "M1 " << hash_value("M1", 8) << endl;
    cout << "M2 " << hash_value("M2", 8) << endl;
    cout << "M3 " << hash_value("M3", 8) << endl;
    cout << "M4 " << hash_value("M4", 8) << endl;
    cout << "M5 " << hash_value("M5", 8) << endl;
    cout << "M6 " << hash_value("M6", 8) << endl;
    cout << "M7 " << hash_value("M7", 8) << endl;
    cout << "M8 " << hash_value("M8", 8) << endl;
    cout << "M9 " << hash_value("M9", 8) << endl;
    cout << "M10 " << hash_value("M10", 8) << endl;
    cout << "M11 " << hash_value("M11", 8) << endl;


    obj.insert_machine("M1");
    obj.insert_machine("M2");
    obj.insert_machine("M3");
    obj.insert_machine("M4");
    obj.insert_machine("M5");
    obj.insert_machine("M6");
    obj.insert_machine("M7");
    obj.insert_machine("M8");
    obj.insert_machine("M9");
    obj.insert_machine("M10");
    obj.insert_machine("M11");
    obj.insert_machine("M12");
    obj.insert_machine("M13");
    obj.insert_machine("M14");
    obj.insert_machine("M15");
    obj.insert_machine("M16");
    obj.insert_machine("M17");
    obj.insert_machine("M18");

    cout << endl;


    obj.display_machines();

    cout << hash_value("ibrahim", 8) << endl;

    obj.insert_from_machine("M7", "ibrahim", "aamer");
    obj.insert_from_machine("M7", "ibrahim", "Musa");

    obj.display_a_machine("M4", 2);


    /*	//----------INPUT VALIDATION IF USER ENTERS AN ID WHICH ALREADY EXIST-----------//

        InfInt hashed_ID = hash_value(machine_id, this->ID_space);


        while (this->check_ID(hashed_ID)) //Loop runs until a new ID is entered
        {
            cout << "Entered ID already exists !" << endl;
            cout << "    Kindly Enter a new ID : ";
            cin >> machine_id;

            hashed_ID = hash_value(machine_id, this->ID_space);//deriving hash of new ID
        }

        //------------------------------------------------------------------------------//
    */

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


