#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student{
    char fname[255];
    char lname[255];
    char major[255];
    char deg[255];
    float gpa;
    int chours;
    char ta[4];
    char advisor[255];
};
char *removecr(char *rmstr)
{
    int len = strlen(rmstr);
	for(int a=0;a<len;a++)
	{
	   if(rmstr[a] == 13)
	   {
	        for(int b=a;b<len;b++)
	        {
	             rmstr[b] = rmstr[b+1];
	        }
	        len--;
	        a--;
	    }
	}
	return rmstr;
}

int main()
{
    char datastore[1286];
    char *fstring;
    float topgpa[3],avg = 0,sum=0;
    int recount = 0,tokcount=0,a=0,b=0,i=0,j=0,k=0,degcount=0,majorcount=0,gpacount=0,cstudents=0,advisorcount=0;
    FILE *inpfp = fopen("students_dataset.csv","r");
    if (inpfp == NULL)
    {
        printf("File is not found");
        return(-1);
    }
    while (fgets(datastore,1286,inpfp)!=NULL)
    {
        recount++;
    }
    fclose(inpfp);
    struct Student* stu = malloc(recount* sizeof(struct Student));
    char store[recount][255];
    char major[recount][255];
    char advisor[recount][255];
    FILE *fpr = fopen("students_dataset.csv","r");
    if (fpr == NULL)
    {
        printf("File is not found");
        return(-1);
    }
    fgets(datastore,1286,fpr);
    while (fgets(datastore,1286,fpr)!=NULL)
    {
       fstring = strtok(datastore,",");
       while(fstring!=NULL)
       {
           tokcount++;
	   
           switch(tokcount){
               case 1:
               strcpy(stu[i].fname,fstring);	
               break;
               case 2:
               strcpy(stu[i].lname,fstring);
               break;
               case 3:
               strcpy(stu[i].major,fstring);
               break;
               case 4:
               strcpy(stu[i].deg,fstring);
               break;
               case 5:
               stu[i].gpa = atof(fstring);
               break;
               case 6:
               stu[i].chours = atoi(fstring);
               break;
               case 7:
               strcpy(stu[i].ta,fstring);
               break;
               case 8:
               strcpy(stu[i].advisor,fstring);
               break;
               
           }	
	   fstring = strtok(NULL,",");
       }
       tokcount = 0;
        i++;
    }
    fclose(fpr);
    for(i=0;i<recount-1;i++)
    {
	for(j=0;j<recount-1;j++)
	{
	    if(strcmp(major[j],stu[i].major)==0)
	    {
		break;
	    }
	    else if(strcmp(major[j],"")==0)
	    {
		strcpy(major[j],stu[i].major);
		majorcount++;
		break;
	    }

	}	
    }
    for(i=0;i<recount-1;i++)
    {
	for(j=0;j<recount-1;j++)
	{
	    if(strcmp(store[j],stu[i].deg)==0)
	    {
		break;
	    }
	    else if(strcmp(store[j],"")==0)
	    {
		strcpy(store[degcount],stu[i].deg);
		degcount++;
		break;
	    }

	}	
    }
    printf("Total number of degrees: %d\n",degcount);
    for(j=0;j<degcount;j++)
    {
	    printf("%s\n",store[j]);
    }
    printf("-------------------------------------------------------\n"); 
    printf("Top 3 students with highest GPAs:\n\n");
    for(i=0;i<recount-1;i++)
    {
 	if(stu[i].gpa == topgpa[0] || stu[i].gpa == topgpa[1] || stu[i].gpa == topgpa[2])
        {
	    continue;
        }
        if (stu[i].gpa > topgpa[0])
        {
            topgpa[2] = topgpa[1];
            topgpa[1] = topgpa[0];
            topgpa[0] = stu[i].gpa;
        }
        else if (stu[i].gpa > topgpa[1])
        {
            topgpa[2] = topgpa[1];
            topgpa[1] = stu[i].gpa;
        }
        else if (stu[i].gpa > topgpa[2])
        {
            topgpa[2] = stu[i].gpa;
        }
    }
    for(i=0;i<3;i++)
    {
        for(j=0;j<recount-1;j++)
        {
            if(stu[j].gpa == topgpa[i])
            {
                printf("Student name: %s %s, GPA: %f\n",stu[j].fname,stu[j].lname,stu[j].gpa);
            }
        }
    }
    printf("-------------------------------------------------------\n"); 
    printf("Average credit hours of the college:\n\n");
    for(i=0;i<recount-1;i++)
    {
	sum = sum + stu[i].chours;
    }
    avg = sum/(recount-1);
    printf("Average credit hours: %.2f\n", avg);
    printf("-------------------------------------------------------\n"); 
    printf("Average GPA of the Computer science students:\n\n");
    sum = 0;
    for(i=0;i<recount-1;i++)
    {
	if(strcmp(stu[i].major,"Computer Science")==0)
	{
	    sum = sum + stu[i].gpa;
	    cstudents++;
	}
    }
    avg = sum/cstudents;
    printf("Average GPA: %.4f\n", avg);
    printf("-------------------------------------------------------\n"); 
    printf("Total number of advisors:\n\n");
    for(i=0;i<majorcount;i++)
    {
        for(j=0;j<recount-1;j++)
        {
            if(strcmp(major[i],stu[j].major)==0)
            {
                for(k=0;k<recount-1;k++)
                {
                char *str1 = removecr(advisor[k]);
                char *str2 = removecr(stu[j].advisor);
		        
                if(strcmp(str1,str2)==0)
                {
                    break;
                }
                else if(strcmp(advisor[k],"")==0)
	            {
		             strcpy(advisor[k],stu[j].advisor);
		             advisorcount++;
		             break;
	            }
                }
            }
        }
	for(k=0;k<recount-1;k++)
	{
	   strcpy(advisor[k],"");
	}
        printf("%s: %d\n",major[i],advisorcount);
 	advisorcount = 0;
    }
    printf("-------------------------------------------------------\n"); 



    return 0;
}

//To remove a character in a strnig: https://www.tutorialgateway.org/c-program-to-remove-all-occurrences-of-a-character-in-a-string/