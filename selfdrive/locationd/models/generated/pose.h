#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2728703337659485106);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4933784707852487941);
void pose_H_mod_fun(double *state, double *out_4112937202201059041);
void pose_f_fun(double *state, double dt, double *out_41468171679069375);
void pose_F_fun(double *state, double dt, double *out_7128628514967391957);
void pose_h_4(double *state, double *unused, double *out_8965394066110212061);
void pose_H_4(double *state, double *unused, double *out_7405284191817771769);
void pose_h_10(double *state, double *unused, double *out_4429682976893391883);
void pose_H_10(double *state, double *unused, double *out_3580593939681347040);
void pose_h_13(double *state, double *unused, double *out_9139916048338221099);
void pose_H_13(double *state, double *unused, double *out_7207704418589255823);
void pose_h_14(double *state, double *unused, double *out_6372905199228253303);
void pose_H_14(double *state, double *unused, double *out_7958671449596407551);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}