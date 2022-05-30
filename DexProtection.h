//I HAVE ABSOLUTELY NO IDEA WTF THIS THING DOES
//CLEAN THE MISSING THINGS YOURSELF
int InitDex(JNIEnv *jni_env, jobject a2, jobject current_activity, jstring a4, jstring a5, jobject a6) {
    const char *v11; // x23
    unsigned __int64 v12; // x0
    unsigned __int64 v13; // x25
    char *v14; // x26
    unsigned __int64 v15; // x27
    const char *v16; // x0
    const char *v17; // x0
    __int64 v18; // x25
    void *v19; // x26
    char *v20; // x27
    unsigned __int64 v21; // x28
    const char *v22; // x3
    const char *v23; // x3
    __int64 v28; // x0
    const char *v29; // x0
    FILE *v30; // x21
    FILE *v31; // x0
    __int64 v32; // x21
    _BYTE *v33; // x1
    __int64 v34; // x22
    const char *v41; // x1
    __int128 v43; // [xsp+20h] [xbp-620h] BYREF
    void *p; // [xsp+30h] [xbp-610h]
    __int128 v45; // [xsp+40h] [xbp-600h] BYREF
    void *v46; // [xsp+50h] [xbp-5F0h]
    char v47; // [xsp+60h] [xbp-5E0h]
    _BYTE v48[15]; // [xsp+61h] [xbp-5DFh] BYREF
    void *v49; // [xsp+70h] [xbp-5D0h]
    char v50; // [xsp+78h] [xbp-5C8h]
    _BYTE v51[15]; // [xsp+79h] [xbp-5C7h] BYREF
    void *v52; // [xsp+88h] [xbp-5B8h]
    size_t v53[4]; // [xsp+90h] [xbp-5B0h] BYREF
    void *v54; // [xsp+A0h] [xbp-5A0h]
    __int128 v55; // [xsp+A8h] [xbp-598h]
    void *v56; // [xsp+B8h] [xbp-588h]


    char name[260]; // [xsp+C0h] [xbp-580h] BYREF
    char src[260]; // [xsp+1C4h] [xbp-47Ch] BYREF
    char dest[264]; // [xsp+2C8h] [xbp-378h] BYREF
    char v60[260]; // [xsp+3D0h] [xbp-270h] BYREF
    char filename[284]; // [xsp+4D4h] [xbp-16Ch] BYREF

    v11 = JNIEnv::GetStringUTFChars(jni_env, a4, 0);

    memset(filename, 0, 260);
    memset(v60, 0, 260);
    memset(dest, 0, 260);
    memset(src, 0, 260);
    memset(name, 0, 260);
    strcpy(filename, v11);

    *((_QWORD *)&v55 + 1) = 30720LL;
    LOBYTE(v55) = 18;
    v56 = 0LL;
    memset(v53, 0, sizeof(v53));
    strcpy(&filename[strlen(filename)], "/.class.dex");
    *(_QWORD *)((char *)&v55 + 1) = *(_QWORD *)"class.dex";
    v54 = 0LL;
    v12 = strlen(v11);
    v13 = v12;

    if (v12 >= 0x17) {
        v15 = (v12 + 16) & 0xFFFFFFFFFFFFFFF0LL;
        v14 = (char *)operator new(v15);
        *(_QWORD *)&v53[2] = v13;
        v54 = v14;
        *(_QWORD *)v53 = v15 | 1;
        goto LABEL_5;
    }

    v14 = (char *)v53 + 1;
    LOBYTE(v53[0]) = 2 * v12;
    if (v12) {
        LABEL_5:
        memcpy(v14, v11, v13);
    }
    v14[v13] = 0;
    std::operator+<char>((int)v53, "/.dex");
    if ((v53[0] & 1) != 0) {
        v16 = (const char *)v54;
    } else {
        v16 = (char *)v53 + 1;
    }
    mkdir(v16, 448);
    if ((v50 & 1) != 0) {
        v17 = (const char *)v52;
    } else {
        v17 = v51;
    }
    mkdir(v17, 448);

    p = 0;
    v46 = v56;
    v45 = v55;
    v43 = 0uLL;

    if ((v53[0] & 1) == 0) {
        p = v54;
        v43 = *(_OWORD *)v53;
        goto LABEL_21;
    }

    v18 = *(_QWORD *)&v53[2];
    if (*(_QWORD *)&v53[2] >= 0xFFFFFFFFFFFFFFF0LL)
        std::__basic_string_common<true>::__throw_length_error(&v43);
    v19 = v54;

    if (*(_QWORD *)&v53[2] >= 0x17uLL) {
        v21 = (*(_QWORD *)&v53[2] + 16LL) & 0xFFFFFFFFFFFFFFF0LL;
        v20 = (char *)operator new(v21);
        *((_QWORD *)&v43 + 1) = v18;
        p = v20;
        *(_QWORD *)&v43 = v21 | 1;
    } else {
        v20 = (char *)&v43 + 1;
        LOBYTE(v43) = 2 * LOBYTE(v53[2]);
        if ( !*(_QWORD *)&v53[2] )
        goto LABEL_20;
    }

    memcpy(v20, v19, v18);
    LABEL_20:
    v20[v18] = 0;
    LABEL_21:
    copyDexToData(jni_env, a6, &v45, &v43);
    if ((v43 & 1) != 0) {
        operator delete(p);
    }

    if ((v45 & 1) != 0) {
        operator delete(v46);
    }

    if ((v47 & 1) != 0) {
        v22 = (const char *)v49;
    } else {
        v22 = v48;
    }

    LOGI("strDexPath = %s", v22);
    if ((v50 & 1) != 0) {
        v23 = (const char *)v52;
    } else {
        v23 = v51;
    }

    LOGI("strDestDexPath = %s", v23);
    LOGI("strDexout = %s", filename);

    (*(void (__fastcall **)(__int64, __int64, const char *))(*(_QWORD *)jni_env + 1360LL))(jni_env, a4, v11);
    jclass current_activity_class = JNIEnv::GetObjectClass(jni_env, current_activity);
    jmethodID get_package_name_id = JNIEnv::GetObjectMethodID(jni_env, current_activity_class, "getPackageName", &unk_33BE2);
    jstring package_name = _JNIEnv::CallObjectMethod(jni_env, current_activity, get_package_name_id);
    if (package_name) {
        native_package_name = JNIEnv::GetStringUTFChars(jni_env, package_name, 0);
        strcpy(src, native_package_name);
    }

    strcpy(dest, "GPresto_");
    strcat(dest, src);
    v28 = strlen(dest);
    md5_buffer_core(v60, dest, v28);

    if ((v47 & 1) != 0) {
        v29 = (const char *)v49;
    } else {
        v29 = v48;
    }

    v30 = fopen(v29, "rb");
    v31 = fopen(filename, "wb");
    decrypt_stream(v30, v31, v60);
    v32 = JNIEnv::(jni_env, filename);
    if ((v50 & 1) != 0) {
        v33 = v52;
    } else {
        v33 = v51;
    }

    v34 = (*(__int64 (__fastcall **)(__int64, _BYTE *))(*(_QWORD *)jni_env + 1336LL))(jni_env, v33);
    jclass class_loader_class = JNIEnv::FindClass(jni_env, "java/lang/ClassLoader");
    jmethodID system_class_loader_id = JNIEnv::GetStaticMethodID(jni_env, class_loader_class, "getSystemClassLoader", "()Ljava/lang/ClassLoader;");
    jobject system_class_loader = _JNIEnv::CallStaticObjectMethod(jni_env, class_loader_class, system_class_loader_id);

    jclass dex_class_loader_class = JNIEnv::FindClass(jni_env, "dalvik/system/DexClassLoader");
    jmethodID dex_class_loader = JNIEnv::GetObjectMethodID(jni_env, dex_class_loader_class, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/ClassLoader;)V");
    jobject new_class_loader = _JNIEnv::NewObject(jni_env, dex_class_loader_class, dex_class_loader, v32, v34, a5, system_class_loader);

    if ((v50 & 1) != 0) {
        v41 = (const char *)v52;
    } else {
        v41 = v51;
    }

    strcpy(name, v41);
    strcpy(&name[strlen(name)], "/.class.dex");
    unlink(filename);
    unlink(name);

    if ((v47 & 1) == 0) {
        if ( (v50 & 1) == 0 )
        goto LABEL_46;
    LABEL_50:
        operator delete(v52);
        if ( (v53[0] & 1) == 0 )
        return new_class_loader;
        goto LABEL_47;
    }
    operator delete(v49);
    if ( (v50 & 1) != 0 )
        goto LABEL_50;
    LABEL_46:
    if ( (v53[0] & 1) != 0 )
    LABEL_47:
        operator delete(v54);
    return new_class_loader;
}

