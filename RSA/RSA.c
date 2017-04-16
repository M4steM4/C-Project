#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define True 1
#define False 0

int number, messageLen;

long createRandomNumber();//random 2 prime number function
int createPublicKey(long bufferKey); //make public key function
int createPrivateKey(int e, long bufferKey);//make private key function
int createEncryptText(char *Plain_text, long *Cyper_text, int key); //plain text to encrypt text function
int createPlainText(long *Cyper_text, char *Plain_text, int key); //encrypt text to plain text function
long modOpration(long n, long e, long m);	//mod function
int isPrime(int number);		//prime number check function
int myCommonFactor(long x, long y){ //minimum common divisor check function
  return y == 0 ? x : myCommonFactor(y, x % y) ;
}

void main(){
	char recvMsg[100];
  	char buffer[100];
	int publicKey, privateKey;
	long bufferKey;
  	long sendMsg[100];

	bufferKey = createRandomNumber();	// make 2 prime key & make number value
	publicKey = createPublicKey (bufferKey);	//make public key
	privateKey = createPrivateKey (publicKey, bufferKey);	//make private key
	printf("Input string : ");
  	gets(buffer);
	createEncryptText(buffer, sendMsg, publicKey);
	createPlainText(sendMsg, recvMsg, privateKey);

  FILE * fp;
  fp = fopen("information.txt", "a");
  fprintf(fp,"publicKey : %d\n privateKey : %d\n Encrypt number : %d\n\n\n Plain text : %s\n",publicKey, privateKey, bufferKey, recvMsg);
  fclose(fp);
  printf("Misson complete\nCheck your file!");
}

long createRandomNumber(){
	int Prime[2];
	time_t t;
	srand((unsigned int)time(&t));
	for (int i=0; i<2; i++){
		do{
      Prime[i]=rand()%100;
    } while(isPrime(Prime[i]) );
	}
	number = Prime[0]*Prime[1];
  FILE * fp;
  fp = fopen("information.txt", "w");
	fprintf(fp,"first number : %d\n second number : %d\n", Prime[0], Prime[1]);
  fclose(fp);
	return (Prime[0]-1)*(Prime[1]-1);
}

int createPublicKey(long bufferKey){
	long e;
	do{
		e=rand()%100;
		if((e<bufferKey) && (myCommonFactor(e,bufferKey)==1)){
      return e;
    }
	} while(1);
}

int createPrivateKey(int e, long bufferKey){
	int d=0;
	while(((e*d)%bufferKey)!=1){
    d++;
  }
	return d;
}

int isPrime(int number){
   int limit;
   if (!(number%2)){
     return (True);
   }
   limit = (int)sqrt(number) + 1;
   for(int i = 3; i <= limit; i += 2){
      if(!(number%i)){
        return (True);
      }
    }
   return (False);
}

long modOpration(long n, long e, long m){
	long residue = 1;
	for(int i=1; i<=e; i++){
		residue *= n;
		residue %= m;
	}
	return residue;
}

int createEncryptText(char *Plain_text, long *Cyper_text, int key){
	messageLen=strlen(Plain_text);
	for(int i = 0; i < messageLen; i++){
		Cyper_text[i]= (long)modOpration( Plain_text[i], key, number);
  }
	Cyper_text[messageLen] = '\0';
	FILE * fp;
  fp = fopen("EncryptText.txt", "w");
  fprintf(fp,"-EncryptText\n");
	for (int i=0; i<messageLen; i++)
		fprintf(fp, "%d\n",Cyper_text[i]);
  fclose(fp);
	return 0;
}

int createPlainText(long *Cyper_text, char *Plain_text, int key){
	for(int i=0; i<messageLen; i++)
		Plain_text[i]= (char)modOpration(Cyper_text[i], key, number);
	Plain_text[messageLen] = '\0';

  FILE * fp;
  fp = fopen("EncryptText.txt", "a");
  fprintf(fp,"-PlainText\n");
	for (int i=0; i<messageLen; i++)
		fprintf(fp, "%d\n",Plain_text[i]);
  fclose(fp);
	return 0;
}
