#include <string>
#include <iostream>
#include <fstream>

#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"

using namespace std;

int main(int argc, char** argv)
{
	/**
	 * TODO: Replace the code below	with your code which can SWITCH
	 * between DES and AES and encrypt files. DO NOT FORGET TO PAD
	 * THE LAST BLOCK IF NECESSARY.
	 *
	 * NOTE: due to the incomplete skeleton, the code may crash or
	 * misbehave.
	 */
		

	//Error check the current command line arguments. Exits upon error
	if(argc != 6){
		fprintf(stderr, "Usage: <CIPHER NAME> <KEY> <ENC/DEC> <INPUTFILE> <OUTPUT FILE>\n");
		exit(-1);
	}

	//Store the command line arguments
	string cipherN = argv[1];
	string cipherK = argv[2];
	string cipherM = argv[3];
	char* cipherIP = argv[4];
	char* cipherOP = argv[5];

	//Variable for valid key
	char* validKey;

	//Create a file object to read the file
	FILE* fp = fopen(cipherIP, "r");

	//The buffer to store the read text
	char buffer[17];

	//The number of bytes read
	int numRead = 0;

	//Checks if file was not opened
	if(!fp){
		perror("fopen");
		exit(-1);
	}

	//Checks for proper mode before continuing program
	if (cipherM != "ENC" && cipherM != "DEC"){
		fprintf(stderr, "INVALID MODE: <ENC> || <DEC>\n");
		exit(-1);
	}
	
	//Print menu if all error checks are passed successfully
	cout << "AES && DES Program\n";
	for(int i = 0; i < 45; ++i){
		cout << "=";
	}
	cout << "\n";

	/* Create an instance of the cipher */	
	CipherInterface* cipher = NULL; 

	//Create DES object
	if(cipherN == "DES"){
		cout << "BLOCK CIPHER: DES\n";

		//Checks if key is a valid length
		if (cipherK.length() != 16){
		fprintf(stderr, "INVALID KEY: Key needs to be 16 characters long\n");
		exit(-1);
		}
		else {

			//Initializes the valid key
			validKey = &cipherK[0];
		}	

		//Create a DES object
		cipher = new DES();
	}

	//Create AES object
	if(cipherN == "AES"){
		cout << "BLOCK CIPHER: AES\n";

		//Checks if key is a valid length
		if (cipherK.length() != 32){
			fprintf(stderr, "INVALID KEY: Key needs to be 32 characters long\n");
			exit(-1);
		}
		else {

			//Initializes the valid key
			validKey = &cipherK[0];
		}

		//Create an AES object
		cipher = new AES();
	}

	/* Error checks */
	if(!cipher)
	{
		fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
		__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}


	/* Set the encryption key
	 * A valid key comprises 16 hexidecimal
	 * characters. Below is one example.
	 * Your program should take input from
	 * command line.
	 */


	// cipher->setKey((unsigned char*)"0123456789abcdef");
	cipher->setKey((unsigned char*)validKey);


	/* Perform encryption */
	if (cipherM == "ENC"){

		// string cipherText = cipher->encrypt((unsigned char*)"hello world");
	}

	/* Perform decryption */
	else{
		// cipher->decrypt(cipherText);	
	}
	
	return 0;
}
