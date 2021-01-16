#include <stdio.h>
#include <stdlib.h>

struct tuple {
  float left;
  float right;
};

typedef struct tuple tuple;

float getMean(int arr[], int size) {
  float sum = 0;

  for(int i = 0; i < size; ++i) { sum += arr[i]; }

  return sum / size;
}

tuple* estimateCoefficient(int x[], int y[], int size) {
  tuple* rt = (tuple*)malloc(sizeof(tuple));

	float mX, mY, SS_xy, SS_xx, b_1, b_0;
	float tempSum = 0;

  /* Get mean of x & y */
  mX = getMean(x, size);
  mY = getMean(y, size);

	/* Calculate cross deviation */
  for(int i = 0; i < size; ++i) {
    tempSum += x[i] * y[i];
  }

  /* SS_xy */
  SS_xy = tempSum - size * mY * mX;

	/* Calculate deviation around X */
  tempSum = 0;
  for(int i = 0; i < size; ++i) {
    tempSum += x[i] * x[i];
  }
	
  /* SS_xy */
  SS_xx = tempSum - size * mX * mX;

	/* Calculate regression coefs */
  b_1 = SS_xy / SS_xx;
  b_0 = mY - b_1*mX;

	/* Set tuple */
	rt->left = b_0;
	rt->right = b_1;
 
  return rt;
}

float predict(tuple* t, int inp) {
	return t->left + t->right*inp;
};

int main(void) {
  int x[] = {0, 1, 2, 3, 4, 5, 6, 7, 8,  9, 11};
  int y[] = {1, 3, 2, 5, 7, 8, 8, 9, 10, 12, 11};
  int size = sizeof(x)/sizeof(int);

  tuple* result = estimateCoefficient(x, y, size);

	printf("h(x_i) = %f + %f*x_i\n", result->left, result->right);
	printf("PREDICTED FOR X=100: %f\n", predict(result, 100));
  return 0;
}