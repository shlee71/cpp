#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
 
int padding = RSA_PKCS1_PADDING;
 
RSA * createRSA(unsigned char * key,int public)
{
    RSA *rsa= NULL;
    BIO *keybio ;
    // 읽기 전용 메모리 만들기 BIO
    keybio = BIO_new_mem_buf(key, -1); 
    if (keybio==NULL)
    {
        printf( "Failed to create key BIO");
        return 0;
    }
    
    /* PEM형식인 키 파일을 읽어와서 RSA 구조체 형식으로 변환 */
    
    if(public) // PEM public 키로 RSA 생성
    {
        rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
    }
    else // PEM private 키로 RSA 생성
    {
        rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
    }
    
    if(rsa == NULL)
    {
        printf( "Failed to create RSA");
    }
 
    return rsa;
}
/* 공개키로 암호화 */
int public_encrypt(unsigned char * data,int data_len,unsigned char * key, unsigned char *encrypted) 
{
    RSA * rsa = createRSA(key,1);
    int result = RSA_public_encrypt(data_len,data,encrypted,rsa,padding);
    return result; // RSA_public_encrypt() returns the size of the encrypted data 
}
/* 개인키로 복호화 */
int private_decrypt(unsigned char * enc_data,int data_len,unsigned char * key, unsigned char *decrypted)
{
    RSA * rsa = createRSA(key,0);
    int  result = RSA_private_decrypt(data_len,enc_data,decrypted,rsa,padding);
    return result;
}
/* 개인키로 암호화 */
int private_encrypt(unsigned char * data,int data_len,unsigned char * key, unsigned char *encrypted)
{
    RSA * rsa = createRSA(key,0);
    int result = RSA_private_encrypt(data_len,data,encrypted,rsa,padding);
    return result;
}
/* 공개키로 복호화 */
int public_decrypt(unsigned char * enc_data,int data_len,unsigned char * key, unsigned char *decrypted)
{
    RSA * rsa = createRSA(key,1);
    int  result = RSA_public_decrypt(data_len,enc_data,decrypted,rsa,padding);
    return result;
}
/* 에러날 때 해당 에러문 출력 */
void printLastError(char *msg)
{
    char * err = malloc(130);;
    ERR_load_crypto_strings();
    ERR_error_string(ERR_get_error(), err);
    printf("%s ERROR: %s\n",msg, err);
    free(err);
}
size_t calcDecodeLength(const char* b64input) { //Calculates the length of a decoded string
	size_t len = strlen(b64input),
		padding = 0;

	if (b64input[len-1] == '=' && b64input[len-2] == '=') //last two chars are =
		padding = 2;
	else if (b64input[len-1] == '=') //last char is =
		padding = 1;

	return (len*3)/4 - padding;
}
int Base64Encode(const unsigned char* buffer, size_t length, char** b64text) 
{ 
    //Encodes a binary safe base 64 string
	BIO *bio, *b64;
	BUF_MEM *bufferPtr;

	b64 = BIO_new(BIO_f_base64());
	bio = BIO_new(BIO_s_mem());
	bio = BIO_push(b64, bio);

	BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Ignore newlines - write everything in one line
	BIO_write(bio, buffer, length);
	BIO_flush(bio);
	BIO_get_mem_ptr(bio, &bufferPtr);
	BIO_set_close(bio, BIO_NOCLOSE);
	BIO_free_all(bio);

	*b64text=(*bufferPtr).data;

	return (0); //success
    size_t calcDecodeLength(const char* b64input) { //Calculates the length of a decoded string
	size_t len = strlen(b64input),
		padding = 0;

	if (b64input[len-1] == '=' && b64input[len-2] == '=') //last two chars are =
		padding = 2;
	else if (b64input[len-1] == '=') //last char is =
		padding = 1;

	return (len*3)/4 - padding;
	}
}

