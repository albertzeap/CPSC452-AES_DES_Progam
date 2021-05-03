#include "AES.h"

/**
 * Converts a character into a hexidecimal integer
 * @param character - the character to convert
 * @return - the converted character, or 'z' on error
 */
unsigned char AES::charToHex(const char& character)
{
	/* Is the first digit 0-9 ? */	
	if(character >= '0' && character <= '9')	
		/* Convert the character to hex */
		return character - '0';
	/* It the first digit a letter 'a' - 'f'? */
	else if(character >= 'a' && character <= 'f')
		/* Conver the cgaracter to hex */
		return (character - 97) + 10;	
	/* Invalid character */
	else return 'z';
}


/**
 * Converts two characters into a hex integers
 * and then inserts the integers into the higher
 * and lower bits of the byte
 * @param twoChars - two charcters representing the
 * the hexidecimal nibbles of the byte.
 * @param twoChars - the two characters
 * @return - the byte containing having the
 * valud of two characters e.g. string "ab"
 * becomes hexidecimal integer 0xab.
 */
unsigned char AES::twoCharToHexByte(const unsigned char* twoChars)
{
	/* The byte */
	unsigned char singleByte;
	
	/* The second character */
	unsigned char secondChar;

	/* Convert the first character */
	if((singleByte = charToHex(twoChars[0])) == 'z') 
	{
		/* Invalid digit */
		return 'z';
	}
	
	/* Move the newly inserted nibble from the
	 * lower to upper nibble.
	 */
	singleByte = (singleByte << 4);
	
	/* Conver the second character */
	if((secondChar = charToHex(twoChars[1])) == 'z')
		return 'z'; 
	
	/* Insert the second value into the lower nibble */	
	singleByte |= secondChar;

	return singleByte;
}





/**
 * Sets the key to use
 * @param key - the first byte of this represents whether
 * to encrypt or to decrypt. 00 means encrypt and any other
 * value to decrypt.  Then come the bytes of the 128-bit key
 * (should be 16 of them).
 * @return - True if the key is valid and False otherwise
 */
bool AES::setKey(const unsigned char* keyArray)
{
	// TODO: AES implementation of openssl cares about whether
	// you are encrypting or decrypting when setting the key.
	// That is, when encrypting you use function AES_set_encrypt_key(...)
	// and when decrypting AES_set_decrypt_key(...).
	//
	// One way to solve this problem is to pass in a 17 byte key, where
	// the first byte is used to indicate whether we are encrypting or
	// decrypting. E.g., if the first byte is 0, then use AES_set_encrypt_key(...).
	// Otherwise, use AES_set_decrypt_key(...).  The rest of the bytes in the
	// array indicate the 16 bytes of the 128-bit AES key.
	//
	// Both functions return 0 on success and other values on faliure.
	// For documentation, please see https://boringssl.googlesource.com/boringssl/+/2623/include/openssl/aes.h
	// and aes.cpp example provided with the assignment.

	unsigned char* aes_key = new unsigned char[16];
	char* buffer;
	int counter = 0;

	cout << "KEY: ";

	//Traverse through the key elements
	for (int i = 2; i < 33; i){

		//Store two chars in temp string
		string temp = "";
		temp += keyArray[i-1];
		temp += keyArray[i];

		//Convert string to char*
		buffer = &temp[0];	

		cout << buffer << " ";
		
		//Initialize aes_key with the hexBytes
		if (counter < 16){
			aes_key[counter] = twoCharToHexByte((unsigned char*)buffer);
		}

		//Increment counters
		counter++;
		i += 2;

	}
	cout << "\n";

	if(keyArray[0] == '0'){

		/* Set the encryption key */
		if(AES_set_encrypt_key(aes_key, 128, &enc_key)!= 0){
			fprintf(stderr, "AES_set_encrypt_key() failed!\n");
			exit(-1);
		}
		else {
			return true;
		}
	}
	else{
	
		/* Set the decryption key */
		if(AES_set_decrypt_key(aes_key, 128, &dec_key) != 0){
			fprintf(stderr, "AES_set_decrypt_key() failed!\n");
			exit(-1);
		}
		else {
			return true;
		}
	}

	return false;
	
}

/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
unsigned char* AES::encrypt(const unsigned char* plainText)
{
	
	//TODO: 1. Dynamically allocate a block to store the ciphertext.
	//	2. Use AES_ecb_encrypt(...) to encrypt the text (please see the URL in setKey(...)
	//	and the aes.cpp example provided.
	// 	3. Return the pointer to the ciphertext

	//Buffers for string text
	unsigned char buffer[16];
	unsigned char* enc_out = new unsigned char[16];
	
	//Clear both buffers 
	memset(enc_out, 0, 16);
	memset(buffer, 0, 16);

	//Encrypt the text
	AES_ecb_encrypt(plainText, buffer, &enc_key, AES_ENCRYPT);
		
	for (int i = 0; i < 16; ++i){
		enc_out[i] = buffer[i];
	}

	return enc_out;	
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
unsigned char* AES::decrypt(const unsigned char* cipherText)
{
	
	//TODO: 1. Dynamically allocate a block to store the plaintext.
	//	2. Use AES_ecb_encrypt(...) to decrypt the text (please see the URL in setKey(...)
	//	and the aes.cpp example provided.
	// 	3. Return the pointer to the plaintext

	//Buffers for string text
	unsigned char buffer[16];
	unsigned char* dec_out = new unsigned char[16];

	//Clear the buffers
	memset(buffer, 0, 16);
	memset(dec_out, 0, 16);

	// Decrypt!
	AES_ecb_encrypt(cipherText, buffer, &dec_key, AES_DECRYPT);

	for(int i = 0; i < 16; ++i){
		dec_out[i] = buffer[i];
	}
		
	return dec_out;
}



