#include <omp.h>

int main(){
	int a=0;
	int array[10];
	for(int i=0; i<10; ++i){
		array[i]=0;
	}
	#pragma omp parallel for private(a)
	for(int k=0; k<10;++k){
		x=array[k];
		array[k]=x+5;
	}

	for(int i=0; i<10; ++i){
		printf("%d ",array[k]);
	}
	return 0;
}
