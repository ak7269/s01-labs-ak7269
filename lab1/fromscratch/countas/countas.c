#include <stdio.h>

int  main(int argc, char** argv)
{
     
    
   if (argc!=2) {
     printf("Not 1 argument!");
     return 0;
  }

    
    char* str=argv[1];
    int length=0;
    int x=0;
    int a=1;
    while(a==1)
    {  
	 if(str[x]=='\0')
		 a=2;
	 else{ 
		length++;
	 }
	x++;
    }
    
   
    int frequency=0;
    int i=0;
    while(i<length)
    {
	  if(str[i]=='a')
		  frequency++;
	  i++;

    }
    printf("%d\n",frequency);
	return 0;

}
