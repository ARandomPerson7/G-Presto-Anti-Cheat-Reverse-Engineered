bool Engine_state() {
  return g_Ehandle != 0;
}

void WorkThread(JNIEnv *jni_env, jobject a2, jobject a3, int a4) {
    int file_len;
    const char *selected_file;
    char file[268];

    m_stillAlive++;
    m_option = a4;
    g_env = jni_env;

    if (g_dataPath == nullptr) {
        getDataDir(jni_env, a3, &g_dataPath);
    }

    if (p_result) {
        free(p_result);
        p_result = nullptr;
    }

    strcpy(file, &g_dataPath);
    *(_WORD *)&file[strlen(file)] = 47;

    switch (family) {
        case 5:
            strcpy(&file[strlen(file)], "ATG_E_x86_64.sec");
            break;
        case 4:
            file_len = strlen(file);
            selected_file = "ATG_E_x64.sec";
            goto LABEL_10;
        case 2:
            file_len = strlen(file);
            selected_file = "ATG_E_x86.sec";

            // SOME WEIRD SHIT
            int jni_env = *(_QWORD *)(selected_file + 6);
            int activity_thread_class = *(_QWORD *)selected_file;
            char *activity_thread_class = &file[file_len];
            *(_QWORD *)(activity_thread_class + 6) = jni_env;
            *(_QWORD *)activity_thread_class = activity_thread_class;
            break;
        default:
            strcpy(&file[strlen(file)], "ATG_E.sec");
            break;
    }

    void *lib_handle = dlopen(file, 1);
    g_Ehandle = (__int64)lib_handle;
    if (lib_handle) {
        if (g_isScanning == 0) {
            void *work_thread_sym = dlsym(lib_handle, "WorkThread");
            if (work_thread_sym) {
                g_isScanning = 1;
                m_infect_cnt = work_thread_sym(jni_env, a3, m_option);
                if (m_infect_cnt < 0) {
                    int *callSendResult(jni_env, a3, 1010);
                    sprintf(&g_result, "* load_error=%d", m_infect_cnt);
                }
            } else {
                int *call_Send_result = callSendResult(jni_env, a3, 1020);
                int *err = errno(call_Send_result);
                char *load_err_str_2 = strerror(*err);
                sprintf(&g_result, "* WorkThread load_error=%s", load_err_str_2);
            }
        }
    } else {
        int *load_error = errno();
        char *load_error_str = strerror(*load_error);
        sprintf(&g_result, "* engine load_error: %s", load_error_str);
        LOGE("%s", &g_result);
    }
    return (*(__int64 (__fastcall **)(__int64, char *))(*(_QWORD *)jni_env + 1336LL))(jni_env, &g_result);
}

int StopWorkThread(JNIEnv *jni_env, jobject *param_2) {
    code *pcVar1;

    g_isScanning = 0;
    if (g_Ehandle == 0) {
        if (p_result != 0) {
            g_isScanning = 0;
            return 0;
        }
    }
    else {
        pcVar1 = dlsym(g_Ehandle,"StopWorkThread");
        if (pcVar1 != nullptr) {
            (*pcVar1)();
        }
    }
    return 1;
}

int ReLogin(JNIEnv *jni_env, jobject a2, jobject a3, int a4) {
    char file[268];

    g_env = jni_env;
    m_option = a4;
    memset(file, 0, 260);

    if (p_result) {
        free(p_result);
        p_result = 0;
    }

    strcpy(file, &g_dataPath);
    *(_WORD *)&file[strlen(file)] = 47;

    switch (family) {
        case 5:
            strcpy(&file[strlen(file)], "ATG_E_x86_64.sec");
            break;
        case 4:
            file_len = strlen(file);
            file_name = "ATG_E_x64.sec";
            goto LABEL_8;
        case 2:
            file_len = strlen(file);
            file_name = "ATG_E_x86.sec";

            //WEIRD STUFF AGAIN
            __int64 v8 = *(_QWORD *)(file_name + 6);
            __int64 v9 = *(_QWORD *)file_name;
            char *v10 = &file[file_len];
            *(_QWORD *)(v10 + 6) = v8;
            *(_QWORD *)v10 = v9;
            break;
        default:
            strcpy(&file[strlen(file)], "ATG_E.sec");
            break;
    }

    file_handle = dlopen(file, 1);
    g_Ehandle = file_handle;
    if (file_handle) {
        void *ReLogin_sym = dlsym(file_handle, "ReLogin");
        if (ReLogin_sym) {
            m_infect_cnt = ReLogin_sym(jni_env, a3, m_option);
            if (m_infect_cnt < 0) {
                callSendResult(jni_env, a3, 1030);
                sprintf(&g_result, "* load_error=%d", m_infect_cnt);
            }
        } else {
            int call_result = callSendResult(jni_env, a3, 1040);
            int err = errno(call_result);
            char *str_err = strerror(*err);
            sprintf(&g_result, "* WorkThread load_error=%s", str_err);
        }
    } else {
        err_2 = errno(0);
        err_str_2 = strerror(*err_2);
        sprintf(&g_result, "* engine load_error: %s", err_str_2);
        LOGE("%s", &g_result);
    }
    //WEIRD RETURN STUFF
    return; //(*(__int64 (__fastcall **)(__int64, char *))(*(_QWORD *)jni_env + 1336LL))(jni_env, &g_result);
}

void ForkProcess() {
    __int64 result;
    unsigned int v1; 
    pthread_t v2[2];

    v2[1] = *(_QWORD *)(_ReadStatusReg(ARM64_SYSREG(3, 3, 13, 0, 2)) + 40);
    dword_579B8 = fork();

    if (dword_579B8) {
        return pthread_create(v2, 0, monitor_pid, 0);
    }

    v1 = getppid();
    result = ptrace(PTRACE_ATTACH, v1, 0LL, 0LL);

    if (!result) {
        waitpid(v1, (int *)v2, 0);
        ptrace(PTRACE_CONT, v1, 0, 0);
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        while (1) {
            result = waitpid(v1, (int *)v2, 0);
            if (!(_DWORD)result) {
                break;
            }
            if ((~LODWORD(v2[0]) & 0x7F) != 0) {
                _exit(0);
            }
            ptrace(PTRACE_CONT, v1, 0, 0);
        }
    }
    return result;
}

void _NoReturn monitor_pid(void *a1) {
    int stat_loc; // [xsp+Ch] [xbp-4h] BYREF

    waitpid(dword_579B8, &stat_loc, 0);
    exit(0);
}