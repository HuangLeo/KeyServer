#include <stdio.h>
#include <time.h>
main()
{
	time_t timep;
	time(&timep);
	printf("%ld\n",timep);
	long int shijian;
	shijian = timep;
	printf("shijian=%ld\n",shijian);
}
