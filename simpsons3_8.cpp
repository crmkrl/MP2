#include<iostream>
#include<math.h>
#include<iomanip>
#include<stdlib.h>
#include<vector>
#include <numeric>

#define f(x) (1/sqrt(M_PI*2))*exp(-0.5*pow(x,2))

using namespace std;

float roundoff(float value, unsigned char prec)
{
  float pow_10 = pow(10.0f, (float)prec);
  return round(value * pow_10) / pow_10;
}

int main()
{
 float lower, upper, integration=0.0, stepSize, k;
 int i, N, prec;

float fx = 0.0;
float x_ = 0.0;
float h = 0.0;


 cout<<"Enter the precision: ";
 cin>>prec;
 cout<< setprecision(prec)<< fixed;

 cout<<"Enter lower limit of integration: ";
 cin>>lower;
 cout<<"Enter upper limit of integration: ";
 cin>>upper;
 cout<<"Enter N: ";
 cin>>N;
 h = (upper-lower)/N;
 
 /* Calculation */
cout<< endl<<"*********************"<< endl;
cout<<"Simpsons 1/3 Method"<< endl;
cout<<"*********************"<< endl;
cout << setw(10) << "X\t" << setw(10) << "F(x)\t" << setw(10) << "Multiplier\t" << setw(10) << "Integration\t" << endl;

x_ = lower;
float sum, I;
int mult = 1;

for (i=0; i<=N; i++) {
  if (i==0 || i==N) {
    mult = 1;   //first and last iteration
  } else {
    if (i%3==0) {
      mult = 2;
    } else {
      mult = 3;
    }
  }

  fx = roundoff(f(x_),prec);
  integration = roundoff((fx * mult), prec);
  cout << setw(10) << x_ << "\t" << setw(10) << f(x_) << "\t" << setw(10) << mult << "\t" << setw(10) << integration << endl;
  
  x_ = roundoff(x_ + h, prec);
  sum = roundoff((sum + integration),prec);
}

  I = roundoff(((3*h)/8)*sum,prec);
  cout << endl << "The sum of integration: " << sum << endl << endl;
  cout << endl << "The required value is: " << I << endl << endl;

 return 0;
}