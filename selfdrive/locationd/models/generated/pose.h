#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_1813739608873815140);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8036368585793301884);
void pose_H_mod_fun(double *state, double *out_3792066886079858939);
void pose_f_fun(double *state, double dt, double *out_8697136999633362847);
void pose_F_fun(double *state, double dt, double *out_3871028545822381301);
void pose_h_4(double *state, double *unused, double *out_2936144003194801573);
void pose_H_4(double *state, double *unused, double *out_591656984978388915);
void pose_h_10(double *state, double *unused, double *out_1737615237719831993);
void pose_H_10(double *state, double *unused, double *out_4052938281048870893);
void pose_h_13(double *state, double *unused, double *out_4819018816793413092);
void pose_H_13(double *state, double *unused, double *out_8202288193295089844);
void pose_h_14(double *state, double *unused, double *out_5456552129190884631);
void pose_H_14(double *state, double *unused, double *out_2491131447316983381);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}