#include "mylibrary.h"
int sum_of_1_to_n(int n)
{
	int sum = 0;

	//TODO: sum all numbers from 1 to n
	for(int i=0 ; i<=n; i++){
	sum+=i;
	}

	return sum;
}

int sum_of_even_numbers(int *array, int count)
{
	int sum = 0;
	for (int i=0;i<count;++i)
	{
		//TODO: only add even numbers, e.g., 4. Skip odd numbers, e.g., 3
		if(array[i]%2==0){
			
		sum += array[i];
		
		}

	}
	return sum;
}

int max_of_numbers(int *array, int count)
{
	//TODO: return the maximum number from the array
	for(int i=0; i<count; i++){
	   if(array[0]<array[i]){
	     array[0]=array[i];
	   }
	}
	return array[0];
}

int reversed_number(int number)
{
	int reversed = number;

	//TODO: if input is 12345, return 54321
        int x=0;
	while(reversed>0){
	x=x*10+reversed%10;
	reversed=reversed/10;
	}
	reversed=x;
	return reversed;
}

int is_prime(int number)
{
	//TODO: return 1 if the input number is prime, otherwise 0
        for(int i=2;i<number/2;i++){
	if(number%i==0){
	return 0;
	}	
	}
	return 1;
}

int count_primes(int start, int end)
{
	//TODO: return the count of prime numbers in range [start, end] inclusive.
       int counter=0;
	for(int i=start;i<=end;i++){
	if(is_prime(i)){
	counter++;
	}	
	}
	return counter;
}


char alphabet_index(int index)
{
	//TODO: for index 0, return A. index 1, B, etc. until 25 for Z.
	//if index is out of range, return space ' '.
	char x='A'+index;
	return x;
}

