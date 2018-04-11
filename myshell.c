#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int split(char const *input, char const delim, char *Commands[]);
void *SysCall(void *call);
void interactMode();
void batchMode(char *file);

int main(int argc, char *argv[])
{

        if (argc == 2)
        {
                batchMode(argv[1]);
        }
        else
        {
                interactMode();
        }
        return 0;
}

void batchMode(char *file)
{
        char input[50];
        char command[50];
        char *inputptr;
        int i;

        char *commandsSeq[1000];
        char *commandsThreaded[1000]; //handle

        inputptr = input;
        FILE *fptr = fopen(file, "r");
        if (!fptr)
        {
                printf("file couldn't open\n");
                return;
        }
        int cikis = 0;
        while (fgets(inputptr, 1000, fptr))
        {
                int commandsSeqLen = split(inputptr, ';', &commandsSeq);
                if (commandsSeqLen == 0)
                {
                        fgets(inputptr, 1000, fptr);
                        continue;
                }

                for (int i = 0; i < commandsSeqLen; i++)
                {
                        if (commandsSeq[i] == NULL)
                        {
                                continue;
                        }
                        int commandsThreadedLen = split(commandsSeq[i], '|', &commandsThreaded);
                        pthread_t threads[commandsThreadedLen];

                        for (int j = 0; j < commandsThreadedLen; j++)
                        {
                                if (strstr(commandsThreaded[j], "quit") != NULL || strstr(commandsThreaded[j], "exit") != NULL)
                                {
                                        cikis = 1;
                                        continue;
                                }
                                int rc = pthread_create(&threads[j], NULL, SysCall, (void *)commandsThreaded[j]);
                                //printf("commandsThreaded[j]:%s\n", commandsThreaded[j]);
                                if (rc)
                                {
                                        printf("ERROR; return code from pthread_create() is %d\n", rc);
                                        exit(-1);
                                }
                        }
                        for (int i = 0; i < commandsThreadedLen; i++)
                                pthread_join(threads[i], NULL);
                }
                //printf("CİKİS:%d\n", cikis);
                if (cikis == 1)
                {
                        break;
                }
        }
}
void interactMode()
{
        char input[50];
        char command[50];
        char *inputptr;
        int i;

        char *commandsSeq[1000];
        char *commandsThreaded[1000]; //handle

        inputptr = input;

        printf("myshell:>");
        //scanf("%s",inputptr);
        gets(inputptr);

        int cikis = 0;
        //printf("%c\n", *++inputptr);

        while (cikis == 0)
        {

                //sprintf(command, "echo \"%s\"", input);

                //printf("PR_out:%s\n", command);
                //system(command);
                //system(inputptr);

                int commandsSeqLen = split(inputptr, ';', &commandsSeq);
                if (commandsSeqLen == 0)
                {
                        printf("myshell:>");
                        //scanf("%s",inputptr);
                        gets(inputptr);
                        continue;
                }

                for (int i = 0; i < commandsSeqLen; i++)
                {
                        if (commandsSeq[i] == NULL)
                        {
                                continue;
                        }
                        int commandsThreadedLen = split(commandsSeq[i], '|', &commandsThreaded);
                        pthread_t threads[commandsThreadedLen];

                        for (int j = 0; j < commandsThreadedLen; j++)
                        {
                                if (strstr(commandsThreaded[j], "quit") != NULL || strstr(commandsThreaded[j], "exit") != NULL)
                                {
                                        cikis = 1;
                                        continue;
                                }
                                int rc = pthread_create(&threads[j], NULL, SysCall, (void *)commandsThreaded[j]);
                                //printf("commandsThreaded[j]:%s\n", commandsThreaded[j]);
                                if (rc)
                                {
                                        printf("ERROR; return code from pthread_create() is %d\n", rc);
                                        exit(-1);
                                }
                        }
                        for (int i = 0; i < commandsThreadedLen; i++)
                                pthread_join(threads[i], NULL);
                }

                //  free(commandsSeq);
                //  free(commandsThreaded);
                if (cikis == 1)
                {
                        continue;
                }
                printf("myshell:>");
                //scanf("%s",inputptr);
                gets(inputptr);
        }
}
void *SysCall(void *call)
{
        char *str;
        int i;

        str = (char *)call;
        //wait(10* rand());
        system(str);
        //wait(10* rand());

        pthread_exit(NULL);
}

int split(char const *input, char const delim, char *Commands[])
{

        char *tofree = malloc(sizeof(char) * strlen(input));

        if (*input != NULL)
        {
                char *token;

                strcpy(tofree, input);
                token = strtok(tofree, &delim);
                if (token == NULL)
                {
                        printf("%s is not a valid command. Try again\n", input);
                        return 0;
                }
                Commands[0] = malloc(sizeof(char) * strlen(token));
                strcpy(Commands[0], token);

                int i = 1;
                while (token != NULL)
                {
                        token = strtok(NULL, &delim);
                        if (token == NULL)
                        {
                                break;
                        }
                        Commands[i] = malloc(sizeof(char) * strlen(token));
                        strcpy(Commands[i], token);
                        i++;
                }
                return i;
        }
}