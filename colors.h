#ifndef COLORS_H
#define COLORS_H

#include <QColor>

struct nc_color {
    QColor fg;
    QColor bg;

    nc_color()
    {
        fg = QColor(Qt::black);
        bg = QColor(Qt::black);
    }

    nc_color(QColor f, QColor b)
    {
        fg = f;
        bg = b;
    }
};

static nc_color color_from_string(QString);
static nc_color bgcolor_from_string(QString);

const nc_color c_white(QColor(Qt::white), QColor(Qt::black));
const nc_color c_black(QColor(Qt::black), QColor(Qt::black));
const nc_color c_brown(QColor(0xA5,0x2A,0x2A), QColor(Qt::black));
const nc_color c_yellow(QColor(Qt::yellow), QColor(Qt::black));
const nc_color c_green(QColor(Qt::green), QColor(Qt::black));
const nc_color c_ltred(QColor(0xFF, 0x63, 0x47), QColor(Qt::black));
const nc_color c_ltgray(QColor(Qt::lightGray), QColor(Qt::black));
const nc_color c_cyan(QColor(Qt::cyan), QColor(Qt::black));
const nc_color c_ltcyan(QColor(0xE0,0xFF,0xFF), QColor(Qt::black));
const nc_color c_dkgray(QColor(Qt::darkGray), QColor(Qt::black));
const nc_color c_ltgreen(QColor(0x90,0xEE,0x90), QColor(Qt::black));
const nc_color c_ltblue(QColor(0xAD,0xD8,0xE6), QColor(Qt::black));
const nc_color c_magenta(QColor(Qt::magenta), QColor(Qt::black));
const nc_color c_blue(QColor(Qt::blue), QColor(Qt::black));
const nc_color c_red(QColor(Qt::red), QColor(Qt::black));
const nc_color c_cyan_red(QColor(Qt::cyan), QColor(Qt::red));
const nc_color c_pink(QColor(0xf8, 0xb8, 0xd8), QColor(Qt::black));

const nc_color c_white_red(QColor(Qt::white), QColor(Qt::red));
const nc_color c_ltgray_red(QColor(Qt::lightGray), QColor(Qt::red));
const nc_color c_dkgray_red(QColor(Qt::black), QColor(Qt::red));
const nc_color c_red_red(QColor(Qt::black), QColor(Qt::red));
const nc_color c_green_red(QColor(Qt::green), QColor(Qt::red));
const nc_color c_blue_red(QColor(Qt::blue), QColor(Qt::red));
const nc_color c_magenta_red(QColor(Qt::magenta), QColor(Qt::red));
const nc_color c_brown_red(QColor(0xA5,0x2A,0x2A), QColor(Qt::red));
const nc_color c_ltred_red(QColor(0xFF, 0x63, 0x47), QColor(Qt::red));
const nc_color c_ltgreen_red(QColor(0x90,0xEE,0x90), QColor(Qt::red));
const nc_color c_ltblue_red(QColor(0xAD,0xD8,0xE6), QColor(Qt::red));
const nc_color c_ltcyan_red(QColor(0xE0,0xFF,0xFF), QColor(Qt::red));
const nc_color c_pink_red(QColor(0xf8, 0xb8, 0xd8), QColor(Qt::red));
const nc_color c_yellow_red(QColor(Qt::yellow), QColor(Qt::red));

const nc_color i_brown(QColor(Qt::black), QColor(0xA5,0x2A,0x2A));
const nc_color i_white(QColor(Qt::black), QColor(Qt::white));
const nc_color i_red(QColor(Qt::black), QColor(Qt::red));
const nc_color i_black(QColor(Qt::black), QColor(Qt::black));
const nc_color i_ltgray(QColor(Qt::black), QColor(Qt::lightGray));
const nc_color i_dkgray(QColor(Qt::black), QColor(Qt::darkGray));
const nc_color i_green(QColor(Qt::black), QColor(Qt::green));
const nc_color i_blue(QColor(Qt::black), QColor(Qt::blue));
const nc_color i_cyan(QColor(Qt::black), QColor(Qt::cyan));
const nc_color i_magenta(QColor(Qt::black), QColor(Qt::magenta));
const nc_color i_ltred(QColor(Qt::black), QColor(0xFF, 0x63, 0x47));
const nc_color i_ltblue(QColor(Qt::black), QColor(0xAD,0xD8,0xE6));
const nc_color i_pink(QColor(Qt::black), QColor(0xf8, 0xb8, 0xd8));
const nc_color i_yellow(QColor(Qt::black), QColor(Qt::yellow));
const nc_color i_ltcyan(QColor(Qt::black), QColor(0xE0,0xFF,0xFF));

