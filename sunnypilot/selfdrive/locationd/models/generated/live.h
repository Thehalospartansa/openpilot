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
void live_H(double *in_vec, double *out_1838674665775953266);
void live_err_fun(double *nom_x, double *delta_x, double *out_6627935093837848526);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_6864097058825384982);
void live_H_mod_fun(double *state, double *out_4320077104922375859);
void live_f_fun(double *state, double dt, double *out_3386152483493284183);
void live_F_fun(double *state, double dt, double *out_4342735657464255216);
void live_h_4(double *state, double *unused, double *out_7721896207677476123);
void live_H_4(double *state, double *unused, double *out_3316443200232436488);
void live_h_9(double *state, double *unused, double *out_4114041915692712962);
void live_H_9(double *state, double *unused, double *out_3557632846862027133);
void live_h_10(double *state, double *unused, double *out_1878628533529168076);
void live_H_10(double *state, double *unused, double *out_6051742026439162701);
void live_h_12(double *state, double *unused, double *out_3758310612140842864);
void live_H_12(double *state, double *unused, double *out_8335899608264398283);
void live_h_35(double *state, double *unused, double *out_3036158860662487068);
void live_H_35(double *state, double *unused, double *out_6683105257605043864);
void live_h_32(double *state, double *unused, double *out_4238516787009440682);
void live_H_32(double *state, double *unused, double *out_9058614303202757815);
void live_h_13(double *state, double *unused, double *out_4749149853615408951);
void live_H_13(double *state, double *unused, double *out_3344329817871085221);
void live_h_14(double *state, double *unused, double *out_4114041915692712962);
void live_H_14(double *state, double *unused, double *out_3557632846862027133);
void live_h_33(double *state, double *unused, double *out_6273598704045784156);
void live_H_33(double *state, double *unused, double *out_8613081811465650148);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}