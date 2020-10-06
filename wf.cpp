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

void Fuzhi(struct Word *Danci, FILE *read,int length) //把文件中单词复制到数组中
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
void Word_count(struct Word *Danci,int length) //统计单词的个数
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
        printf("找不到%s该文件\n", argv[0]);
        exit(EXIT_FAILURE);
    }    
    if ((read = fopen(argv[2], "r")) == NULL)
    {
        printf("文件打开失败\n");
        exit(EXIT_FAILURE);
    }
    while (fscanf(read, "%s", &word) != EOF) //测试是否读到文件末尾
    {
        ++length; //统计文本中单词的个数
    } 
	}
	if(argc==2){
    if (argc < 2 || argc > 2)
    {
        printf("找不到%s该文件\n", argv[0]);
        exit(EXIT_FAILURE);
    }    
	char a[10]=".txt";
		argv[1]=strcat(argv[1],a);
    if ((read = fopen(argv[1], "r")) == NULL)
    {
        printf("文件打开失败\n");
        exit(EXIT_FAILURE);
    }
    while (fscanf(read, "%s", &word) != EOF) 
    {
        ++length; 
    } 
	}
    rewind(read);                                 //清除错位信息
    Danci = (struct Word *)malloc (sizeof(struct Word) * length); 
    Fuzhi(Danci, read, length);                    
    
    return 0;
}
