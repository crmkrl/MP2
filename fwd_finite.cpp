#include<iostream>
#include<math.h>
#include<iomanip>
#include<stdlib.h>
#include<vector>
#include <numeric>
#include <algorithm>

using namespace std;

#define f(x) (1/sqrt(3.141592654*2))*exp((-1*pow(x,2))/2)

float roundoff(float value, unsigned char prec)
{
  float pow_10 = pow(10.0f, (float)prec);
  return round(value * pow_10) / pow_10;
}
int main()
{
      float Xi = 0.75, h=0.125;
      int prec, n=3;
      float lower,upper;


      cout<<"Enter precision: ";
      cin>>prec;
      // cout<< setprecision(prec)<< fixed;

      cout<<"Enter lower limit of integration: ";
      cin>>lower;
      cout<<"Enter upper limit of integration: ";
      cin>>upper;
      // cout<<"Enter N: ";
      // cin>>n;
      // cout<<"Enter h:";
      // cin>>h;

      cout<< endl<<"*********************"<< endl;
      cout<<"FORWARD DIFFERENCE TABLE"<< endl;
      cout<<"*********************"<< endl;

      std::vector<float> truncF;
      std::vector<float> accF;
      float Xi_, Xi__, FXi, FXi_, FXi__;
      float val;
      
      //Derivative Truncated Version
      cout<< endl<<"********************* Derivative Truncanted Version *********************"<<endl<<endl;
      cout << setw(10) << "Xi" << setw(10) << "Xi+1" << setw(10) << "FXi" << setw(10) << "FXi+1" << setw(10) << "h" << setw(10) << "F'" <<endl;
      h=0.125;
      for (int it=0; it<n; it++) {
        Xi_ = roundoff(Xi + (1*h),prec); 
        FXi = roundoff(f(Xi),prec);
        FXi_ = roundoff(f(Xi_),prec);

        val = roundoff((FXi_-FXi)/h, prec);
        cout << setw(10) << Xi << setw(10) << Xi_ << setw(10) << FXi << setw(10) << FXi_ << setw(10) << h << setw(10) << val <<endl;
        truncF.push_back(val);
        h = h/2;
      }

      //More Accurate Version
      cout<< endl<<"********************* More Accurate Version *********************"<<endl<<endl;
      cout << setw(10) << "Xi" << setw(10) << "Xi+1" << setw(10) << "Xi+2" << setw(10) << "FXi" << setw(10) << "FXi+1" << setw(10) << "FXi+2" << setw(10) << "h" << setw(10) << "F'" <<endl;
      h=0.125;
      for (int it=0; it<n; it++) {
        Xi_ = roundoff(Xi + (1*h),prec); 
        Xi__ = roundoff(Xi + (2*h),prec);
        FXi = roundoff(f(Xi),prec);
        FXi_ = roundoff(f(Xi_),prec);
        FXi__ = roundoff(f(Xi__),prec);

        val = roundoff((-FXi__+(4*FXi_)-(3*FXi))/(2*h),prec);
        cout << setw(10) << Xi << setw(10) << Xi_ << setw(10) << Xi__ << setw(10) << FXi << setw(10) << FXi_ << setw(10) << FXi__ << setw(10) << h << setw(10) << val <<endl;
        accF.push_back(val);
        h = h/2;
      }

      cout<< endl<<"***************************************************************"<<endl<<endl;
      cout << setw(10) << "Truncated" << "\t" << setw(10) << "Accurate" << "\tRichardson's Interpolation" <<endl;
      for (int it=0; it<n; it++) {
        float X0;
        if (it==(n-1)) {   //last iteration
          X0 = roundoff(0, prec);
        } else {
          X0 = roundoff(((4*truncF[it+1])/3)-(truncF[it]/3),prec);
        }

        cout << setw(10) << truncF[it] << "\t" << setw(10) << accF[it] << "\t" << X0 << endl;
      }

      cout<<endl;
      return 0;
}