#pragma once
#include"sha256.h"
#include"InfInt.h"
#include<iostream>
#include<cmath>
using namespace std;


int hex_to_int(char c)
{
	int val=0;
	if (c == '0')
	{
		val = 0;
	}
	else if (c == '1')
	{
		val = 1;
	}
	else if (c == '2')
	{
		val = 2;
	}
	else if (c == '3')
	{
		val = 3;
	}
	else if (c == '4')
	{
		val = 4;
	}
	else if (c == '5')
	{
		val = 5;
	}
	else if (c == '6')
	{
		val = 6;
	}
	else if (c == '7')
	{
		val = 7;
	}
	else if (c == '8')
	{
		val = 8;
	}
	else if (c == '9')
	{
		val = 9;
	}
	else if ((c == 'a')or (c == 'A'))
	{
		val = 10;
	}
	else if ((c == 'b') or (c == 'B'))
	{
		val = 11;
	}
	else if ((c == 'c') or (c == 'C'))
	{
		val = 12;
	}
	else if ((c == 'd') or (c == 'D'))
	{
		val = 13;
	}
	else if ((c == 'e') or (c == 'E'))
	{
		val = 14;
	}
	else if ((c == 'f') or (c == 'F'))
	{
		val = 15;
	}

	return val;

}



//Function to raise an InfInt to a given power
InfInt InfIntpow(InfInt base_num,InfInt exponent) 
{
	InfInt result = 1;//storing result

	for (InfInt c = 0; c < exponent; ++c) 
	{
		result = result * base_num;//adding in result
	}

	return result;
}

//This function converts a hexadecimal string to InfInt
InfInt convert_hex(string hex)
{
	InfInt val = 0;
	InfInt exponent = 0;
	InfInt exponentvalue = 0;

	int stringlength = hex.length();
	stringlength--;
	for (int i = stringlength; i >= 0; i--)
	{
		exponentvalue = InfIntpow(16, exponent);
		val = val + (exponentvalue * hex_to_int(hex[i]));
		exponent++;
	}

	return val;
}

string int_to_hex(InfInt id)
{
	string hex = "";
	InfInt temp;

	while (id != 0)
	{
		temp = id % 16;
		id = id / 16;
		
		if (temp == 0)
		{
			hex = '0' + hex;
		}
		else if (temp == 1)
		{
			hex = '1' + hex;
		}
		else if (temp == 2)
		{
			hex = '2' + hex;
		}
		else if (temp == 3)
		{
			hex = '3' + hex;
		}
		else if (temp == 4)
		{
			hex = '4' + hex;
		}
		else if (temp == 5)
		{
			hex = '5' + hex;
		}
		else if (temp == 6)
		{
			hex = '6' + hex;
		}
		else if (temp == 7)
		{
			hex = '7' + hex;
		}
		else if (temp == 8)
		{
			hex = '8' + hex;
		}
		else if (temp == 9)
		{
			hex = '9' + hex;
		}
		else if (temp == 10)
		{
			hex = 'a' + hex;
		}
		else if (temp == 11)
		{
			hex = 'b' + hex;
		}
		else if (temp == 12)
		{
			hex = 'c' + hex;
		}
		else if (temp == 13)
		{
			hex = 'd' + hex;
		}
		else if (temp == 14)
		{
			hex = 'e' + hex;
		}
		else if (temp == 15)
		{
			hex = 'f' + hex;
		}

	}
	return hex;
}


InfInt hash_value(string key, int num_bits)  //Can return a hash value of 1-256 bits
{
	SHA256 sha256;
	string hashed_value = sha256(key);
	InfInt final_hash = convert_hex(hashed_value);

	if (num_bits != 256)
	{
		/////////////APROACH 1/////////////
		//This approach is used when we are returning an InfInt
		InfInt max_value = InfIntpow(2, num_bits);
		final_hash = final_hash % max_value;


		/////////////APPROACH 2////////////
		//This approach was used when we were dealing with strings. We were returning a string in hexadecimal representation
		/*
		//Over here we are not using a % approach since calculating the denary value of this hash function is not possible with the current library
		//So simply we will take the number of bits we need

		int num_halfbytes = num_bits / 4;
		int remaining_bits = num_bits % 4;
		hashed_value = hashed_value.substr(0, num_halfbytes);


		//If the num_bits was not a multiple of 4, we have some bits that we still need to cater to. Their possible values are 0,1,2 or 3

		//In all these scenarios I'm simply dividing the space 0-15 into subspaces (the size depends on the number of remaining bits)
		//We'll append a value that can be produced in those number of bits that we have left over, at the start of our hashed value to get a hashed_value that is truly that number of bits
		if (remaining_bits == 1)
		{
			int check_value = hex_to_int(hashed_value[0]);
			if (check_value <= 7)
			{
				//Commenting this out because it makes no difference if you add a zero at the start of a number
				//hashed_value = '0' + hashed_value;
			}
			else
			{
				hashed_value = '1' + hashed_value;
			}
		}
		else if (remaining_bits == 2)
		{
			int check_value = hex_to_int(hashed_value[0]);
			if (check_value <= 3)
			{
				//hashed_value = '0' + hashed_value;
			}
			else if(check_value<=7)
			{
				hashed_value = '1' + hashed_value;
			}
			else if (check_value <= 11)
			{
				hashed_value = '2' + hashed_value;
			}
			else
			{
				hashed_value = '3' + hashed_value;
			}
		}
		else if (remaining_bits == 3)
		{
			int check_value = hex_to_int(hashed_value[0]);
			if (check_value <= 1)
			{
				//hashed_value = '0' + hashed_value;
			}
			else if (check_value <= 3)
			{
				hashed_value = '1' + hashed_value;
			}
			else if (check_value <= 5)
			{
				hashed_value = '2' + hashed_value;
			}
			else if (check_value <= 7)
			{
				hashed_value = '3' + hashed_value;
			}
			else if (check_value <= 9)
			{
				hashed_value = '4' + hashed_value;
			}
			else if (check_value <= 11)
			{
				hashed_value = '5' + hashed_value;
			}
			else if (check_value <= 13)
			{
				hashed_value = '6' + hashed_value;
			}
			else
			{
				hashed_value = '7' + hashed_value;
			}
		}
		*/
	}

	return final_hash;
}

InfInt log2(InfInt val)
{
	InfInt i = 0;
	while (InfIntpow(2, i) < val)
	{
		i++;
	}

	return i;
}