nc_color color_from_string(QString new_color){
    if("red"==new_color){
        return c_red;
    } else if("blue"==new_color){
        return c_blue;
    } else if("green"==new_color){
        return c_green;
    } else if("light_cyan"==new_color || "ltcyan"==new_color){
        return c_ltcyan;
    } else if("brown"==new_color){
        return c_brown;
    } else if("light_red"==new_color || "ltred"==new_color){
        return c_ltred;
    } else if("white"==new_color){
        return c_white;
    } else if("black"==new_color){
        return c_black;
    } else if("light_blue"==new_color || "ltblue"==new_color){
        return c_ltblue;
    } else if("yellow"==new_color){
        return c_yellow;
    } else if("magenta"==new_color){
        return c_magenta;
    } else if("cyan"==new_color){
        return c_cyan;
    } else if("light_gray"==new_color || "ltgray"==new_color){
        return c_ltgray;
    } else if("dark_gray"==new_color || "dkgray"==new_color){
        return c_dkgray;
    } else if("light_green"==new_color || "ltgreen"==new_color){
        return c_ltgreen;
    } else if("pink"==new_color){
        return c_pink;
    } else if("white_red"==new_color){
        return c_white_red;//
    } else if("ltgray_red"==new_color || "light_gray_red"==new_color){
        return c_ltgray_red;//
    } else if("dkgray_red"==new_color || "dark_gray_red"==new_color){
        return c_dkgray_red;//
    } else if("red_red"==new_color){
        return c_red_red;//
    } else if("green_red"==new_color){
        return c_green_red;//
    } else if("blue_red"==new_color){
        return c_blue_red;//
    } else if("cyan_red"==new_color){
        return c_cyan_red;
    } else if("magenta_red"==new_color){
        return c_magenta_red;//
    } else if("brown_red"==new_color){
        return c_brown_red;//
    } else if("ltred_red"==new_color || "light_red_red"==new_color){
        return c_ltred_red;//
    } else if("ltgreen_red"==new_color || "light_green_red"==new_color){
        return c_ltgreen_red;
    } else if("ltblue_red"==new_color || "light_blue_red"==new_color){
        return c_ltblue_red;//
    } else if("ltcyan_red"==new_color || "light_cyan_red"==new_color){
        return c_ltcyan_red;//
    } else if("pink_red"==new_color){
        return c_pink_red;//
    } else if("yellow_red"==new_color){
        return c_yellow_red;//
    } else {
        return c_white;
    }
}

nc_color bgcolor_from_string(QString new_color) {
  if("black" == new_color) {
    return i_black;
  } else if("white" == new_color) {
    return i_white;
  } else if("light_gray" == new_color || "ltgray" == new_color) {
    return i_ltgray;
  } else if("dark_gray" == new_color || "dkgray" == new_color) {
    return i_dkgray;
  } else if("red" == new_color) {
    return i_red;
  } else if("green" == new_color) {
    return i_green;
  } else if("blue" == new_color) {
    return i_blue;
  } else if("cyan" == new_color) {
    return i_cyan;
  } else if("magenta" == new_color) {
    return i_magenta;
  } else if("brown" == new_color) {
    return i_brown;
  } else if("light_red" == new_color || "ltred" == new_color) {
    return i_ltred;
  } else if("light_blue" == new_color || "ltblue" == new_color) {
    return i_ltblue;
  } else if("light_cyan" == new_color || "ltcyan" == new_color) {
    return i_ltcyan;
  } else if("pink" == new_color) {
    return i_pink;
  } else if("yellow" == new_color) {
    return i_yellow;
  } else {
    return i_white;
  }
}

#endif // COLORS_H
