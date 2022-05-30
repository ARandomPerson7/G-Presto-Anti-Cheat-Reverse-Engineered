int isEmulator(JNIEnv *jni_env) {
    //SET GLOBAL VARIABLES TO NULL
    memset(native_brand_buff, 0, 260);
    memset(global_android_model, 0, 260);
    memset(global_android_hardware, 0, 260);
    memset(global_android_bootloader, 0, 260);

    jclass v2 = JNIEnv::FindClass(jni_env, "android/os/Build");
    jfieldID v3 = JNIEnv::GetbjectFieldID(jni_env, v2, "BRAND", "Ljava/lang/String;");
    jstring android_brand = JNIEnv::GetObjectField(jni_env, v2, v3);
    if (android_brand) {
        char *native_brand_str = JNIEnv::GetStringUTFChars(jni_env, android_brand, 0);
        if (native_brand_str) {
            memcpy(native_brand_buff, native_brand_str, (strlen(native_brand_str) + 1));
        }
    }

    jclass build_class = JNIEnv::FindClass(jni_env, "android/os/Build");
    jfieldID android_model_id = JNIEnv::GetbjectFieldID(jni_env, build_class, "MODEL", "Ljava/lang/String;");
    jstring android_model = JNIEnv::GetObjectField(jni_env, build_class, android_model_id);
    if (android_model) {
        char *native_model_str = JNIEnv::GetStringUTFChars(jni_env, android_model, 0);
        if (native_model_str) {
            memcpy(global_android_model, native_model_str, (strlen(native_model_str) + 1));
        }
    }

    jclass build_class = JNIEnv::FindClass(jni_env, "android/os/Build");
    jfieldID android_hardware_id = JNIEnv::GetbjectFieldID(jni_env, build_class, "HARDWARE", "Ljava/lang/String;");
    jstring android_hardware = JNIEnv::GetObjectField(jni_env, build_class, android_hardware_id);
    if (android_hardware) {
        char *native_hardware_str = JNIEnv::GetStringUTFChars(jni_env, android_hardware, 0);
        if (native_hardware_str) {
            memcpy(global_android_hardware, native_hardware_str, (strlen(native_hardware_str) + 1)); //global_android_hardware IS GLOBAL VARIABLE
        }
    }

    jclass build_class = JNIEnv::FindClass(jni_env, "android/os/Build");
    jfieldID android_bootloader_id = JNIEnv::GetbjectFieldID(jni_env, build_class, "BOOTLOADER", "Ljava/lang/String;");
    jstring android_bootloader = JNIEnv::GetObjectField(jni_env, build_class, android_bootloader_id);
    if (android_bootloader) {
        native_bootloader_str = JNIEnv::GetStringUTFChars(jni_env, android_bootloader, 0);
        if (native_bootloader_str) {
            memcpy(global_android_bootloader, native_bootloader_str, (strlen(native_bootloader_str) + 1)); //global_android_bootloader IS GLOABAL VARIABLE
        }
    }
    
    //YANDERE DEV??? LMAO
    if(strcmp(native_brand_buff, "generic")
    && strcmp(native_brand_buff, "sdk")
    && strcmp(native_brand_buff, "Microvirt")
    && strcmp(native_brand_buff, "AMIDuOS")
    && strcmp(native_brand_buff, "TTVM")
    && strcmp(global_android_model, "AMIDuOS")
    && strcmp(global_android_model, "Memu")
    && strcmp(global_android_model, "TiantianVM")
    && strcmp(global_android_model, "Droid4X")
    && strcmp(global_android_hardware, "andy")
    && strcmp(global_android_hardware, "vbox86")
    && strcmp(global_android_hardware, "nox")
    && strcmp(global_android_hardware, "windroye")
    && strcmp(global_android_hardware, "goldfish")
    && strcmp(global_android_hardware, "ttVM_x86")
    && strcmp(global_android_bootloader, "nox")) 
    {
        v30 = open("/system/bin/bstfolderd", 0);
        if ((v30 < 0) {
            v30 = open("/system/bin/bstfolder_ctl", 0);
            if ((v30 < 0) {
                v30 = open("/system/bin/bstsyncfs", 0);
                if ((v30 < 0) {
                    v30 = open("/system/bin/bstshutdown", 0);
                    if ((v30 < 0) {
                        v30 = open("/system/bin/nox", 0);
                        if ((v30 < 0) {
                            v30 = open("/system/bin/noxscreen", 0);
                            if ((v30 < 0) {
                                v30 = open("/system/bin/nemuVM-prop", 0);
                                if ((v30 < 0) {
                                    v30 = open("/system/bin/droid4x", 0);
                                    if ((v30 < 0) {
                                        v30 = open("/system/bin/droid4x-prop", 0);
                                        if ((v30 < 0) {
                                            v30 = open("/fstab.vbox86", 0);
                                            if ((v30 < 0) {
                                                v30 = open("/fstab.android_x86", 0);
                                                if ((v30 < 0) {
                                                    v30 = open("/system/app/EmuCoreService/EmuCoreService.apk", 0);
                                                    if ((v30 < 0) {
                                                        v30 = open("/system/app/EmuInputService/EmuInputService.apk", 0);
                                                        if ((v30 < 0) {
                                                            v30 = open("/system/app/gpLogin/gpLogin.apk", 0);
                                                            if ((v30 < 0) {
                                                                v30 = open("/system/app/Helper/NoxHelp_en.apk", 0);
                                                                if ((v30 < 0) {
                                                                    return opendir("/sdcard/windows/BstSharedFolder") != 0;
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        close(v30);
    }
    return 1;
}