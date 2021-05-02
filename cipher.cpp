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
	FILE* fpIn = fopen(cipherIP, "r");
	FILE* fpOut = fopen(cipherOP, "w");

	//The buffer to store the read text
	char buffer[17];

	//The number of bytes read
	int numRead = -1;

	//Checks if file was not opened
	if(!fpIn){
		perror("fopen");
		exit(-1);
	}

	if(!fpOut)
	{
		perror("Cannot open the file for output.");
		exit(1);
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

		//Blocks to be read
		unsigned char* block = new unsigned char[8];

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

		//Set the key
		cipher->setKey((unsigned char*)validKey);

		if(cipherM == "ENC")
		{

			//read till end of file
			unsigned char* cipherText = new unsigned char;
			while(!feof(fpIn))
			{
				numRead = fread(block, 1, 8, fpIn);
				//Not end of file yet
				if(numRead != 0)
				{
					//Padding
					if(numRead < 8)
					{
						memset(block+numRead, 0,8 - numRead);
					}
						cipherText = cipher->encrypt(block);
						fwrite(cipherText, 1, 8, fpOut);
						
				}
			}
		}
		else if(cipherM == "DEC")
		{
			//read till end of file
			unsigned char* plainText = new unsigned char;
			while(!feof(fpIn))
			{
				numRead = fread(block, 1, 8, fpIn);
				//Not end of file yet
				if(numRead != 0)
				{
					//Padding
					if(numRead < 8)
					{
						memset(block+numRead, 0,8 - numRead);
					}
						plainText = cipher->decrypt(block);
						fwrite(plainText, 1, 8, fpOut);
		
						
				}
			}
		
		}
	}




	//Create AES object
	if(cipherN == "AES"){
		cout << "BLOCK CIPHER: AES\n";
		
		//Block to be read
		unsigned char* block = new unsigned char[16];

		//Checks if key is a valid length
		if (cipherK.length() != 32){
			fprintf(stderr, "INVALID KEY: Key needs to be 32 characters long\n");
			exit(-1);
		}
		else {
			if(cipherM == "ENC"){
				cipherK.insert(0, 1,'0'); 
			}
			if(cipherM == "DEC"){
				cipherK.insert(0,1,'1');
			}
			
			//Initializes the valid key
			validKey = &cipherK[0];
		}


		//Create an AES object
		cipher = new AES();

		//Set key
		cipher->setKey((unsigned char*)validKey);

		if(cipherM == "ENC")
		{

			//read till end of file
			unsigned char* cipherText = new unsigned char;
			while(!feof(fpIn))
			{
				numRead = fread(block, 1, 16, fpIn);
				//Not end of file yet
				if(numRead != 0)
				{
					//Padding
					if(numRead < 16)
					{
						memset(block+numRead, 0,16 - numRead);
					}
						cipherText = cipher->encrypt(block);
						fwrite(cipherText, 1, 16, fpOut);
						
				}
			}
		}
		else if(cipherM == "DEC")
		{
			//read till end of file
			unsigned char* plainText = new unsigned char;
			while(!feof(fpIn))
			{
				numRead = fread(block, 1, 16, fpIn);
				//Not end of file yet
				if(numRead != 0)
				{
					//Padding
					if(numRead < 16)
					{
						memset(block+numRead, 0,16 - numRead);
					}
						plainText = cipher->decrypt(block);
						fwrite(plainText, 1, 16, fpOut);
		
						
				}
			}
		
		}






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
	// cipher->setKey((unsigned char*)validKey);


	/* Perform encryption */
	// if (cipherM == "ENC"){

		// string cipherText = cipher->encrypt((unsigned char*)"hello world");
		// cipher->encrypt((unsigned char*)"helloworld123456");
	// }

	/* Perform decryption */
	// else{
		// cipher->decrypt(cipherText);	
	// }
	
	return 0;
}
