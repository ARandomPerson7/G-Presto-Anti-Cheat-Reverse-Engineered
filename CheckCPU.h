//sub_17C3C
void check_cpu_info() {
    signed int cpu_info; // w27
    __int64 current_line; // x0
    char *v4; // x0
    char *v5; // x19
    signed int v8; // w28
    __int64 v9; // x0
    uint8x8_t v10; // d0
    int v11; // w8

    unsigned int possible_cpu_present_cpu_bufff;
    int present_cpu_buff[64];

    byte_579C0 = 1;
    qword_579C8 = 0LL;
    dword_579D0 = 1;
    byte_579D4 = 1;

    FILE file = open("/proc/cpuinfo", 0);
    if ((file & 0x80000000) == 0) {
        FILE tmp_file = file;
        cpu_info = 0;

        while ((DWORD)current_line) {
            while (1) {
                current_line = read(tmp_file, present_cpu_buff, 256);
                if ((current_line & 0x80000000) == 0)
                    break;
                if (*(_DWORD *)__errno(current_line) != 4)
                    break;
            }
            cpu_info += current_line;
        }


        close(tmp_file);

        if ((cpu_info & 0x80000000) == 0) {
            v4 = (char *)malloc(cpu_info);

            if (v4) {
                v5 = v4;
                FILE file_2 = open("/proc/cpuinfo", 0);
                if ((file_2 & 0x80000000) != 0) {
                    //NOTHING?
                }
                v8 = 0;
                while (v8 < cpu_info) {
                    v9 = read(file_2, &v5[v8], cpu_info - v8);
                    if ((v9 & 0x80000000) != 0) {
                        if ( *(_DWORD *)__errno(v9) != 4 )
                        {
                            if (!v8) {
                                close(file_2);
                            }
                            break;
                        }
                    } else {
                        v8 += v9;
                        if (!(_DWORD)v9) {
                            break;
                        }
                    }
                }

                close(file_2);

                if ((v8 & 0x80000000) != 0) {
                     //NOTHING?
                }

                //PROBABLY SOME FILE READ FUNCTION
                sub_17FAC(present_cpu_buff, "/sys/devices/system/cpu/present");
                sub_17FAC(&possible_cpu_present_cpu_bufff, "/sys/devices/system/cpu/possible");

                v10.n64_u64[0] = vcnt_s8((int8x8_t)(present_cpu_buff[0] & possible_cpu_present_cpu_bufff)).n64_u64[0];
                v10.n64_u16[0] = vaddlv_u8(v10);
                v11 = v10.n64_u32[0];
                if ((present_cpu_buff[0] & possible_cpu_present_cpu_bufff) == 0) {
                    v11 = 1;
                }

                dword_579D0 = v11;
                dlerror();
                void *lib_c_handle = dlopen("libc.so", 2);

                if (!lib_c_handle) {
                    dlclose(lib_c_handle);
                }

                void *get_auxval_sym = dlsym(lib_c_handle, "getauxval");

                if (!get_auxval_sym) {
                    dlclose(lib_c_handle);
                } else {
                    int get_auxval = get_auxval_sym(16);

                    dlclose(lib_c_handle);
                    //SET GLOBAL VARIABLES
                    if (get_auxval != nullptr) {
                        if ((get_auxval & 1) != 0) {
                            DAT_001579c8 = DAT_001579c8 | 1;
                        }

                        if ((get_auxval >> 1 & 1) != 0) {
                            DAT_001579c8 = DAT_001579c8 | 2;
                        }

                        if ((get_auxval >> 3 & 1) != 0) {
                            DAT_001579c8 = DAT_001579c8 | 4;
                        }

                        if ((get_auxval >> 4 & 1) != 0) {
                            DAT_001579c8 = DAT_001579c8 | 8;
                        }

                        if ((get_auxval >> 5 & 1) != 0) {
                            DAT_001579c8 = DAT_001579c8 | 0x10;
                        }

                        if ((get_auxval >> 6 & 1) != 0) {
                            DAT_001579c8 = DAT_001579c8 | 0x20;
                        }

                        if ((get_auxval >> 7 & 1) != 0) {
                            DAT_001579c8 = DAT_001579c8 | 0x40;
                        }
                    }
                }
            }     
        }
    }
}