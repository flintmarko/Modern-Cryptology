#include <iostream>
using namespace std;
int main()
{
  char ch[100],temp[100];
  FILE *fi,*fo;
  fi = fopen("output_clean.txt","r+");
  fo = fopen("output_1.txt","w+");
  long int j = 0;
  while(j < 200000)
  {
    int flag = 0;
    strcpy(ch,temp);
    fscanf(fi,"%s",ch);
    //fprintf(fo,"%s\n",ch);
    for(int i=0;i<16;i++){
          //int j=0;
          int x = ch[i]-'f';
          //fprintf(fo," %d ",x);
          for(int k=0;k<4;k++){

            fprintf(fo, "%d", ((x>>(3-k))&1) );
          }
    }
    fprintf(fo,"\n");
    j++;
  }
}