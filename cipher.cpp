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
	string cipherIP = argv[4];
	string cipherOP = argv[5];

	//File objects
	fstream inputFile, outputFile;			
	inputFile.open (cipherIP, ios::in );	

	//Error checks for file
	if(!inputFile){
		fprintf(stderr, "ERROR: Invalid file\n");
		exit(-1);
	}

	//Store the contents of the file into a string
	string fileContents;					
	while(!inputFile.eof()){
		inputFile >> fileContents;
	}
	
	//Closing file afer open
	if (inputFile.is_open()){
		inputFile.close();
	}

	//Print menu if all error checks are passed successfully
	cout << "AES && DES Program\n";
	for(int i = 0; i < 45; ++i){
		cout << "=";
	}
	cout << "\n";

	/* Create an instance of the DES cipher */	
	CipherInterface* cipher = NULL; 

	//Create DES object
	if(cipherN == "DES"){
		cout << "BLOCK CIPHER: DES\n";
		cipher = new DES();
	}

	//Create AES object
	if(cipherN == "AES"){
		cout << "BLOCK CIPHER: AES\n";
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
	cipher->setKey((unsigned char*)"0123456789abcdef");
	
	/* Perform encryption */
	//string cipherText = cipher->encrypt("hello world");
	
	/* Perform decryption */
	//cipher->decrypt(cipherText);	
	
	return 0;
}
