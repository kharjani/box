//
//  PencilShape.cpp
//  paint-mac
//
//  Created by Krish on 2/22/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "PencilShape.hpp"

PencilShape::PencilShape(const wxPoint& start) : Shape(start)
{
    mPoints.push_back(start);
}

PencilShape::~PencilShape()
{
    
}

void PencilShape::Draw(wxDC &dc) const
{

    dc.SetPen(mPen);
    dc.SetBrush(mBrush);
    if(mPoints.size() == 1)
    {
        dc.DrawPoint(mPoints[0] + mOffset);
    }
    else
    {
        
        dc.DrawLines(static_cast<int>(mPoints.size()), mPoints.data(), mOffset.x, mOffset.y);
        
    }
    
}

void PencilShape::Update(const wxPoint &newPoint)
{
    Shape::Update(newPoint);
    mPoints.push_back(newPoint);
}

void PencilShape::Finalize()
{
    for(int i = 0; i < mPoints.size(); ++i)
    {
        if (mPoints[i].x < mTopLeft.x) {
            mTopLeft.x = mPoints[i].x + mOffset.x;
        }
        
        if (mPoints[i].y < mTopLeft.y) mTopLeft.y = mPoints[i].y + mOffset.y;
        
        if (mPoints[i].x > mBotRight.x) mBotRight.x = mPoints[i].x + mOffset.x;
        if (mPoints[i].y > mBotRight.y) mBotRight.y = mPoints[i].y + mOffset.y;
    }
}
