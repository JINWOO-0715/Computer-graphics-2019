#include<stdio.h>
#include<stdlib.h>


int main()
{
	FILE *fop;

	char cha;
	char total[20];
	int word_count = 0;
	int num_count = 0;
	int num[10];
	int num2 = 0;
	char *ptr = total;
	fop = fopen("text.txt", "r");
	if (fop == NULL)
	{
		printf("실패");
	}

	while (!feof(fop))
	{
		cha = fgetc(fop);
		if (cha == ' ')
		{
			word_count++;
		}
		if (cha == '\n')
		{
			word_count++;
		}
		if (cha >= '0' && cha <= '9')
		{
			num_count++;

		}
		printf("%c", cha);

		fscanf(fop, "%*[^0-9]");
		num2 = 
	}

	

		num = fscanf(fop, "%d", num + i);
		if (cha == EOF) break;
	

	}


	

	printf("\n");
	printf("단어 수 : %d \n", word_count+1);
	printf("숫자 수 : %d", num_count);



	fclose(fop);

}