#include<iostream>
using namespace std;
int main(){
    FILE*fpt1;
    fpt1=fopen("random.txt","w+");
    char s[65];
    s[64]='\0';
    int N=500000;
    while(N--){
    for(int i=0;i<64;i++){
        int random_number=rand()%2;
        s[i]=(random_number+48);
    }
    fprintf(fpt1, "%s\n",s);
    }
    return 0;
}