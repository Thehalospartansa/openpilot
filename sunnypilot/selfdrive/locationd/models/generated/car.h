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
void car_err_fun(double *nom_x, double *delta_x, double *out_5960298151612549262);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3713988653844672293);
void car_H_mod_fun(double *state, double *out_3260348241577175577);
void car_f_fun(double *state, double dt, double *out_4734299198424188856);
void car_F_fun(double *state, double dt, double *out_5631824782310061315);
void car_h_25(double *state, double *unused, double *out_4076735487506752080);
void car_H_25(double *state, double *unused, double *out_1643343583607489263);
void car_h_24(double *state, double *unused, double *out_7512610211448591818);
void car_H_24(double *state, double *unused, double *out_4557689096243672163);
void car_h_30(double *state, double *unused, double *out_6606743329382127095);
void car_H_30(double *state, double *unused, double *out_2884352746520118935);
void car_h_26(double *state, double *unused, double *out_2858031572320583756);
void car_H_26(double *state, double *unused, double *out_2098159735266566961);
void car_h_27(double *state, double *unused, double *out_924937780154093565);
void car_H_27(double *state, double *unused, double *out_660758675336175718);
void car_h_29(double *state, double *unused, double *out_6838327476666578876);
void car_H_29(double *state, double *unused, double *out_2374121402205726751);
void car_h_28(double *state, double *unused, double *out_2111848271290239120);
void car_H_28(double *state, double *unused, double *out_410491130640400500);
void car_h_31(double *state, double *unused, double *out_3383823276742136245);
void car_H_31(double *state, double *unused, double *out_2724367837499918437);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}