void copyDexToData(JNIEnv *jni_env, void *a2@<X1>, unsigned __int8 *a3@<X2>, int a4@<W3>, _QWORD *a5@<X8>) {
    AAssetManager *v8; // x0
    const char *v9; // x1
    AAsset *v10; // x0
    AAsset *v11; // x20
    unsigned __int64 v12; // x8
    void *v13; // x1
    unsigned __int64 v14; // x2
    __int64 v15; // x0
    __int128 v16; // q0
    off_t Length; // w21
    const char *v18; // x23
    int v19; // w22
    void *v20; // x23
    int v21; // w24
    void *v22; // x8
    __int128 v23; // q0
    const char *v24; // x3
    char v25; // w8
    char v26; // [xsp+8h] [xbp-78h] BYREF
    void *p; // [xsp+18h] [xbp-68h]
    __int128 v28; // [xsp+20h] [xbp-60h] BYREF
    void *v29; // [xsp+30h] [xbp-50h]
    __int64 v30; // [xsp+38h] [xbp-48h]

    v30 = *(_QWORD *)(_ReadStatusReg(ARM64_SYSREG(3, 3, 13, 0, 2)) + 40);
    v8 = AAssetManager_fromJava(jni_env, a2);
    if ( (*a3 & 1) != 0 )
        v9 = (const char *)*((_QWORD *)a3 + 2);
    else
        v9 = (const char *)(a3 + 1);
    v10 = AAssetManager_open(v8, v9, 0);
    if ( v10 )
    {
        v11 = v10;
        std::operator+<char>(a4, "/");
        v12 = *a3;
        if ( (v12 & 1) != 0 )
        v13 = (void *)*((_QWORD *)a3 + 2);
        else
        v13 = a3 + 1;
        if ( (v12 & 1) != 0 )
        v14 = *((_QWORD *)a3 + 1);
        else
        v14 = v12 >> 1;
        v15 = std::string::append((int)&v26, v13, v14);
        v16 = *(_OWORD *)v15;
        v29 = *(void **)(v15 + 16);
        v28 = v16;
        *(_QWORD *)(v15 + 8) = 0LL;
        *(_QWORD *)(v15 + 16) = 0LL;
        *(_QWORD *)v15 = 0LL;
        if ( (v26 & 1) != 0 )
        operator delete(p);
        Length = AAsset_getLength(v11);
        if ( (v28 & 1) != 0 )
        v18 = (const char *)v29;
        else
        v18 = (char *)&v28 + 1;
        v19 = open(v18, 65, 493LL);
        if ( (v19 & 0x80000000) != 0 )
        {
        AAsset_close(v11);
        __android_log_print(6, "<Presto_L>", "Open %s File Error!", v18);
        v25 = v28;
        a5[1] = 0LL;
        a5[2] = 0LL;
        *a5 = 0LL;
        if ( (v25 & 1) != 0 )
            operator delete(v29);
        }
        else
        {
        v20 = (void *)operator new[](0x400uLL);
        if ( Length >= 1 )
        {
            do
            {
            memset(v20, 0, 0x400u);
            v21 = AAsset_read(v11, v20, 0x400u);
            if ( (v21 & 0x80000000) != 0 )
                break;
            write(v19, v20, v21);
            Length -= v21;
            }
            while ( Length > 0 );
        }
        operator delete[](v20);
        AAsset_close(v11);
        close(v19);
        v22 = v29;
        v23 = v28;
        v29 = 0LL;
        v28 = 0uLL;
        a5[2] = v22;
        *(_OWORD *)a5 = v23;
        }
    }
    else
    {
        if ( (*a3 & 1) != 0 )
        v24 = (const char *)*((_QWORD *)a3 + 2);
        else
        v24 = (const char *)(a3 + 1);
        __android_log_print(6, "<Presto_L>", "%s not found in assets!", v24);
        a5[1] = 0LL;
        a5[2] = 0LL;
        *a5 = 0LL;
    }
}