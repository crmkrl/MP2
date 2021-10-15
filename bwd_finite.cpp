#include<iostream>
#include<math.h>
#include<iomanip>
#include<stdlib.h>
#include<vector>
#include <numeric>
#include <algorithm>

using namespace std;

#define f(x) (1/sqrt(M_PI*2))*exp(-0.5*pow(x,2))

float roundoff(float value, unsigned char prec)
{
  float pow_10 = pow(10.0f, (float)prec);
  return round(value * pow_10) / pow_10;
}

int main()
{
    float Xi;
    int prec, n;

    cout<<"Enter precision: ";
    cin>>prec;
    // cout<< setprecision(prec)<< fixed;

    cout << "Enter X: ";
    cin >> Xi;
    cout << "Enter number of data: ";
    cin >> n;

    float h[n];
    cout << "Enter h data: " << endl;
    for(int i = 0; i < n; i++) {
      cout << "h[" << i << "] = ";
      cin >>h[i];
    }

    cout<< endl<<"*********************"<< endl;
    cout<<"BACKWARD DIFFERENCE TABLE"<< endl;
    cout<<"*********************"<< endl;
    std::vector<float> truncF;
    std::vector<float> accF;
    float _Xi, __Xi, FXi, _FXi, __FXi;
    float val;

    //Derivative Truncated Version
    cout<< endl<<"********************* Derivative Truncanted Version *********************"<<endl<<endl;
    cout << setw(10) << "Xi" << setw(10) << "Xi-1" << setw(10) << "FXi" << setw(10) << "FXi-1" << setw(10) << "h" << setw(10) << "F'" <<endl;
    for (int it=0; it<n; it++) {
      _Xi = roundoff(Xi - (1*h[it]),prec); 
      FXi = roundoff(f(Xi),prec);
      _FXi = roundoff(f(_Xi),prec);

      val = roundoff((FXi-_FXi)/h[it],prec);
      cout << setw(10) << Xi << setw(10) << _Xi << setw(10) << FXi << setw(10) << _FXi << setw(10) << h[it] << setw(10) << val <<endl;
      truncF.push_back(val);
    }

    cout<< endl<<"********************* More Accurate Version *********************"<<endl<<endl;
    cout << setw(10) << "Xi" << setw(10) << "Xi-1" << setw(10) << "Xi-2" << setw(10) << "FXi" << setw(10) << "FXi-1" << setw(10) << "FXi-2" << setw(10) << "h" << setw(10) << "F'" <<endl;
    for (int it=0; it<n; it++) {
      _Xi = roundoff(Xi - (1*h[it]),prec); 
      __Xi = roundoff(Xi - (2*h[it]),prec);
      FXi = roundoff(f(Xi),prec);
      _FXi = roundoff(f(_Xi),prec);
      __FXi = roundoff(f(__Xi),prec);

      val = roundoff(((3*FXi)-(4*_FXi)+__FXi)/(2*h[it]),prec);
      cout << setw(10) << Xi << setw(10) << _Xi << setw(10) << __Xi << setw(10) << FXi << setw(10) << _FXi << setw(10) << __FXi << setw(10) << h[it] << setw(10) << val <<endl;
      accF.push_back(val);
    }

    cout<< endl<<"***************************************************************"<<endl<<endl;
    cout << setw(10) << "Truncated" << "\t" << "\tRichardson's Interpolation" << endl<<endl;
    std::vector<float> richardsons;
    for (int it=0; it<n; it++) {
        float X0;
        if (it==(n-1)) {   //last iteration
          X0 = roundoff(((4*richardsons[it-1])/3)-(richardsons[it-2]/3),prec);
          richardsons.push_back(X0);
        } else {
          X0 = roundoff(((4*truncF[it+1])/3)-(truncF[it]/3),prec);
          richardsons.push_back(X0);
        }

        cout << setw(10) << truncF[it] << setw(10) << "\t" << richardsons[it] << endl;
    }
 return 0;
}