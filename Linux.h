void pid_cmdline(int pid, char *return_buffer, int lengh) {
    FILE *file;
    char cmdLineBuffer[268];

    sprintf(cmdLineBuffer, "/proc/%d/cmdline", pid);
    return_buffer = 0;

    file = fopen(cmdLineBuffer, "r");
    if (file != nullptr) {
        fgets(return_buffer, lengh, file);
        fclose(file);
    }
    return;
}