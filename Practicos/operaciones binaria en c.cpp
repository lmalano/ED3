#include <iostream>
using namespace std;


int main() {
 int a,b;
 char c,d;
 	cout<<"ingrese el valor del primero numero\n";
 	cin>>a;
 	cout<<"ingrese el valor del segundo numero\n";
 	cin>>b;
 	  c=a;
 	  d=b;
 	
 	cout<<"desplazo el primer numero 4 lugares a la izquieda\n";
 	
 	cout<<(a<<4)<<endl;
 	
 	cout<<"desplazo el primer numero 4 lugares a la derecha\n";
 	
 	cout<<(a>>4)<<endl;
 	
 	cout<<"hago and con el 1 y 2 numero\n";
 		
 	printf("%d\n",c & d) ;
 	
 	cout<<"hago or con el 1 y 2 numero\n";
 		
 	printf("%d\n",c|d);
 	
 	cout<<"hago xor con el 1 y 2 numero\n";
 		
 	printf("%d\n",c^d);
 	
 	cout<<"hago not con el 1 numero\n";
 		
 	printf("%d\n",~c);
 	
 	
 	
 	
 	
 }
 	
