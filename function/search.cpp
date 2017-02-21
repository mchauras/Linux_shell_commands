#include<iostream>
#include<vector>
#include<string>
#include<ctime>
#include<fstream>
#include<cctype>
using namespace std;

vector<int> kmp_preprocessor(string K)
{
    vector<int> T(K.size()+1,-1);
    int i=0,j=-1;

    while(i<K.size())
    {
        while(j>=0 && tolower(K[i])!=tolower(K[j])) j=T[j];
        i++; j++;
        T[i]=j;
    }
    return T;
}

void string_matcher(string S,string K,vector<int> T,int &counter,int linenumber)
{


    int i=0,j=0;
    while(i<S.length())                   //KMP search
    {
        while(j>=0 && tolower(S[i])!=tolower(K[j])) j=T[j];
        i++; j++;
        if(j==K.length())
        {
            printf("\n%d.[%d]",linenumber,i-j+1);
            counter++;
            printf("....");
            if(i-j-10<0) for(int k=i-j;k<=i-j+15 && S[k]!='\0' ;k++) printf("%c",S[k]);
            else         for(int k=i-j-10;k<=i-j+5 && S[k]!='\0';k++) printf("%c",S[k]);
            printf("....");
            j=T[j];
        }
    }
    return;
}


int main(int argc,char **argv)
{
   clock_t start=clock();
   vector<int> T(sizeof(argv[2])+1);
   int occurrence=0,linenumber=0;
   if(argc!=3)
   {
        printf("Usage: search <filename> <string to be searched>\n");
        return 1;
   }
    T=kmp_preprocessor(argv[2]);
    string info;
    ifstream foo(argv[1],ios::in);
    if(!foo)
    {
        printf("\nFile not found!\n");
        return 1;
    }
    while(getline(foo,info,'\n'))
    {
        linenumber++;
        string_matcher(info,argv[2],T,occurrence,linenumber);
    }
    foo.close();

    printf("\n\nTotal occurrences: %d",occurrence);
    clock_t ends=clock();
    printf("\nRunning Time : %3.3f seconds\n",(float)(ends-start)/CLOCKS_PER_SEC);
    return 0;
}