int Base64Decode(char* b64message, unsigned char** buffer, size_t* length) 
{
    //Decodes a base64 encoded string
	BIO *bio, *b64;

	int decodeLen = calcDecodeLength(b64message);
	*buffer = (unsigned char*)malloc(decodeLen + 1);
	(*buffer)[decodeLen] = '\0';

	bio = BIO_new_mem_buf(b64message, -1);
	b64 = BIO_new(BIO_f_base64());
	bio = BIO_push(b64, bio);

	BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Do not use newlines to flush buffer
	*length = BIO_read(bio, *buffer, strlen(b64message));
	assert(*length == decodeLen); //length should equal decodeLen, else something went horribly wrong
	BIO_free_all(bio);

	return (0); //success
}

 
int main(int argc, char *argv)
{
 
    char plainText[2048/8] = "This is test Text"; //key length : 2048
 
 /*
    char publicKey[]="-----BEGIN PUBLIC KEY-----\n"\
               "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA1qm64PJaW3eYJhdG6zeW\n"\
               "3fDKIQH0fFMobzvIw7mz5MjTgKABZnjxW/wQzdu370WnxCFixo36xZ/e4eUiPTwC\n"\
               "zzNFS0lE29OcgXiqLzCtu6ykyTEvhuQ/86F7zspRGuAaiA3t+695s3lep63viMuF\n"\
               "ACTHcrWv1aeK8JUM//H1cOf3KGv+VFp1dYPZSNsM5cDWfR3VZJdRJwT1iPfJUFkF\n"\
               "YQaDIKFeDV4HO7i8fSHZ8O25dRgy0v/HQYBrx66vjF8P7dtlHhGcdaMF5XHmrMb3\n"\
               "6YssQglDBWO1TZNtabtV02SLVY8i8GijXinUcW/hzZ6Sl6VNfzpFxqsiM7GObnNP\n"\
               "7QIDAQAB\n"\
               "-----END PUBLIC KEY-----\n";

    char privateKey[]="-----BEGIN RSA PRIVATE KEY-----\n"\
               "MIIEowIBAAKCAQEA1qm64PJaW3eYJhdG6zeW3fDKIQH0fFMobzvIw7mz5MjTgKAB\n"\
               "ZnjxW/wQzdu370WnxCFixo36xZ/e4eUiPTwCzzNFS0lE29OcgXiqLzCtu6ykyTEv\n"\
               "huQ/86F7zspRGuAaiA3t+695s3lep63viMuFACTHcrWv1aeK8JUM//H1cOf3KGv+\n"\
               "VFp1dYPZSNsM5cDWfR3VZJdRJwT1iPfJUFkFYQaDIKFeDV4HO7i8fSHZ8O25dRgy\n"\
               "0v/HQYBrx66vjF8P7dtlHhGcdaMF5XHmrMb36YssQglDBWO1TZNtabtV02SLVY8i\n"\
               "8GijXinUcW/hzZ6Sl6VNfzpFxqsiM7GObnNP7QIDAQABAoIBAQDRN0e+ajaKozsV\n"\
               "FOa35cwSr9Yw6XjhmyLzlq8Lo/ii6ODKoif7ObDzV+8A1D6m45qpW2ir4EEjT7ep\n"\
               "Lut6Bv0t+Oh2ggisv8fvoC0uJSGOoqtQs7GApQF3cFH8r87whK8XH4xtGw9gTtBk\n"\
               "WO/2wXT1OONy94VSlSKjbIHpCmePC50xWMcur595KT8TCWhokxXrUCwLFgAki9Ld\n"\
               "4g+U6PJW67HDm5vi/0MUdnawa0GkaH1HGpNEGJNo74ZcB+jSJBlWrrCk7Hic1tpV\n"\
               "OCNxnHxeWkBDLYwXoq7kS7T72aWuZuBVLczOzM3DHg7W/CpaJZuGaWqhxMgSUkmW\n"\
               "c6861A9BAoGBAOsm6eWvI8fazMkedsBfLaUsXzWHYY2sXr0kRfkwjxZxpDpYsaLU\n"\
               "j/t7uhpgj+G7Sk3B5mqJNpVX+5jXL3tKuh3PIXa3uGXLyv50SGYZfQ7WVJS0c7ID\n"\
               "gqcSmDTXo26gM65pflIDO9rm4zcQ2V5yR5IJ87aCNnbsXihkhk4vox2pAoGBAOmx\n"\
               "ypbAdLxVj2BGMEdbBvqGpHKP123P7/W2EzkQGYyQ4sAfbFazmh6OXN7Dc3H6hX20\n"\
               "fl0ZOAwUZDoEIm0Sc6SOYtGFPq7jC+9ACBDWG8moaJNxeUHzcpaG3UTWKzsmJ6yH\n"\
               "2AY8rVBZibsm2KNQgK9/ciYSw5gf5GsX5BqqUuKlAoGAGMd++j8cbCD4V3EoXlkp\n"\
               "PDCSz9c2RnGVgiTiYsHlMh5DigpynY/8pCmDkOgAAW91AwCdwTg4UkB1OMPkMv/K\n"\
               "4P1Er3forIFvIKUsQ+YHsZqQSyNA1c9c4zIoa9kVVcD38TcYopfIpOaTpufVoAg2\n"\
               "1oLJ9b9+8cUyntsI9BA9BhECgYAghT1L/TxBeSaanynYxDIUaug3iQzRmz4pU00Z\n"\
               "g8QKa58iXT0WU6f+2JDT7x8BnXs2IwfyrK+//pZz/F9ODmNJYwcdYQ14COCASsjU\n"\
               "jvcO+QCUhBX7t4UarWndSnB5qrWarMzDEW6M3+jqwl0jXPCLe5DG+5V8dfOzc3+q\n"\
               "tkkSgQKBgC6QnAhzi8QWT/pe6EjPmOlbplIsCJMxi1cmINZ8DtxxYcOBV2xznQ71\n"\
               "vY3Sb0PSNyBh9rGBlZLtCjB/zLAcXxMD1QeqBw6w92fVmF4goGiyc8pdo2ngfCga\n"\
               "Jbl8WTlUY7jH+3Ki7c0FgWVH2MzQol1B3AqHQsSST25nSbw+9Pm1\n"\
               "-----END RSA PRIVATE KEY-----\n";
*/
    char publicKey[5000];
    char privateKey[5000];
    char buf[1000];

    FILE *fp = NULL;
    int pos_len;
 
    unsigned char encrypted[4098]={}; // variable for encrypted data
    unsigned char decrypted[4098]={}; // variable for decrypted data
 
    // publicKey read from public.pem file
    pos_len = 0;
    memset(publicKey, 0, sizeof(publicKey));
    memset(buf, 0, sizeof(buf));

    fp = fopen("myssl_publickey.txt", "r");
    while( (fgets(buf, sizeof(buf), fp)) != NULL )
    {
        memcpy(publicKey  + pos_len, buf, strlen(buf));
        pos_len = pos_len + strlen(buf);
        memset(buf, 0, sizeof(buf));
    }
    fclose(fp);

    // publicKey read from private.pem file
    pos_len = 0;
    memset(privateKey, 0, sizeof(privateKey));
    memset(buf, 0, sizeof(buf));

    fp = fopen("myssl_privatekey.txt", "r");
    while( (fgets(buf, sizeof(buf), fp)) != NULL )
    {
        memcpy(privateKey  + pos_len, buf, strlen(buf));
        pos_len = pos_len + strlen(buf);
        memset(buf, 0, sizeof(buf));
    }
    fclose(fp);

    printf("Plain Text = %s\n", plainText);
    printf("%s", privateKey);
    printf("%s", publicKey);
    
    /* Encrypted using RSA public Key */
    int encrypted_length= public_encrypt(plainText,strlen(plainText),publicKey,encrypted);
    if(encrypted_length == -1) // RSA_public_encrypt() returns -1 on error
    {
        printLastError("Public Encrypt failed ");
        exit(0);
    }
    printf("Encrypted Text = %s\n",encrypted);
	
	//Encode To Base64
	char* base64EncodeOutput; // base64 저장공간

    int base64_enclen = Base64Encode(encrypted, encrypted_length, &base64EncodeOutput);
	printf("base64 Encoded Text = %s\n", base64EncodeOutput);

	//Decode From Base64
	unsigned char* base64DecodeOutput;
	size_t base64_declen = 0;

	Base64Decode(base64EncodeOutput, &base64DecodeOutput, &base64_declen);
	printf("base64 Decoded Text = %s\n", base64DecodeOutput);

    /* 개인키로 복호화하기 */
    //int decrypted_length = private_decrypt(encrypted,encrypted_length,privateKey, decrypted);
	int decrypted_length = private_decrypt(base64DecodeOutput,base64_declen,privateKey, decrypted);
    if(decrypted_length == -1)  // RSA_private_decrypt() returns -1 on error
    {
        printLastError("Private Decrypt failed ");
        exit(0);
    }
    printf("Decrypted Text = %s\n",decrypted);

 
/*
RSA_public_encrypt() returns the size of the encrypted data (i.e., RSA_size(rsa)). RSA_private_decrypt() returns the size of the recovered plaintext.
On error, -1 is returned
*/
}
