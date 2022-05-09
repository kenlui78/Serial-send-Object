#pragma once
class Point {
public:
    Point(int X = 0, int Y = 0);
    int x, y;
};
class RemoteButton {
public:
    RemoteButton();
    Point leftStick, rightStick;
    bool l1, l3, r1, r3, triangle, circle, cross, square, up, left, down, right, share, option;
    int l2, r2;
};