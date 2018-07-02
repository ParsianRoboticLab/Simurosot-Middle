#ifndef _FIELD_HEADER
#define _FIELD_HEADER

#include "geom.h"


class Field {
public:
    Field();
    ~Field();
    static const double height = 180;
    static const double width = 220;
    static const double goalDepth = 15;
    static const double goalWidth = 40;
    static const double penaltyAheight = 50;
    static const double penaltyAwidth  = 15;
    static const double penaltyBheight = 80;
    static const double penaltyBwidth = 35;
    static const double penaltyPoint = 37.5;
    static const double penaltyCheight = 80;
    static const double penaltyCwidth = 120;
    static const double FBHeightOffSet = 30;
    static const double FBHWidthOffSet = 55;
    static const double markerFBOffSet = 25;
    static const double centerCircleRadius = 25;
    static const double cornerTriangleSide = 7;

    static rcsc::Vector2D FBLeftTop()  { return rcsc::Vector2D{-width/2 + FBHWidthOffSet, -height/2 + FBHeightOffSet};}
    static rcsc::Vector2D FBRightTop() { return rcsc::Vector2D{width/2 - FBHWidthOffSet, -height/2 + FBHeightOffSet};}
    static rcsc::Vector2D FBLeftBot()  { return rcsc::Vector2D{-width/2 + FBHWidthOffSet, height/2 - FBHeightOffSet};}
    static rcsc::Vector2D FBRightBot() { return rcsc::Vector2D{width/2 - FBHWidthOffSet, height/2 - FBHeightOffSet};}

    static rcsc::Vector2D cornerLeftTop()  { return rcsc::Vector2D{-width/2, -height/2};}
    static rcsc::Vector2D cornerLeftBot()  { return rcsc::Vector2D{-width/2, height/2};}
    static rcsc::Vector2D cornerRightTop() { return rcsc::Vector2D{width/2, -height/2};}
    static rcsc::Vector2D cornerRightBot() { return rcsc::Vector2D{width/2, height/2};}

    static rcsc::Vector2D ourGoal()  { return rcsc::Vector2D{-width/2,   0}; }
    static rcsc::Vector2D ourGoalT() { return rcsc::Vector2D{-width/2, -20}; }
    static rcsc::Vector2D ourGoalB() { return rcsc::Vector2D{-width/2,  20}; }
    static rcsc::Vector2D oppGoal()  { return rcsc::Vector2D{ width/2,   0}; }
    static rcsc::Vector2D oppGoalT() { return rcsc::Vector2D{ width/2, -20}; }
    static rcsc::Vector2D oppGoalB() { return rcsc::Vector2D{ width/2,  20}; }

    static rcsc::Vector2D ourPenalty() { return rcsc::Vector2D{ -width/2 + penaltyPoint, 0}; }
    static rcsc::Vector2D oppPenalty() { return rcsc::Vector2D{  width/2 + penaltyPoint, 0}; }

    static rcsc::Rect2D ourGoalRect()     { return rcsc::Rect2D{-width/2 - goalDepth, -goalWidth/2, goalDepth, goalWidth};}
    static rcsc::Rect2D ourPenaltyARect() { return rcsc::Rect2D{-width/2, -penaltyAheight/2, penaltyAwidth, penaltyAheight};}
    static rcsc::Rect2D ourPenaltyBRect() { return rcsc::Rect2D{-width/2, -penaltyBheight/2, penaltyBwidth, penaltyBheight};}
    static rcsc::Rect2D ourPenaltyCRect() { return rcsc::Rect2D{-width/2, -penaltyCheight/2, penaltyCwidth, penaltyCheight};}

    static rcsc::Rect2D oppGoalRect()     { return rcsc::Rect2D{width/2, -goalWidth/2, goalDepth, goalWidth};}
    static rcsc::Rect2D oppPenaltyARect() { return rcsc::Rect2D{width/2 - penaltyAwidth, -penaltyAheight/2, penaltyAwidth, penaltyAheight};}
    static rcsc::Rect2D oppPenaltyBRect() { return rcsc::Rect2D{width/2 - penaltyBwidth, -penaltyBheight/2, penaltyBwidth, penaltyBheight};}
    static rcsc::Rect2D oppPenaltyCRect() { return rcsc::Rect2D{width/2 - penaltyCwidth, -penaltyCheight/2, penaltyCwidth, penaltyCheight};}

    static rcsc::Rect2D fieldRect()   { return rcsc::Rect2D{-width/2, -height/2, width, height};}
    static rcsc::Rect2D ourHalfRect() { return rcsc::Rect2D{-width/2, -height/2, width/2, height};}
    static rcsc::Rect2D oppHalfRect() { return rcsc::Rect2D{0, -height/2, width/2, height};}

};

#endif // _FIELD_HEADER