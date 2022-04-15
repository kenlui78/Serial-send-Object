#include "remoteButton.h"
Point::Point(int X, int Y) {
    x = X;
    y = Y;
}
RemoteButton::RemoteButton() : leftStick(0, 0), rightStick(0, 0) {
    l1 = false;
    l3 = false;
    r1 = false;
    r3 = false;
    triangle = false;
    circle = false;
    cross = false;
    square = false;
    up = false;
    left = false;
    down = false;
    right = false;
    share = false;
    option = false;
    l2 = 0;
    r2 = 0;
}