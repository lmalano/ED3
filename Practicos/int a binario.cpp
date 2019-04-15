#include<stdio.h> 

void binario(int); 

int main() 
{ 
   int num; 
    
   printf("Introduce el numero que deseas convertir a binario:\n"); 
   scanf("%d",&num); 
   binario(num); 
    
   printf("\n"); 
   return 0; 
} 





void binario(int num) 
{ 
   int aux; 
    
   if(num==0) 
      return; 

   aux=num%2; 
   num=num/2; 
   binario(num); 
   printf("%d",aux); 
}
