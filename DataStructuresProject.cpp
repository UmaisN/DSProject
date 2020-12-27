#include <iostream>
#include"AVLTree.h"
#include"Hashing.h"
#include"DHT.h"
#include<cmath>
using namespace std;


int main()
{
    cout << " --------------------------------------------------" << endl;
    cout << "| EXAMPLE CODE FOR DHT USING 4 BIT IDENTIFIER SPACE |" << endl;
    cout << " --------------------------------------------------" << endl;

    DHT<int, string>dht1(4);
    dht1.insert_machine("1");
    dht1.insert_machine("2");
    dht1.insert_machine("3");
    dht1.insert_machine("4");


    cout << endl << " --------------------------------------------------" << endl;
    cout << "|    DISPLAYING ROUTING TABLES FOR ALL MACHINES     |" << endl;
    cout << " --------------------------------------------------" << endl;
    dht1.display_machines();


    cout << endl << endl << "Inserting the key 'Ibrahim' " << endl;
    dht1.insert_from_machine("1", "Ibrahim", "This is Ibrahim's Data");
    cout << endl << endl << "Inserting the key 'Noveen' " << endl;
    dht1.insert_from_machine("2", "Noveen", "This is Noveen's Data");
    cout << endl << endl << "Inserting the key 'Umais' " << endl;
    dht1.insert_from_machine("4", "Umais", "This is Umais's Data");
    cout << endl << endl << "Inserting the key 'Aamer' " << endl;
    dht1.insert_from_machine("3", "Aamer", "This is Aamer's Data");

    cout << endl << endl << "To also show duplicates, we will insert more data with the key 'Ibrahim' " << endl;
    dht1.insert_from_machine("2", "Ibrahim", "This is Ibrahim's Data Part 2");

    cout << endl << " --------------------------------------------------" << endl;
    cout << "|     DISPLAYING AVL TREES FOR ALL MACHINES       |" << endl;
    cout << " --------------------------------------------------" << endl;

    dht1.display_a_machine("1", 2);
    dht1.display_a_machine("2", 2);
    dht1.display_a_machine("3", 2);
    dht1.display_a_machine("4", 2);

    cout << endl << hash_value("Umais", 4);

    /*

    cout << " --------------------------------------------------" << endl;
    cout << "|                  USER  DRIVEN DHT                 |" << endl;
    cout << " --------------------------------------------------" << endl;

    int identifier_space, num_of_machines, manual_choice;
    string machine_id;
    cout << "Specify the size of the identifier space : ";
    cin >> identifier_space;
    DHT<int, string>dht2(identifier_space);

    cout << endl << "Specify the number of machines : ";
    cin >> num_of_machines;
    cout << "Do you want to manually assign the ID to each machine? Press 1 for YES: ";
    cin >> manual_choice;

    for (int i = 0; i < num_of_machines; i++)
    {
        if (manual_choice == 1) //If User is assigning IDs
        {
            cout << endl << "Input ID for Machine "<<i<<" : ";
            cin >> machine_id;
            //----------INPUT VALIDATION IF USER ENTERS AN ID WHICH ALREADY EXIST-----------//

            InfInt hashed_ID = hash_value(machine_id, identifier_space);


            while (dht2.check_ID(hashed_ID)) //Loop runs until a new ID is entered
            {
                cout <<endl<< "Entered ID already exists !" << endl;
                cout << "    Kindly Enter a new ID : ";
                cin >> machine_id;

                hashed_ID = hash_value(machine_id, identifier_space);//deriving hash of new ID
            }

            //Now that we have a unique hashed_ID, we can create the machine
            dht2.insert_machine(machine_id);

        }
        else //If Randomly Assigning ID
        {
            machine_id=gen_random(10); //Value 10 can be changed to anything, it does not matter in the long run
            //----------INPUT VALIDATION IF USER ENTERS AN ID WHICH ALREADY EXIST-----------//

            InfInt hashed_ID = hash_value(machine_id, identifier_space);


            while (dht2.check_ID(hashed_ID)) //Loop runs until a new ID is generated
            {
                machine_id=gen_random(10);
                hashed_ID = hash_value(machine_id, identifier_space);//deriving hash of new ID
            }

            //Now that we have a unique hashed_ID, we can create the machine
            dht2.insert_machine(machine_id);
        }

    }

    //Menu
    int choice = 0;
    while (choice != 10)
    {
        cout << "---------Menu-----------" << endl;
        cout << "1) Insert data in the form of key" << endl;
        cout << "2) Remove data by specifying the key from any machine" << endl;
        cout << "3) Print the routing table of a machine" << endl;
        cout << "4) Print the AVL tree of a machine" << endl;
        cout << "5) Print the routing tables of all machines" << endl;
        cout << "6) Add a new machine on the fly" << endl;
        cout << "7) Remove any machine" << endl;
        cout << "8) Exit" << endl;
        cout << endl;
        cout << "Please select an option: ";
        cin >> choice;
        if (choice == 1)
        {
            string key, data;
            cout << endl << "Input the key: ";
            cin >> key;
            cout << endl << "Input the data: ";
            cin >> data;
            cout << endl << "Input the Machine ID from which we will begin the insertion process: ";
            cin >> machine_id;
            dht2.insert_from_machine(machine_id, key, data);
        }
        else if (choice == 2)
        {
            string key, data;
            cout << endl << "Input the key: ";
            cin >> key;
            cout << endl << "Input the data: ";
            cin >> data;
            cout << endl << "Input the Machine ID from which we will begin the insertion process: ";
            cin >> machine_id;
            dht2.remove_from_machine(machine_id, key, data);
        }
        else if (choice == 3)
        {
            cout << endl << "Enter the ID of the machine: ";
            cin >> machine_id;
            dht2.display_a_machine(machine_id, 1);
        }
        else if (choice == 4)
        {
            cout << endl << "Enter the ID of the machine: ";
            cin >> machine_id;
            dht2.display_a_machine(machine_id, 2);
        }
        else if (choice == 5)
        {
            dht2.display_machines();
        }
        else if (choice == 6)
        {

        }
        else if (choice == 7)
        {

        }
        else if (choice == 8)
        {
            break;
        }
        else
        {
            cout << "Invalid option selected." << endl;
        }
    }
*/
}


