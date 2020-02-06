#include <stdio.h>
#include <string.h>

int  main(int argc, char** argv)
{
     char *a=argv[1];
     char *b=argv[2];

   if (argc!=3) 
   {
     printf("Not 2 arguments!");
     return 0;
  }

    

    int length_a=strlen(a);
    int length_b=strlen(b);

	if(length_a<3)
	{
		if(length_b<3)
		{

			printf("Strings are too short!");
			return 0;
		}
		
	}
    for(int i=0;i<3;i++)
    {
	  printf("%c",a[i]);
    }

    int j=0;

    while(j<3)
    {
    printf("%c",b[j]);
    j++;
    }
	return 0;

}
