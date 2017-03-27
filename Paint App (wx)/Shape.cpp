#include "Shape.h"

Shape::Shape(const wxPoint& start)
	:mStartPoint(start)
	,mEndPoint(start)
	,mTopLeft(start)
	,mBotRight(start)
{
    mOffset.x = 0;
    mOffset.y = 0;
}

// Tests whether the provided point intersects
// with this shape
bool Shape::Intersects(const wxPoint& point) const
{
	wxPoint topleft;
	wxPoint botright;
	GetBounds(topleft, botright);
	if (point.x >= topleft.x && point.x <= botright.x &&
		point.y >= topleft.y && point.y <= botright.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Update shape with new provided point
void Shape::Update(const wxPoint& newPoint)
{
	mEndPoint = newPoint;

	// For most shapes, we only have two points - start and end
	// So we can figure out the top left/bottom right bounds
	// based on this.
	mTopLeft.x = std::min(mStartPoint.x, mEndPoint.x);
	mTopLeft.y = std::min(mStartPoint.y, mEndPoint.y);
	mBotRight.x = std::max(mStartPoint.x, mEndPoint.x);
	mBotRight.y = std::max(mStartPoint.y, mEndPoint.y);
}

void Shape::Finalize()
{
	// Default finalize doesn't do anything
}

void Shape::GetBounds(wxPoint& topLeft, wxPoint& botRight) const
{
	topLeft = mTopLeft + mOffset;
	botRight = mBotRight + mOffset;
}

void Shape::setBrush(wxBrush brush)
{
    mBrush = brush;
}

void Shape::setPen(wxPen pen)
{
    mPen = pen;
}

wxPen Shape::getPen()
{
    return mPen;
}

wxBrush Shape::getBrush()
{
    return mBrush;
}

void Shape::DrawSelection(wxDC& dc)
{
    dc.SetPen(*wxBLACK_DASHED_PEN);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    
    wxPoint TopLeftMargin;
    wxPoint BotRightMargin;
    
    TopLeftMargin.x = mTopLeft.x - margin + mOffset.x;
    TopLeftMargin.y = mTopLeft.y - margin + mOffset.y;
    
    BotRightMargin.x = mBotRight.x + margin + mOffset.x;
    BotRightMargin.y = mBotRight.y + margin + mOffset.y;
    
    
    
    dc.DrawRectangle(wxRect(TopLeftMargin , BotRightMargin));
}

int Shape::getMargin()
{
    return margin;
}
bool Shape::checkIntersect(const wxPoint &point)
{
    // checks if the shape intersects that point at all (excluding margins)
    
    if (point.x >= mTopLeft.x && point.x <= mBotRight.x)
    {
        if(point.y >= mTopLeft.y && point.y <= mBotRight.y)
        {
            return true;
        }
    }
    return false;
}

void Shape::setPenColor(wxColour color)
{
    mPen.SetColour(color);
}

void Shape::setBrushColor(wxColour color)
{
    mBrush.SetColour(color);
}

wxPoint Shape::getStart()
{
    return mStartPoint;
}

void Shape::setOffset(wxPoint point)
{
    mOffset = point;
}

wxPoint Shape::getOffset()
{
    return mOffset;
}
