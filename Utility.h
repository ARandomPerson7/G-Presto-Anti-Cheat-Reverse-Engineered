int AlertDetect(_JNIEnv *jni_env, jobject *param_2, jobject *param_3, int param_4) {
  callSendResult(jni_env, param_3, param_4);
  return 1;
}

int callSendResult(JNIEnv *jni_env, jobject java_context, int param3) {
    char error_message_buffer[268];

    memset(error_message_buffer, 0, 260);
    sprintf(error_message_buffer,
    "[Error_%d] 3rd party apps that modify game data are not supported. Shutting down in 8 seconds.\n"
    "Please remove all third party \"patcher\" apps before running this application. Protected by Presto", param3);

    main_java_class = JNIEnv::FindClass(jni_env, "com/bishopsoft/Presto/SDK/Presto");
    jstring native_error_string = JNIEnv::NewStringUTF(jni_env, error_message_buffer);
    jmethodID get_scan_result_id = JNIEnv::GetMethodID(jni_env, application_info_id, "Result_Scanning", "(Ljava/lang/String;)V");
    JNIEnv::CallVoidMethod(jni_env, java_context, get_scan_result_id, native_error_string);

    sleep(8);

    jmethodID get_instance_id = JNIEnv::GetStaticMethodID(jni_env, package_manager_class, "getInstance", "()Lcom/bishopsoft/Presto/SDK/Presto;");
    jobject get_instance_object = JNIEnv::CallStaticObjectMethod(jni_env, package_manager_class, get_instance_id);
    jmethodID stop_scan_id = JNIEnv::GetMethodID(jni_env, package_manager_class, "StopScan", "()V");
    JNIEnv::CallVoidMethod(jni_env, get_instance_object, stop_scan_id, 0);

    return 0;
}

void random_str(char *return_val, int lengh) {
    int random;
    ulong lengh_copy;
    char *pcVar1;

    lengh_copy = (ulong)lengh;
    pcVar1 = return_val;
    if (0 < lengh) {
        while (lengh_copy != 0) {
            random = rand();
            lengh_copy = lengh_copy - 1;
            *pcVar1 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
                    [(long)random + (((ulong)(long)random >> 1) / 0x1f) * -0x3e];
            pcVar1 = pcVar1 + 1;
        }
    }
    return_val[lengh] = 0;
    return return_val;
}

int getDataDir(JNIEnv *jni_env, jobject current_activity, char *return_val) {
    jclass package_manager_class = (*(__int64 (__fastcall **)(__int64))(*(_QWORD *)jni_env + 248))(jni_env); //WTF?

    jmethodID application_info_id = (jni_env, package_manager_class, "getApplicationInfo", "()Landroid/content/pm/ApplicationInfo;");
    jobject application_info = _JNIEnv::CallObjectMethod(jni_env, current_activity, application_info_id);
    jfieldID data_dir_id = JNIEnv::FindObjectField(jni_env, application_info, "dataDir", "Ljava/lang/String;");
    jstring data_dir = JNIEnv::GetObjectField(jni_env, application_info, data_dir_id);

    if (data_dir) {
        const char *native_data_dir = JNIEnv::GetStringUTFChars(jni_env, data_dir, 0);
        if (native_data_dir) {
            memcpy(return_val, native_data_dir, (strlen(native_data_dir) + 1));
        }
        JNIEnv::(jni_env, data_dir, native_data_dir); //WUT?
    }
    return 0;
}

int getNativeLibraryDir(JNIEnv *jni_env, jobject current_activity, char *return_val) {
    jclass current_class = JNIEnv::GetObjectClass(jni_env, current_activity);
    jmethodID application_info_id = JNIEnv::GetObjectMethodID(jni_env, current_class, "getApplicationInfo", "()Landroid/content/pm/ApplicationInfo;");
    jobject application_info = _JNIEnv::CallObjectMethod(jni_env, current_activity, application_info_id);

    jclass application_info_class = JNIEnv::(jni_env, application_info);
    jmethodID native_library_dir_id = JNIEnv::(jni_env, application_info_class, "nativeLibraryDir", "Ljava/lang/String;");
    jstring native_library_dir = JNIEnv::GetObjectField(jni_env, application_info, native_library_dir_id);

    if (native_library_dir) {
        const char *native_lib_dir = JNIEnv::GetStringUTFChars(jni_env, native_library_dir, 0);
        if (native_lib_dir) {
            memcpy(return_val, v14, (strlen(native_lib_dir) + 1));
        }
    }
    return 0;
}

