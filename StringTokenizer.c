#include <stdio.h>
#include <string.h>

#define ROW_SIZE 999
#define COL_SIZE 20



//Global variables
int numbers[10],alphabets[51],symbols[194],freq[ROW_SIZE];
int i=0,j=0,k=0;
char words[ROW_SIZE][COL_SIZE];



//Testing Alphabets
int alpha(char stra)
{
    for(i=0;i<=51;i++)
    {
        if (words[j][k] == alphabets[i])
        {
            k++;
            words[j][k] = stra;
            return words[j][k];
        }
    }
    j++;
    k=0;
    words[j][k] = stra;

    return words[j][k];
}

//Testing Numbers
int num(char strn)
{
    for(i=0;i<=10;i++)
    {
        if(words[j][k]==numbers[i])
        {
            k++;
            words[j][k]=strn;
            return words[j][k];
        }
    }
    j++;
    k=0;
    words[j][k] = strn;

    return words[j][k];
}

//Testing Symbols
int sym(char strs)
{
    j++;
    k=0;
    words[j][k]=strs;
    return words[j][k];
}



//Testing Character taken input
int start(char str)
{
    for(i=0;i<=51;i++)
        if(str==alphabets[i])
        {
            alpha(str);
            return words[j][k];
        }
    for(i=0;i<=10;i++)
        if(str==numbers[i])
        {
            num(str);
            return words[j][k];
        }
    for(i=0;i<=194;i++)
        if(str==symbols[i])
        {
            sym(str);
            return words[j][k];
        }
    return words[j][k];
}




//Find frequency of each word/number/character
int frequency()
{
    int count=0,l=0;
    char string1[COL_SIZE],string2[COL_SIZE];
    //Initialize each element of frequency array
    for(j=0;j<=ROW_SIZE;j++)
    {
        freq[j]=-1;
    }
    //Counting frequency of words/numbers/symbols
    for(j=0;j<=ROW_SIZE;j++)
    {
        count=1;
        for(l=j+1;l<=ROW_SIZE;l++)
        {
            k=0;
            while(k<COL_SIZE)
            {
                string1[k]=words[j][k];                 //Storing pivot word to string1
                string2[k]=words[l][k];                 //Storing comparing word to string2
                k++;
            }
            if(stricmp(string1,string2)==0)
            {
                freq[l]=0;
                count++;
            }
        }
        if(freq[j]!=0)
        {
            freq[j]=count;
        }
    }

    return freq[j];
}




//<<============================================================================>>
//<<============================================================================>>
//Main() function
int main()
{
    int string_length=0,c=0,temp_freq[ROW_SIZE];        //Integer variables
    char string,temp_words[ROW_SIZE][COL_SIZE];         //Character variables/arrays
    FILE *fp,*fp1;                                       //Pointers to file



//Creating arrays of alphabets/numbers/symbols
    //Array of alphabets
    i=0;
    for (c=65;c<=90;c++)
    {
        alphabets[i]=((char)c);
        i++;
    }
    for (c=97;c<=122;c++)
    {
        alphabets[i]=((char)c);
        i++;
    }

    //Array of numbers
    i=0;
    for (c=48;c<=57;c++)
    {
        numbers[i]=((char)c);
        i++;
    }

    //Array of symbols
    i=0;
    for (c=0;c<=47;c++)
    {
        symbols[i]=((char)c);
        i++;
    }
    for (c=58;c<=64;c++)
    {
        symbols[i]=((char)c);
        i++;
    }
    for (c=91;c<=96;c++)
    {
        symbols[i]=((char)c);
        i++;
    }
    for (c=123;c<=256;c++)
    {
        symbols[i]=((char)c);
        i++;
    }



//Accessing file (.txt)
    fp=fopen("input.txt","r");

    //If File is not present at the provided address
    if(fp==NULL)
    {
        printf("\nFile Not Found!\n");
        return 1;
    }

    //File present at the provided address
    else
    {
        while ((string=(char)fgetc(fp))!=EOF)
        {
            start(string);
            string_length++;                    //Counting total number of characters
        }
    }

    printf("\nFile contains %d characters.\n\n",string_length);       //Total number of characters



//Calling frequency function
    frequency();


//Swap words to show them in descending order of frequency
    for(i=0;i<=ROW_SIZE;i++)
    {
        for(j=i+1;j<=ROW_SIZE;j++)
        {
            if(freq[i]<freq[j])
            {
                for(k=0;k<COL_SIZE;k++)                 //Swapping Words
                {
                    temp_words[i][k]=words[i][k];
                    words[i][k]=words[j][k];
                    words[j][k]=temp_words[i][k];
                }
                temp_freq[i]=freq[i];                   //Swapping Frequency
                freq[i]=freq[j];
                freq[j]=temp_freq[i];
            }
        }
    }



//Storing words and frequency to a file
    fp1=fopen("output.txt","w");
    for(j=0;j<=ROW_SIZE;j++)
    {
        if(freq[j]!=0)
        {
            for(k=0;k<COL_SIZE;k++)
            {
                fputc(words[j][k],fp1);                 //Words
            }
            fprintf(fp1,"occurred"),
            fprintf(fp1," %d ",freq[j]);                //Frequency
            fprintf(fp1,"time(s).\n");
        }
    }



//Printing words with frequency to std out
    for(j=0;j<=ROW_SIZE;j++)
    {
        if(freq[j]!=0)
        {
            for(k=0;k<COL_SIZE;k++)
            {
                printf("%c",words[j][k]);       //Words
            }
            printf("occurred %d time(s). \n",freq[j]);      //Frequency
        }
    }



//Close open files
    fclose(fp);
    fclose(fp1);
    return 0;
}


//<<============================================================================>>
//<<=========================THE-END============================================>>