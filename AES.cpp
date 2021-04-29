#include "AES.h"

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
	
	
	unsigned char aes_key[16];
	memset(aes_key, 0, 16);
	
	cout << "Size of Key Array: " << sizeof(keyArray) << "\n";
	cout << "Key Array: " << keyArray << "\n";

	for(int i = 1; i < 17; ++i){
		aes_key[i - 1] = keyArray[i];
		// cout << "Key Array[i]: " << keyArray[i] << "\n";
		cout << "AES Key:      " << aes_key[i-1] << "\n";
	}

	/* AES-128 bit ECB Encryption key */
	// AES_KEY enc_key, dec_key;
	

	if(keyArray[0] == 0){

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
	unsigned char enc_out[17];
	
	/* Clear both buffers */
	memset(enc_out, 0, 17);

	//Encrypt the text
	AES_ecb_encrypt(plainText, enc_out, &enc_key, AES_ENCRYPT);
		
	return NULL;	
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
	unsigned char dec_out[17];

	//Clear both buffers
	memset(dec_out, 0, 17);

	// Decrypt!
	AES_ecb_encrypt(cipherText, dec_out, &dec_key, AES_DECRYPT);
		
	return NULL;
}



