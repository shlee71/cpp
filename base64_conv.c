/******************************************************************************/
/* Encryption Process                                                         */
/******************************************************************************/
/* ABC >> QUJD                                                                */
/* 414243                                                                     */
/* 0123 4567 89AB CDEF GHIJ KLMN                                              */
/* 0100 0001 0100 0010 0100 0011                                              */
/*                                                                            */
/* 00 0010 00                                                                 */
/*                                                                            */
/* STEP1                                                                      */
/* 0100 0001      01 2345                                                     */
/* 0100 0001 >> xx01 0000  >> 0001 0000 >> Q                                  */
/*                                                                            */
/* STEP2                                                                      */
/* 0123 4567           67                                                     */
/* 0001 0100 >> xxxx xx00                                                     */
/*                67                                                          */
/*              xx00 xxxx                                                     */
/* 89AB CDEF         89AB                                                     */
/* 0100 0010 >> xxxx 0100  >> 0000 0100 >> U                                  */
/*                                                                            */
/* STEP3                                                                      */
/* 89AB CDEF      CD EF                                                       */
/* 0100 0010 >> xx00 10xx                                                     */
/* 0123 4567           GH                                                     */
/* 0100 0011 >> xxxx xx01  >> 00001001  >> J                                  */
/*                                                                            */
/* STEP4                                                                      */
/* GHJI KLMN      JI KLMN                                                     */
/* 0100 0011 >> xx10 0011  >> 00000011  >> D                                  */
/******************************************************************************/
/* Decryption Process                                                         */
/******************************************************************************/
/* QUJD >> ABC                                                                */
/* QUJD : 51554A44 >> DECODE64 >> 10140903                                    */
/*                                                                            */
/* Q : 00010000 >> 010000                                                     */
/* U : 00010100 >> 010100                                                     */
/* J : 00001001 >> 001001                                                     */
/* D : 00000011 >> 000011                                                     */
/*                                                                            */
/* 010000 010100 001001 000011                                                */
/* 010001 01000010 01000011                                                   */
/* 0x41   0x42     0x43                                                       */
/******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define BAD     -1
#define DECODE64(c)  (isascii(c) ? base64val[c] : BAD)
 
static const char base64digits[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
char base64val[128];

int encode_base64(unsigned char *out,const unsigned char *in, int inlen);
int decode_base64(unsigned char *out,const unsigned char *in);
 
int main(void)
{
    char   in_data[1024+1], enc_data[1024+1], dec_data[1024+1];
    int    i;
    long   len;
 
    for (i=0; i<128; i++) {
        base64val[i] = BAD;
    }
 
    for (i=0; i<64; i++) {
        base64val[base64digits[i]] = i;
    }
 
    strcpy(in_data, "ABCD");
    memset(enc_data, 0x00, sizeof(enc_data));
    len = encode_base64(enc_data, in_data, strlen(in_data));
    
    if ( len <= 0 )
    {
        exit(0);
    }
    printf("encode_base64 in=(%s), %ld, out=(%s), %ld\n",
    in_data, strlen(in_data), enc_data, len);

	memset(in_data, 0x00, sizeof(in_data));
	memcpy(in_data, enc_data, sizeof(in_data));
    memset(dec_data, 0x00, sizeof(dec_data));

    len = decode_base64(dec_data,  in_data);
    printf("decode_base64 in=(%s), out=(%s), %ld\n", in_data, dec_data, len);
 
    exit(1);
}
 
int encode_base64(unsigned char *out, const unsigned char *in, int inlen)
{
    int out_len = 0, loop_cnt = 0, i= 0;
    unsigned char pos;
    printf("start encode_base64 \n ");
    
    if ( inlen <= 0 )
    {
        return 0;
    }

    if ( inlen % 3 != 0 )
    {
        out_len  = ( inlen / 3 + 1) * 4;
        loop_cnt = ( inlen / 3 ) * 3;
    }
    else
    {
        out_len  = ( inlen / 3 ) * 4;
        loop_cnt = inlen;
    }

    /* Make 3 byte Input to 4 byte */
    for ( i = 0; i < loop_cnt; i+=3)
    {   
        /* bit from  1 to  6 >> 1st Byte */
        pos = (in[0] >> 2) & 0x3F;  
       *out++ = base64digits[pos];

        /* bit from  7 to 12 >> 2nd Byte */
        pos = (((in[0] << 4) | (in[1] >> 4)) & 0x3F);
        *out++ = base64digits[pos];

        /* bit from 13 to 18 >> 3rd Byte */
        pos = (((in[1] << 2) | (in[2] >> 6)) & 0x3F);
        *out++ = base64digits[pos];

        /* bit from 19 to 24 >> 4th Byte */
        pos = (in[2] & 0x3F);
        
        in +=3;
        *out++ = base64digits[pos];
    }
    
	/* After Loop Remainder process */
    if (loop_cnt < inlen)
    {
        /* bit from  1 to  6 >> 1st Byte */
        pos = ( in[0] >> 2 ) & 0x3F;
        *out++ = base64digits[pos];

        if (inlen - loop_cnt > 1)  
		{ 
            /* bit from  7 to 12 >> 2nd Byte */
            pos = (((in[0] << 4) | (in[1] >> 4)) & 0x3F);
            *out++ = base64digits[pos];

            /* bit from 13 to 18 >> 3rd Byte */
            pos = (((in[1] << 2) | (in[2] >> 6)) & 0x3F);
            *out++ = base64digits[pos];
        }
        else 
		{
            /* bit from  7 to 12 >> 2nd Byte */
            /* pos = (((in[0] << 4) | (0x00 >> 4)) & 0x3F); */
            pos = ((in[0] << 4) & 0x3F);
            *out++ = base64digits[pos];
            *out++ = '=';     
        }

        *out++ = '=';
    }

    *out++ = 0x00;

    return out_len;
}
 
