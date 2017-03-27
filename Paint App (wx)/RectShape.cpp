//
//  RectShape.cpp
//  paint-mac
//
//  Created by Krish on 2/21/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "RectShape.hpp"

RectShape::RectShape(const wxPoint& start):Shape(start)
{
 // parent's constructor
    
}

RectShape::~RectShape()
{
    //
}

void RectShape::Draw(wxDC &dc) const
{
    dc.SetPen(mPen);
    dc.SetBrush(mBrush);
    dc.DrawRectangle(wxRect(mOffset + mTopLeft, mOffset + mBotRight));
}
void RectShape::Finalize()
{
    //
}

