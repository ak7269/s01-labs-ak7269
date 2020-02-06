#include <stdio.h>

int  main(int argc, char** argv)
{
     
    
   if (argc!=2) {
     printf("Not 1 argument!");
     return 0;
  }

    
   char* s=argv[1];
    int length=0;
    int x=0;
   int a=1;
    while(a==1)
    {  
	 if(s[x]=='\0')
		 a=2;
	 else{ 
	length++;
	 }
	x++;
    }
    
   
    int count=0;
    for(int i=0;i<length;i++)
    {
	  if(s[i]=='a')
		  count++;

    }
    printf("%d",count);
	return 0;

}
