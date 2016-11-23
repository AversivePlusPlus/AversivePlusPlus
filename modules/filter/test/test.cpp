#include <filter/quadramp.hpp>
#include <filter/derivate.hpp>
#include <filter/integral.hpp>
#include <filter/proportional.hpp>
#include <filter/shift.hpp>
#include <filter/chain.hpp>
#include <filter/parallel.hpp>
#include <filter/pid.hpp>
#include <filter/average.hpp>
#include <filter/limiter.hpp>
#include <filter/difference.hpp>

#include <base/integer.hpp>

#include <cassert>
#include <iostream>
#include <cmath>
using namespace std;

using namespace Filter;

int main(int, char**) {

  {
    Proportional<s32> P(3);
    assert(P(5) == 15);
  }

  {
    Shift<s32, u8> S(1);
    assert(S(222) == 222/2);
  }

  {
    Integral<s32> I(0);
    assert(I(5) == 5);
    assert(I(5) == 10);
  }

  {
    Derivate<s32> D(0);
    assert(D(5) == 5);
    assert(D(5) == 0);
  }

  {
    Pid<s32> PID(0,1,1,1,18);
    assert(PID(5) == 15);
    assert(PID(5) == 15);
    assert(PID(5) == 20);
    assert(PID(5) == 23);
 }

  {
    Average<s32, 5> M(5);
    assert(M(5) == 5);

    M(1);
    M(2);
    M(3);
    M(4);
    assert(M(5) == 3);
  }

  {
    Limiter<s32> S(0, 5);
    assert(S(-2) == 0);
    assert(S(2) == 2);
    assert(S(12) == 5);
  }

  {
    Difference<s32> DIFF(100);
    assert(DIFF(0) == 100);
    assert(DIFF(100) == 0);
    assert(DIFF(101) == -1);
  }

  {
//    double amin = -1;
//    double amax = 1;
//    double sneg = -200;
//    double spos = 20;

//    Integral<double> Ispe(0);
//    Integral<double> Ipos(0);

//    Derivate<double> Dacc(0);
//    Derivate<double> Dspe(0);

//    Difference<double> DIFF(-2000.28);
//    int first_seg = 80;

//    double pos = 0;
//    auto func_speed_cmd = [](double dpos, double smax, double amin) {
//        // Quadramp function
//        cout << "dbg " << _min(_sqrt(amin*dpos*2)-_min(amin, (amin)*dpos)/2, smax) << endl;
//        return _min(_sqrt(amin*dpos*2)-_min(amin, (amin)*dpos)/2, smax);
//      };

//    auto func_speed_err = [](double spe, double cur_spe, double amax, double amin) {
//        // If not fast enough
//        if(cur_spe < spe) {
//            return _min(amax, spe-cur_spe);
//          }
//        // Too fast !
//        else if(cur_spe > spe) {
//            return _max(-amin, spe-cur_spe);
//          }
//        return 0.;
//      };

//    auto func_quadramp = [&pos, &Dspe, &Dacc, &DIFF, func_speed_cmd, func_speed_err, &Ispe, &Ipos](int i, double spos, double sneg, double amax, double amin){
//        double spe = 0;
//        double cur_spe = Dspe(pos);

//        // Below setpoint
//        if(DIFF(pos) > 0) {
//            spe = func_speed_cmd(DIFF(pos), spos, -amin);
//            spe = Ispe(func_speed_err(spe, cur_spe, amax, -amin));
//          }
//        // Over setpoint
//        else if(DIFF(pos) < 0) {
//            spe = -func_speed_cmd(-DIFF(pos), -sneg, -amin);
//            spe = Ispe(-func_speed_err(-spe, -cur_spe, -amin, amax));
//          }
//        // At setpoint
//        else {
//            Ispe.reset();
//          }

//        // If near setpoint
//        if((amin < DIFF(pos) && DIFF(pos) < -amin) ||
//           (-_abs(spe) < DIFF(pos) && DIFF(pos) < _abs(spe))) {
//            spe = DIFF(pos);
//            pos = Ipos(spe);
//          }
//        // Normal speed integration
//        else {
//            pos = Ipos(spe);
//          }

//        cout << i << " ";
//        cout << pos << " ";
//        cout << cur_spe << " ";
//        cout << Dacc(cur_spe) << " ";
//        cout << endl;
//      };

    Quadramp<double> qramp(0, 100, -100, 10, -2);
    int first_seg = 80;

    for(int i = 0 ; i < first_seg ; i++) {
        //func_quadramp(i, spos, sneg, amax, amin);
        cout << i << " ";
        cout << qramp(-500) << " ";
        cout << endl;
      }

    //DIFF.setRefference(1000);

    for(int i = 0 ; i < 150 ; i++) {
        //func_quadramp(i+first_seg, spos, sneg, amax, amin);
        cout << i+first_seg << " ";
        cout << qramp(500) << " ";
        cout << endl;
      }
  }

  return 0;
}
