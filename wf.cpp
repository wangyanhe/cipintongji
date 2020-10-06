#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Word 
{
    size_t time;
    char word[100000];
};


void Fuzhi(struct Word *Danci, FILE *read,int length);
void Word_count(struct Word *Danci,int length);

void Fuzhi(struct Word *Danci, FILE *read,int length) //���ļ��е��ʸ��Ƶ�������
{

    char word[100000];
    int i = 0, j=0;

    while (fscanf(read, "%s", &word) != EOF)
    {
        strcpy(Danci[i].word, word); 
        ++i;                         
    }
    fclose(read);                  
    Word_count(Danci, length); 
}
void Word_count(struct Word *Danci,int length) //ͳ�Ƶ��ʵĸ���
{
    int i, j,cishu=0;
    for (i = 0; i < length; i++)
    {
        Danci[i].time = 1;
        for (j = i + 1; j < length; j++)
        {
            if (strcmp(Danci[i].word, Danci[j].word) == 0)
            {
                ++Danci[i].time;            
                strcpy(Danci[j].word, " "); 
            }
        }
    }
    for (int index = 0; index < length; index++) 
    {
        for (int temp = 0; temp < length - index-1; temp++)
        {
            if (Danci[temp].time < Danci[temp + 1].time)
            {
                struct Word word = Danci[temp];
                Danci[temp] = Danci[temp + 1];
                Danci[temp + 1] = word;
            }
        }
    }

    for (i = 0; i < length; i++)
        if (strcmp(Danci[i].word, " ") != 0)
        {  
			cishu++;
        }
	printf("total %d words\n\n", cishu);
    for (i = 0; i < length; i++)
        if (strcmp(Danci[i].word, " ") != 0)
        { 
            printf("%-5s:%-3d\n", Danci[i].word, Danci[i].time);
        }
}

int main(int argc, char *argv[])
{
	extern int cishu;
    char word[100000];
    int length = 0;
    FILE *read;
    struct Word *Danci;
	if(argc==3){
    if (argc < 3 || argc > 3)
    {
        printf("�Ҳ���%s���ļ�\n", argv[0]);
        exit(EXIT_FAILURE);
    }    
    if ((read = fopen(argv[2], "r")) == NULL)
    {
        printf("�ļ���ʧ��\n");
        exit(EXIT_FAILURE);
    }
    while (fscanf(read, "%s", &word) != EOF) //�����Ƿ�����ļ�ĩβ
    {
        ++length; //ͳ���ı��е��ʵĸ���
    } 
	}
	if(argc==2){
    if (argc < 2 || argc > 2)
    {
        printf("�Ҳ���%s���ļ�\n", argv[0]);
        exit(EXIT_FAILURE);
    }    
	char a[10]=".txt";
		argv[1]=strcat(argv[1],a);
    if ((read = fopen(argv[1], "r")) == NULL)
    {
        printf("�ļ���ʧ��\n");
        exit(EXIT_FAILURE);
    }
    while (fscanf(read, "%s", &word) != EOF) 
    {
        ++length; 
    } 
	}
    rewind(read);                                 //�����λ��Ϣ
    Danci = (struct Word *)malloc (sizeof(struct Word) * length); 
    Fuzhi(Danci, read, length);                    
    
    return 0;
}
