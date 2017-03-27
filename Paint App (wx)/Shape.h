#pragma once
#include <wx/dc.h>
#include <wx/pen.h>
#include <wx/brush.h>


// Abstract base class for all Shapes
class Shape
{
public:
	Shape(const wxPoint& start);
	// Tests whether the provided point intersects
	// with this shape
	bool Intersects(const wxPoint& point) const;
	// Update shape with new provided point
	virtual void Update(const wxPoint& newPoint);
	// Finalize the shape -- when the user has finished drawing the shape
	virtual void Finalize();
	// Returns the top left/bottom right points of the shape
	void GetBounds(wxPoint& topLeft, wxPoint& botRight) const;
	// Draw the shape
	virtual void Draw(wxDC& dc) const = 0;
	virtual ~Shape() { }
    
    void setBrush(wxBrush brush);
    void setPen(wxPen pen);
    
    wxBrush getBrush();
    wxPen getPen();
    
    void setPenColor(wxColour color);
    void setBrushColor(wxColour color);
    
    void DrawSelection(wxDC& dc);
    int getMargin();
    
    bool checkIntersect(const wxPoint& point);
    
    wxPoint getStart();
    
    void setOffset(wxPoint point);
    
    wxPoint getOffset();

    
protected:
	// Starting point of shape
	wxPoint mStartPoint;
	// Ending point of shape
	wxPoint mEndPoint;
	// Top left point of shape
	wxPoint mTopLeft;
	// Bottom right point of shape
	wxPoint mBotRight;
    
    wxPen mPen;
    wxBrush mBrush;
    int margin = 10;
    
    wxPoint mOffset;

};
