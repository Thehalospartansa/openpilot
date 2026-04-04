#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_6097178045969778433);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8027253490896525492);
void car_H_mod_fun(double *state, double *out_2448319121674464114);
void car_f_fun(double *state, double dt, double *out_1967878612429161037);
void car_F_fun(double *state, double dt, double *out_6453372126869218354);
void car_h_25(double *state, double *unused, double *out_2045742138170453634);
void car_H_25(double *state, double *unused, double *out_5971299771663955791);
void car_h_24(double *state, double *unused, double *out_5287849605296050304);
void car_H_24(double *state, double *unused, double *out_1224790444697446757);
void car_h_30(double *state, double *unused, double *out_8519729284785048797);
void car_H_30(double *state, double *unused, double *out_5558753960553979070);
void car_h_26(double *state, double *unused, double *out_7576219431883386362);
void car_H_26(double *state, double *unused, double *out_2229796452789899567);
void car_h_27(double *state, double *unused, double *out_7047415405831299279);
void car_H_27(double *state, double *unused, double *out_7733517272354403981);
void car_h_29(double *state, double *unused, double *out_7322609468115805168);
void car_H_29(double *state, double *unused, double *out_5048522616239586886);
void car_h_28(double *state, double *unused, double *out_6173421452042927390);
void car_H_28(double *state, double *unused, double *out_3917465057416066028);
void car_h_31(double *state, double *unused, double *out_1591707390083568716);
void car_H_31(double *state, double *unused, double *out_6001945733540916219);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}