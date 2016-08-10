#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>    //Color
#define CMD_SIZE 100
#define FILE_NAME_SIZE 100
int main(int argc, char * argv [] )
{
    //Color
    HANDLE  m_hConsole;
    CONSOLE_SCREEN_BUFFER_INFO   csbi;
    WORD m_currentConsoleAttr;
    m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if(GetConsoleScreenBufferInfo(m_hConsole, &csbi))
    m_currentConsoleAttr = csbi.wAttributes;

    //Color
    FILE* fp;
    FILE* rcmd;
    char ch;
    char file[FILE_NAME_SIZE];
    //char file[50];
    char write[CMD_SIZE];
    int counter = 0,progress = 0;
    int flag = 0;
    //printf("\nEnter .R file name [include .r extension]    :   ");
    //gets(file);
    fp = fopen(argv[1],"r");
    printf("Converting : %s",argv[1]);
    if(fp == NULL)
        fprintf(stderr, "\n%s\n", strerror(errno));
        //printf("\nError Opening File! Try Again\n");
    printf("\nEnter destination file [FULL QUALIFIED NAME WITH EXTENSION] or Press [N] to use DEFAULT\n");
    gets(file);
    if(strcmp(file,"N") == 0 || strcmp(file,"n") == 0)
    {
        strcpy(file,"Rcommands.R");
        printf("\nFileName : %s",file);

    }
    rcmd = fopen(file,"w");
    printf("\n\n");
    while( (ch = fgetc(fp) ) != EOF)
    {
        /*
        SetConsoleTextAttribute(m_hConsole, COLOR);     //define macro COLOR firstly    #define COLOR 161
        printf("%3d  %s\n", COLOR, "I want to be nice today!");
        */
        SetConsoleTextAttribute(  GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_GREEN );    //Color
        if(progress == 50)
        {
         printf( "%s", ">" ); //Color
         progress = 0;
        }
        progress++;
        //printf("\nRead : %c",ch);
        if(ch == '>')
        {
            flag = 0;
            //getline(&line,&nbytes,fp);
            while(ch != '\n' && ch != EOF)
            {
                //Ignore >
                ch = fgetc(fp);
                if(ch == '\n' || ch == EOF)
                    flag = 1;
                //printf("\nRead : %c\n",ch);
                //printf("\nFlag : %d\n",flag);
                if(flag == 0)
                {
                    write[counter++] = ch;
                    //printf("\nWritten : %c\n",write[counter-1]);
                }
                else
                    write[counter++] = '\0';
            }
            fprintf(rcmd,"%s",write);
            fprintf(rcmd,"%s","\n");
            counter = 0;
            memset(write,0,strlen(write));
        }
    }
    //Back to previous Color

    SetConsoleTextAttribute (
            m_hConsole,
            m_currentConsoleAttr);

    //reset text color, only on Windows
    //SetConsoleTextAttribute(  GetStdHandle( STD_OUTPUT_HANDLE ), 0x08 );
    //Color
    printf("\n\n");
    printf("\nResults Saved as : %s \n",file);
    fclose(fp);
    fclose(rcmd);
    return 0;
}
