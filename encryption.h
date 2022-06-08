void decrypt_buffer(char *input_output, int str_lengh) {
    int v5; // w10
    __int64 v6; // x8
    __int64 v7; // x9
    int v8; // w23
    int v9; // w12
    char v10; // w10
    int v11; // w11
    char v12; // w10
    unsigned __int64 tmp_lengh; // x21
    __int64 v14; // x21
    __int128 v15; // q1
    int8x16_t v18; // [xsp+0h] [xbp-14B0h] BYREF
    __int128 v19; // [xsp+10h] [xbp-14A0h]
    __int128 v21; // [xsp+1020h] [xbp-490h]


    char output_buffer[4096];
    char encryption_key[30];


    __int128 v23; // [xsp+1050h] [xbp-460h]
    _QWORD key[130]; // [xsp+1060h] [xbp-450h] BYREF

    //If input lengh is bigger or equal to 0
    if (str_lengh >= 0) {
        v5 = str_lengh;
    } else {
        v5 = str_lengh + 1;
    }

    //Copy hardcoded encryption key into the variable
    memcpy(encryption_key, "e38d99fb4434d3d485794c6b34cd5d1f", 30); //ENCRYPTION KEY!!!

    v21 = xmmword_33DB4;

    //If lengh is smaller than 2
    if (str_lengh < 2) {
        v18 = 0;
        v19 = v21;
        memset(output_buffer, 0, 4096);
        aes_set_key(key, encryption_key, 256);
        tmp_lengh = 0;
    } else {
        v6 = 0;
        v7 = 0;
        v8 = v5 >> 1;

        while ((int)v7 < v8) {
            v9 = (unsigned __int8)input_output[v6];
            v10 = v9 - 48;

            if ((unsigned int)(v9 - 48) >= 0xA) {
                if ((unsigned int)(v9 - 65) > 5)
                break;
                v10 = v9 - 55;
            }
            v11 = (unsigned __int8)input_output[v6 + 1];

            if ((unsigned int)(v11 - 48) > 9) {
                if ((unsigned int)(v11 - 65) > 5) {
                    break;
                }
                v12 = v11 + 16 * v10 - 55;
            } else {
                v12 = v11 - 48 + 16 * v10;
            }
            input_output[v7++] = v12;
            v6 += 2LL;
        }

        v18 = 0;
        v19 = v21;
        memset(output_buffer, 0, 4096);
        aes_set_key(key, encryption_key, 256);
        tmp_lengh = 0;

        if (str_lengh >= 2) {
            v14 = 0;
            while (v14 < v8) {
                v18 = *(int8x16_t *)&input_output[v14];
                v23 = *(_OWORD *)&input_output[v14];
                aes_decrypt(key, &v18, &v18);
                v18 = veorq_s8(v18, (int8x16_t)v19);
                v15 = v23;
                *(int8x16_t *)&output_buffer[v14] = v18;
                v14 += 16;
                v19 = v15;
            }

            tmp_lengh = (v8 + 15) & 4294967280;
        }
    }

    if (tmp_lengh >= str_lengh) {
        str_lengh = tmp_lengh;
    }
    
    memset(&input_output[tmp_lengh], 0, str_lengh - tmp_lengh);

    //Copy decrypted string into input_output
    memcpy(input_output, output_buffer, tmp_lengh);
    return 0;
}