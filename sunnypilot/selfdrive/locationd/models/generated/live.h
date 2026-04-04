#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void live_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_9(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_12(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_35(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_32(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_33(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_H(double *in_vec, double *out_3539274906800403715);
void live_err_fun(double *nom_x, double *delta_x, double *out_2993397994093672511);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_6614972468445730595);
void live_H_mod_fun(double *state, double *out_614062097395160592);
void live_f_fun(double *state, double dt, double *out_2408887140973051885);
void live_F_fun(double *state, double dt, double *out_1509425091423108686);
void live_h_4(double *state, double *unused, double *out_7126672468929614472);
void live_H_4(double *state, double *unused, double *out_779299795802848775);
void live_h_9(double *state, double *unused, double *out_8631842072273718025);
void live_H_9(double *state, double *unused, double *out_6507919139461598695);
void live_h_10(double *state, double *unused, double *out_6536284867551505883);
void live_H_10(double *state, double *unused, double *out_2022835333472696007);
void live_h_12(double *state, double *unused, double *out_6172871616172180315);
void live_H_12(double *state, double *unused, double *out_7160558172845581771);
void live_h_35(double *state, double *unused, double *out_2351358577156121422);
void live_H_35(double *state, double *unused, double *out_2587362261569758601);
void live_h_32(double *state, double *unused, double *out_663802385778089559);
void live_H_32(double *state, double *unused, double *out_942522751858858999);
void live_h_13(double *state, double *unused, double *out_165771986195742117);
void live_H_13(double *state, double *unused, double *out_2010344156717437123);
void live_h_14(double *state, double *unused, double *out_8631842072273718025);
void live_H_14(double *state, double *unused, double *out_6507919139461598695);
void live_h_33(double *state, double *unused, double *out_157662992357107482);
void live_H_33(double *state, double *unused, double *out_5662795518866078586);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}