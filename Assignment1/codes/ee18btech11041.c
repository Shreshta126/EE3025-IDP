
#include <complex.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


double complex* fft(double complex* p,int n)
{
	if (n <= 1)
	{
		return p;
	}
	
	double complex*pe = (double complex*)malloc((n/2) * sizeof(double complex));
	double complex*po = (double complex*)malloc((n - (n/2))*sizeof(double complex));

	for(int i=0;i<n;i=i+2)
	{
		if (i/2<n/2) pe[i/2] = p[i];

		if (i+1< n && i/2 < n-(n/2)) po[i/2] = p[i+1];	
		 
	}

	double complex* ye = fft(pe,n/2);
	double complex* yo = fft(po,n-(n/2));
	

	double complex* y = (double complex*)malloc(n*sizeof(double complex));
	
	for(int i=0;i<n/2;i++)
	{
		double  wi = sin(2*M_PI*i/n);
		double wr = cos(2*M_PI*i/n);
		y[i] = ye[i] + (wr+I*wi)*yo[i];
		y[i + n/2] = ye[i] - (wr+I*wi)*yo[i];; 
	}
	
	free(ye);
	free(yo);
	return y;
}


double complex* ifft(double complex* p , int n)
{
	if (n <= 1)
	{
		return p;
	}
	
	double complex*pe = (double complex*)malloc((n/2) * sizeof(double complex));
	double complex*po = (double complex*)malloc((n - (n/2))*sizeof(double complex));

	for(int i=0;i<n;i=i+2)
	{
		if (i/2<n/2) pe[i/2] = p[i];

		if (i+1< n && i/2 < n-(n/2)) po[i/2] = p[i+1];	
		 
	}

	double complex* xe = fft(pe,n/2);
	double complex* xo = fft(po,n-(n/2));
	

	double complex* x = (double complex*)malloc(n*sizeof(double complex));
	
	for(int i=0;i<n/2;i++)
	{
		double  wi = sin(-2*M_PI*i/n);
		double wr = cos(-2*M_PI*i/n);
		x[i] = xe[i] + (wr+I*wi)*xo[i];
		x[i + n/2] = xe[i] - (wr+I*wi)*xo[i];; 
	}
	
	free(xe);
	free(xo);
	return x;	
}


int main()
{
	int n=8;
	double complex* x = (double complex*)malloc(n*sizeof(double complex));  
	x[0] = 1;
	x[1] = 2;
	x[2] = 3;
	x[3] = 4;
	x[4] = 5;
	x[6] = 6;
	x[7] = 7;

	double complex* y = fft(x,n);
	double complex* xf = ifft(y,n); 
	printf("%s\n","fft" );
	for(int i=0;i<n;i++)
	{
		  printf( "%f %f\n", creal(y[i]), cimag(y[i]));

	}
	printf("%s\n","ifft" );
	for(int i=0;i<n;i++)
	{
		  printf( "%f %f\n", creal(xf[i])/n, cimag(xf[i])/n);

	}
}