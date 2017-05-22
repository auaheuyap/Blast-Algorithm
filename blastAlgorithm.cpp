#include <iostream>
#include <conio.h>
#include <string.h>
#define SIZE 11
#define WINDOW 3

using namespace std;

int blosum62[SIZE][SIZE];

/*
initblosum62 : menginisiasi matriks blosum62 seperti berikut

	A	B	C	D	E	F	G	H	I	J
A	0	-1	-2	-3	-4	-5	-6	-7	-8	-9
B	-1	2	-1	-2	-3	-4	-5	-6	-7	-8
C	-2	-1	4	-1	-2	-3	-4	-5	-6	-7
D	-3	-2	-1	6	-1	-2	-3	-4	-5	-6
E	-4	-3	-2	-1	8	-1	-2	-3	-4	-5
F	-5	-4	-3	-2	-1	10	-1	-2	-3	-4
G	-6	-5	-4	-3	-2	-1	12	-1	-2	-3
H	-7	-6	-5	-4	-3	-2	-1	14	-1	-2
I	-8	-7	-6	-5	-4	-3	-2	-1	16	-1
J	-9	-8	-7	-6	-5	-4	-3	-2	-1	18

*/

void initblosum62(){
     for(int i=0;i<SIZE;i++)
             for(int j=0;j<SIZE;j++){
                     if(i==j)blosum62[i][j]=i+j;
                     else blosum62[i][j]=abs(i-j)*-1;
                     }
     }

//menampilkan matriks blosum62 pada konsol

void displayblosum62(){
     for(int i=0;i<SIZE;i++){
             for(int j=0;j<SIZE;j++){cout<<blosum62[i][j]<<" ";}
             cout<<endl;}
     cout<<endl;
     }

//menghitung nilai blosum berdasarkan matriks blosum62

int countScore(char x,char y){
    return blosum62[x-'A'][y-'A']; 
    }
    

//menghitung nilai maksimum dari query a terhadap sequence b

int maxscore(char a[100], char b[100]){
    //mencari maximum score (maxscore) dan lokasi maximum score query a (maxi) dan sequence b (maxj)
    int maxscore=0,score,maxi,maxj;
    for(int i=0;i<strlen(a)-WINDOW+1;i++){
            for(int j=0;j<strlen(b)-WINDOW+1;j++)
                    {
                     //menghitung score sequence berwindow 3                            
                     score=0;
                     for(int k=0;k<WINDOW;k++){
                             score+=countScore(a[i+k],b[j+k]);
                              
                             }
                     //menentukan maximum score       
                     if(maxscore<score){maxscore=score;maxi=i,maxj=j;}    
                     }              
    }
    //expand 
    int newscore=1000,r=1,l=1;                     
    
    //expand right
    while(maxscore<=newscore && maxj+WINDOW-1+r<strlen(b) && maxi+WINDOW-1+r<strlen(a)){
                    newscore=countScore(a[maxi+WINDOW-1+r],b[maxj+WINDOW-1+r])+maxscore;
                    if(newscore>=maxscore){maxscore=newscore;r++;}         
                    }          
    //expand left
    newscore=1000;
    while(maxscore<=newscore && maxi-l>=0 && maxj-l>=0){
                    newscore=countScore(a[maxi-l],b[maxj-l])+maxscore;
                    if(newscore>=maxscore){maxscore=newscore;l++;}         
                    }
                    
    //display hasil expand
    for(int i=maxi-l+1;i<=maxi+WINDOW-1+r-1;i++)cout<<a[i];
    cout<<endl;                
    for(int i=maxj-l+1;i<=maxj+WINDOW-1+r-1;i++)cout<<b[i];
    cout<<endl;
    
    //return skor maksimal
    return maxscore;
    }    

int main(){
    char q[100]="ABCDEFGHIAB",s1[100]="CDEFGHFEDCBA",s2[100]="IHGFGHIAB",s3[100]="FDABCAIADBC";
    initblosum62();
    displayblosum62();
    cout<<maxscore(q,s1)<<endl<<endl;
    cout<<maxscore(q,s2)<<endl<<endl;
    cout<<maxscore(q,s3)<<endl<<endl;
    getch();
    }
