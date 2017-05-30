/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   define.h
 * Author: lucas
 *
 * Created on May 27, 2017, 11:26 AM
 */

#ifndef DEFINE_H
#define DEFINE_H

#define SCREEN_W (1000)
#define SCREEN_H (527)

#define ESPACIO_LAT (70)
#define ESPACIO_INT (20)
#define LARGO_X (90)
#define LARGO_Y (90)
#define SQUARE_X(counter) (ESPACIO_LAT+(counter * ESPACIO_INT) + (counter * LARGO_X ))

#define ESPACIO_LAT_RECT (58)
#define ESPACIO_INT_RECT (58)
#define LARGO_RECT_X (256)
#define LARGO_RECT_Y (77)
#define RECTANGLE_X(counter) (ESPACIO_LAT_RECT + (counter * ESPACIO_INT_RECT) + (counter *LARGO_RECT_X))








#endif /* DEFINE_H */

