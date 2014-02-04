#include <stdlib.h>
#include <stdio.h>

#define WHEEL_LENGTH 7
#define PRINT_LENGTH
#define PRINT_WHEEL

void n_primes(int * results, int n){
	if(n < 1)
		return;
	*results = 2;

	int i, j, index;
	for(i = 3, index = 1; index < n; i+=2){
		int prime = 1;
		for(j = 3; j * j <= i; j+=2)
			if(i % j == 0){
				prime = 0;
				break;
			}
		if(prime)
			results[index++] = i;
	}
}

int array_product(int * nums, int len){
	int product = 1;

	int index;
	for(index = 0; index < len; index++){
		product *= nums[index];
	}

	return product;
}

int calculate_wheel_len(int * primes, int len){
	int calc_len = 1;

	int i;
	for(i = 0; i < len; i++){
		calc_len *= primes[i] - 1;
	}

	return calc_len;
}

int * init_wheel(int num_primes, int * out_len){
	/* --------------- Find the primes --------------- */
	int * nums = malloc((num_primes + 1)* sizeof(int));
	n_primes(nums, num_primes + 1);

	/* --------------- Product of the primes  --------------- */
	int product = array_product(nums, num_primes);

	/* --------------- Make the wheel  --------------- */
	int calc_len = calculate_wheel_len(nums, num_primes);
	int * wheel = calloc(calc_len, sizeof(int));

	int i;
	int start = nums[num_primes];
	int last_coprime = start;
	int wheel_index = 0;
	int nums_index;

	// Find all the numbers coprime to the primes in 'nums' in the wheel's
	// 'circumference' (the size of which is the product of those primes)
	for(i = start; i < product; i++){
		int skip = 0;
		// Skip is set if a number is not coprime to one of the primes in nums
		for(nums_index = 0; nums_index < num_primes; nums_index++){
			if(i % nums[nums_index] == 0){
				skip = 1;
				break;
			}
		}
		// This only gets executed if 'i' is coprime to every prime in 'nums'
		// (which are the first 'num_primes' prime numbers)
		if(!skip && i != start){
			wheel[wheel_index] = i - last_coprime;
			wheel_index++;
			last_coprime = i;
		}
	}
	// To go from the end of the wheel back to the '1' spoke
	// Unless we're just doing a 2wheel in which the next
	// section does the trick (go from the 1 spoke to after
	// the last prime in 'num_primes')
	if(num_primes != 1){
		wheel[wheel_index] = 2;
		wheel_index++;
	}

	// This jumps from the 1 spoke to the first prime after the last
	// one in 'nums'
	wheel[wheel_index] = start - 1;
	wheel_index++;

	// We don't need the list of primes that made the wheel anymore
	free(nums);
	// Set the length of the wheel and return the wheel
	*out_len = calc_len;
	return wheel;
}

int main(int argc, char *argv[]){
	/* --------------- Set the number of primes to use for the wheel --------------- */
	int len = WHEEL_LENGTH;
	if(argc > 1)
		len = atoi(argv[1]);

	/* --------------- Create the wheel  --------------- */
	int wheel_len = 0;
	int * wheel = init_wheel(len, &wheel_len);
	if(wheel == NULL){
		printf("This should never happen.");
	}

	/* --------------- Print Junk  --------------- */
	#ifdef PRINT_LENGTH
		printf("Length: %d\n\n", wheel_len);
	#endif

	#ifdef PRINT_WHEEL
		int i;
		for(i = 0; i < wheel_len; i++){
			printf("%d", wheel[i]);
			if(i != wheel_len - 1)
				printf(", ");
			if(i % 16 == 15)
				printf("\n");
		}
		printf("\n\n");
	#endif
	return 0;
}
