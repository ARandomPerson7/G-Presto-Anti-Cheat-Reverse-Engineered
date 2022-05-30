int g_isScanning;
int p_result;
void *g_Ehandle;
void *g_Uhandle;
char *g_dataPath;
JavaVM *glpVM;
JNIEnv *g_env;
char global_android_bootloader[260];
char global_android_hardware[260];
char global_android_model[260]; 
char native_brand_buff[260];

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    jint v3; // w19
    void *v4; // x0
    int CpuFamily; // w0
    __int64 v7; // x0
    int v13; // w0
    int v14; // w0
    int v15; // w0
    int v16; // w0
    FILE *v17; // x24
    FILE *v18; // x0
    FILE *v19; // x21
    __int64 v20; // x27
    __int64 v21; // x26
    __int64 v22; // x25
    void *v23; // x22
    void *v24; // x0
    void *v25; // x23
    __int64 v26; // x8
    int v27; // w9
    char v28; // w11
    int v29; // w0
    int v30; // w0
    void (__fastcall *v31)(char *); // x0
    JNIEnv *jni_env;
    __int64 ptr; // [xsp+10h] [xbp-BA0h] BYREF
    char v34[260]; // [xsp+18h] [xbp-B98h] BYREF
    char v35[260]; // [xsp+11Ch] [xbp-A94h] BYREF
    char src[260]; // [xsp+220h] [xbp-990h] BYREF
    char v37[260]; // [xsp+324h] [xbp-88Ch] BYREF
    char name[260]; // [xsp+428h] [xbp-788h] BYREF
    char dest[260]; // [xsp+52Ch] [xbp-684h] BYREF
    char v40[41]; // [xsp+630h] [xbp-580h] BYREF
    __int64 v41; // [xsp+659h] [xbp-557h]
    __int64 v42; // [xsp+661h] [xbp-54Fh]
    __int64 v43; // [xsp+669h] [xbp-547h]
    __int64 v44; // [xsp+671h] [xbp-53Fh]
    __int64 v45; // [xsp+679h] [xbp-537h]
    __int64 v46; // [xsp+681h] [xbp-52Fh]
    __int64 v47; // [xsp+689h] [xbp-527h]
    __int64 v48; // [xsp+691h] [xbp-51Fh]
    __int64 v49; // [xsp+699h] [xbp-517h]
    __int64 v50; // [xsp+6A1h] [xbp-50Fh]
    __int64 v51; // [xsp+6A9h] [xbp-507h]
    __int64 v52; // [xsp+6B1h] [xbp-4FFh]
    __int64 v53; // [xsp+6B9h] [xbp-4F7h]
    __int64 v54; // [xsp+6C1h] [xbp-4EFh]
    __int64 v55; // [xsp+6C9h] [xbp-4E7h]
    __int64 v56; // [xsp+6D1h] [xbp-4DFh]
    __int64 v57; // [xsp+6D9h] [xbp-4D7h]
    __int64 v58; // [xsp+6E1h] [xbp-4CFh]
    __int64 v59; // [xsp+6E9h] [xbp-4C7h]
    __int64 v60; // [xsp+6F1h] [xbp-4BFh]
    __int64 v61; // [xsp+6F9h] [xbp-4B7h]
    __int64 v62; // [xsp+701h] [xbp-4AFh]
    __int64 v63; // [xsp+709h] [xbp-4A7h]
    __int64 v64; // [xsp+711h] [xbp-49Fh]
    __int64 v65; // [xsp+719h] [xbp-497h]
    __int64 v66; // [xsp+721h] [xbp-48Fh]
    __int64 v67; // [xsp+729h] [xbp-487h]
    __int16 v68; // [xsp+731h] [xbp-47Fh]
    char v69; // [xsp+733h] [xbp-47Dh]
    char v70[260]; // [xsp+738h] [xbp-478h] BYREF
    char v71[260]; // [xsp+83Ch] [xbp-374h] BYREF
    char v72[260]; // [xsp+940h] [xbp-270h] BYREF
    char filename[284]; // [xsp+A44h] [xbp-16Ch] BYREF

    v3 = 65542;
    jni_env = 0;
    memset(dest, 0, sizeof(dest));
    memset(name, 0, sizeof(name));
    memset(v37, 0, sizeof(v37));
    memcpy(src, "225B833CFD5F43A729E49BBF8C002480", sizeof(src));
    memcpy(v35, "3ED33E9DF4FDC88E8D79CBD807560972", sizeof(v35));
    v4 = memcpy(v34, "0FF1038D784959AD9070A6E91D73022B", sizeof(v34));
    CpuFamily = android_getCpuFamily(v4);
    v67 = 0LL;
    family = CpuFamily;
    *(_QWORD *)&v40[33] = 0;

    v7 = JNIEnv::NewStringUTF(jni_env, "com/bishopsoft/Presto/SDK/Presto");

    if (!v7) {
        LOGI("Native registration unable to find class(AVMJni)");
        return -1;
    }
    if (JNIEnv::(jni_env, v7, off_50010, 8LL) & 0x80000000) != 0) {
        LOGE("RegisterNatives failed !!!\n");
        return -1;
    }

    jclass activity_thread_class = JNIEnv::FindClass(jni_env, "android/app/ActivityThread");
    jmethodID current_application_id = JNIEnv::GetStaticMethodID(jni_env, activity_thread_class, "currentApplication", "()Landroid/app/Application;");
    jobject current_application = JNIEnv::CallStaticObjectMethod(jni_env, activity_thread_class, current_application_id);

    getDataDir(jni_env, current_application, &g_dataPath);
    getNativeLibraryDir(jni_env, current_application, g_nativePath);

    //SOME AES DECRYPTION
    decrypt_buffer(src, strlen(src));
    decrypt_buffer(v35, strlen(v35));
    decrypt_buffer(v34, strlen(v34));

    strcpy(dest, &g_dataPath);
    strcat(dest, src);
    strcpy(name, &g_dataPath);
    strcat(name, v35);
    strcpy(v37, &g_dataPath);
    strcat(v37, v34);

    if (!access(dest, 0) && !access(name, 0) && !access(v37, 0)) {
        ptr = 0;
        memset(filename, 0, 260);
        memset(v72, 0, 260);
        memset(v71, 0, 260);
        memcpy(v70, "C081CD4C7F549EC7B6F15000E2D92C4C", 260); //ENCRYPTED STRING?
        strcpy(filename, g_nativePath);
        *(_WORD *)&filename[strlen(filename)] = 47;
        strcpy(&filename[strlen(filename)], "libATG_L.so");
        v16 = strlen(v70);
        decrypt_buffer(v70, v16);
        strcpy(v72, &g_dataPath);
        strcpy(&v72[strlen(v72)], "/.");
        strcpy(v71, v70);
        strcat(v72, v71);
        v17 = fopen(filename, "rb");
        v18 = fopen(v72, "wb");

        //SOME WEIRD SHIT
        //NOT SURE WHAT IT'S SUPPOSED TO DO
        if (v17) {
            v19 = v18;
            fseek(v17, -4LL, 2);
            v20 = ftell(v17);
            fread(&ptr, 1u, 8u, v17);
            v21 = ptr;
            v22 = v20 - ptr;
            v23 = calloc((int)v20 - (int)ptr, 1u);
            v24 = calloc(v20, 1u);

            if (v23) {
                v25 = v24;
                if (v24)
                {
                    fseek(v17, 0LL, 0);
                    fread(v25, 1u, v20, v17);
                    fseek(v17, v21, 0);
                    fread(v23, 1u, v22, v17);
                    fclose(v17);
                    if (v22 >= 1) {
                        v26 = 0;
                        v27 = 0;
                        while ( v22 != v26 ) {
                            if (v21 <= v26) {
                                v27 = 0;
                                v28 = *((_BYTE *)v25 + v27++);
                                *((_BYTE *)v23 + v26++) ^= v28;
                            }
                        }
                    }
                    fwrite(v23, 1u, v22, v19);
                    fclose(v19);
                    free(v23);
                    free(v25);
                }
            }
        }

        memset(v72, 0, sizeof(v72));
        memcpy(v71, "6D644316380AF571DA568B7A0F3414D5", sizeof(v71));
        memcpy(v70, "C081CD4C7F549EC7B6F15000E2D92C4C", sizeof(v70));

        v29 = strlen(v70);
        decrypt_buffer(v70, v29);
        strcpy(filename, &g_dataPath);
        strcpy(&filename[strlen(filename)], "/.");
        strcpy(v72, v70);
        strcat(filename, v72);
        g_Uhandle = dlopen(filename, 1);

        if (g_Uhandle) {
            v30 = strlen(v71);
            decrypt_buffer(v71, v30);
            v31 = dlsym(g_Uhandle, v71);
            if (v31) {
                v31(filename);
            }
            LOGE("G-Presto load failed : 1003");
        }
        else
        {
            LOGE("G-Presto load failed : 1001");
        }
        exit(1);
    }
    glpVM = vm;
    return v3;
}
