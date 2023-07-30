#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PROCESSES 25
#define MAX_CMD_LENGTH 256

typedef struct {
    int pid;
    int ppid;
    char cmd[MAX_CMD_LENGTH];
    float cpu;
    float mem;
} Process;

Process processes[MAX_PROCESSES];

// Function to retrieve top processes using the 'ps' command
void get_top_processes() {
    // Open a pipe to read the output of the 'ps' command
    FILE *fp = popen("ps -eo pid,ppid,cmd,%cpu,%mem --sort=-%cpu | head -n 26", "r");

    if (fp == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    // Skip the first line (column headers)
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), fp) == NULL) {
        perror("fgets");
        pclose(fp);
        exit(EXIT_FAILURE);
    }

    // Read process data
    int count = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL && count < MAX_PROCESSES) {
        char *pid_str = strtok(buffer, " ");
        char *ppid_str = strtok(NULL, " ");
        char *cmd_str = strtok(NULL, " ");
        char *cpu_str = strtok(NULL, " ");
        char *mem_str = strtok(NULL, " ");

        if (pid_str && ppid_str && cmd_str && cpu_str && mem_str) {
            // Convert string data to appropriate data types and store in the 'processes' array
            processes[count].pid = atoi(pid_str);
            processes[count].ppid = atoi(ppid_str);
            strncpy(processes[count].cmd, cmd_str, MAX_CMD_LENGTH - 1);
            processes[count].cpu = atof(cpu_str);
            processes[count].mem = atof(mem_str);
            count++;
        }
    }

    // Close the pipe
    pclose(fp);
}

// Function to display the retrieved process data in a tabular format
void display_processes() {
    printf("%-10s %-10s %-40s %-10s %-10s\n", "PID", "PPID", "COMMAND", "%CPU", "%MEM");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("%-10d %-10d %-40s %-10.2f %-10.2f\n",
               processes[i].pid, processes[i].ppid, processes[i].cmd, processes[i].cpu, processes[i].mem);
    }
}

int main() {
    while (1) { 
        // Periodically retrieve and display the top processes
        get_top_processes();
        system("clear"); // Clear the terminal screen
        system("figlet ConView"); // Print the banner "ConView"
        printf("\nConView was made by Aitzaz Imtiaz, under the representation\n");
        printf("of predecessor BS Consortium, the last software written during\n");
        printf("during \"The Great Depression\" and extracted by BArchive. This\n");
        printf("project as-is is the first working software of B Consortium\n\n");
        display_processes();
        sleep(1.5); // Pause execution for 1.5 seconds
    }
    system("reset"); // Reset the terminal before exiting (Note: This line is never reached in the current code)
    return 0;
}