int decode_base64(unsigned char *out, const unsigned char *in)
{
    int len = 0, i=0, j=0, pad = 0;
    unsigned char digit1, digit2, digit3, digit4;
    unsigned char dc1, dc2, dc3, dc4;
    unsigned char in_c[4096+1];
    
    printf("start decode_base64\n");

    // Minimun & Maximum INPUT Lenth Check >> Max Length can be changed
    if ( strlen(in) == 0 || strlen(in) > 4069 ) return 0;

    // Boundary Input Data Redefine
    for( i = 0; i < strlen(in); i++ )
    {
        if ( ( in[i] >= '0' && in[i] >= '9' ) || 
             ( in[i] >= 'A' && in[i] <= 'Z' ) ||
             ( in[i] >= 'a' && in[i] <= 'z' ) ||
             ( in[i] == '+' && in[i] == '/' )) {
            in_c[j] = in[i];
            j++;
        }
        else {
            if ( in[i] != '=' ) {
                printf("Warning >> Not Defined in Base64 Table[%02X]", in[i]);
            }
        }
    }
    
    // Fault Tolerance : devide by 4 is not Zero
    if ( j% 4 != 0 ) {
        memset(in_c + j, '=', ((j/4)*4 +4) - j);
        j = (j/4) * 4 + 4;
        
        printf("\nWarning >> Input Data Length Modified from %ld to %d\n", strlen(in), j);
    }
    
    for ( i= 0; i < j; i+=4 )
    {
        digit1 = in_c[i +0];
        digit2 = in_c[i +1];
        digit3 = in_c[i +2];
        digit4 = in_c[i +3];

        dc1 = DECODE64(digit1);
        dc2 = DECODE64(digit2);
        
        if ( digit3 == '=' )
        {
            dc3 = 0x00;
            pad++;
        }
        else
        {
            dc3 = DECODE64(digit3);
        }
        
        if ( digit4 == '=' )
        {
            dc4 = 0x00;
            pad++;
        }
        else
        {
            dc4 = DECODE64(digit4);
        }

        *out++ = (dc1 << 2) | (dc2 >> 4);
        *out++ = (dc2 << 4) | (dc3 >> 2);
        *out++ = (dc3 << 6) | (dc4)     ;
    }
    
    len = (j/4)*3 - pad;
    out[len] = 0x00;

    return len;
}