void *subNRes(char *a1) { //UNUSED PARAM?
    char encrypted_str_buffer[260];
    char src[260];
    char dest[268];

    memset(src, 0, 260);
    memcpy(encrypted_str_buffer, "C081CD4C7F549EC7B6F15000E2D92C4C", 260);

    decrypt_buffer(encrypted_str_buffer, strlen(encrypted_str_buffer));
    strcpy(dest, &g_dataPath);
    strcpy(&dest[strlen(dest)], "/.");
    strcpy(src, encrypted_str_buffer);
    strcat(dest, src);

    void *handle = dlopen(dest, 1);
    g_Uhandle = handle;

    if (!handle) {
        LOGE("G-Presto load failed : 2001");
        exit(1);
    }
    void *res_sym = dlsym(handle, "Res");

    if (!res_sym) {
        LOGE("G-Presto load failed : 2003");
        exit(1);
    }
    return res_sym;
}

int getBuildProperty(JNIEnv *jni_env, jobject a2, jobject a3, char *return_val) {
    jclass build_class = JNIEnv::FindClass(jni_env, "android/os/Build");
    android_build_prop_id = JNIEnv::GetObjectFieldID(jni_env, build_class, a3, "Ljava/lang/String;");
    android_build_prop = JNIEnv::GetObjectField(jni_env, build_class, android_build_prop_id);

    if (android_build_prop) {
        char *native_build_prop_str = JNIEnv::GetStringUTFChars(jni_env, android_build_prop, 0);
        if (native_build_prop_str) {
            memcpy(return_val, native_build_prop_str, (strlen(native_build_prop_str) + 1));
        }
    }
    return 0;
}

//NOT IMPORTANT
int getDataDir(JNIEnv *env, jobject *param_2, char *return_val) {
  undefined8 uVar1;
  undefined8 uVar2;
  long lVar3;
  char *__s;
  size_t sVar4;
  
  uVar1 = (**(code **)(*(long *)env + 0xf8))();
  uVar1 = (**(code **)(*(long *)env + 0x108))
                    (env,uVar1,"getApplicationInfo","()Landroid/content/pm/ApplicationInfo;");
  uVar1 = _JNIEnv::CallObjectMethod((_jobject *)env,(_jmethodID *)param_2,uVar1);
  uVar2 = (**(code **)(*(long *)env + 0xf8))(env,uVar1);
  uVar2 = (**(code **)(*(long *)env + 0x2f0))(env,uVar2,"dataDir","Ljava/lang/String;");
  lVar3 = (**(code **)(*(long *)env + 0x2f8))(env,uVar1,uVar2);
  if (lVar3 != 0) {
    __s = (char *)(**(code **)(*(long *)env + 0x548))(env,lVar3,0);
    if (__s != (char *)0x0) {
      sVar4 = strlen(__s);
      memcpy(return_val,__s,sVar4 + 1);
    }
    (**(code **)(*(long *)env + 0x550))(env,lVar3,__s);
  }
  return 0;
}

//NOT IMPORTANT
int getNativeLibraryDir(_JNIEnv *param_1,_jobject *param_2, char *return_val) {
  undefined8 uVar1;
  undefined8 uVar2;
  long lVar3;
  char *__s;
  size_t sVar4;
  
  uVar1 = (**(code **)(*(long *)param_1 + 0xf8))();
  uVar1 = (**(code **)(*(long *)param_1 + 0x108))
                    (param_1,uVar1,"getApplicationInfo","()Landroid/content/pm/ApplicationInfo;");
  uVar1 = _JNIEnv::CallObjectMethod((_jobject *)param_1,(_jmethodID *)param_2,uVar1);
  uVar2 = (**(code **)(*(long *)param_1 + 0xf8))(param_1,uVar1);
  uVar2 = (**(code **)(*(long *)param_1 + 0x2f0))
                    (param_1,uVar2,"nativeLibraryDir","Ljava/lang/String;");
  lVar3 = (**(code **)(*(long *)param_1 + 0x2f8))(param_1,uVar1,uVar2);
  if (lVar3 != 0) {
    __s = (char *)(**(code **)(*(long *)param_1 + 0x548))(param_1,lVar3,0);
    if (__s != (char *)0x0) {
      sVar4 = strlen(__s);
      memcpy(return_val,__s,sVar4 + 1);
    }
    (**(code **)(*(long *)param_1 + 0x550))(param_1,lVar3,__s);
  }
  return 0;
}

int android_setCpu(int a1, __int64 a2) {
    unsigned int v2; // w19
    int v3; // w8

    if ((byte_579D4 & 1) != 0) {
        return 0;
    } else {
        v2 = 1;
        byte_579C0 = 1;
        if (a1 <= 1) {
            v3 = 1;
        } else {
            v3 = a1;
        }

        qword_579C8 = a2;
        dword_579D0 = v3;
        pthread_once(&dword_579BC, sub_17F9C);
    }
    return v2;
}

void android_getCpuFeatures() {
    pthread_once(&dword_579BC, &sub_17C3C);
    return qword_579C8;
}

void android_getCpuFamily() {
    pthread_once(&dword_579BC, &sub_17C3C);
    if (byte_579C0) {
        return 4;
    } else {
        return 0;
    }
}

void android_getCpuCount() {
  pthread_once(&dword_579BC, &sub_17C3C);
  return (unsigned int)dword_579D0;
}

