#pragma once
#include <memory>
#include <vector>
#include "Shape.h"
#include "Command.h"
#include <wx/bitmap.h>
#include <wx/pen.h>
#include <wx/brush.h>
#include <stack>

class PaintModel : public std::enable_shared_from_this<PaintModel>
{
public:
	PaintModel();
	
	// Draws any shapes in the model to the provided DC (draw context)
	void DrawShapes(wxDC& dc, bool showSelection = true);

	// Clear the current paint model and start fresh
	void New();

	// Add a shape to the paint model
	void AddShape(std::shared_ptr<Shape> shape);
	// Remove a shape from the paint model
	void RemoveShape(std::shared_ptr<Shape> shape);
    
    bool HasActiveCommand();
    
    void CreateCommand(CommandType comType, wxPoint const start);
    
    void UpdateCommand(wxPoint const point);
    
    void FinalizeCommand();
    
    bool CanUndo() const;
    bool CanRedo() const;
    
    void Undo();
    
    void Redo();
    
    wxPen getPen();
    wxBrush getBrush();
    
    void setPen(wxPen pen);
    
    void setBrush(wxBrush brush);
    
    void setPenColor(wxColour color);
    
    void setBrushColor(wxColour color);

    void setPenWidth(int width);
    
    void selectShape(wxPoint point);
    
    std::shared_ptr<Shape> getSelectedShape();
    
    void Unselect();
    
    void DeleteSelectedShape(std::shared_ptr<Command> command);
    
    void Export(std::string name, wxSize size);
    
    void Import(std::string filepath);
    
    
    
    
private:
	// Vector of all the shapes in the model
	std::vector<std::shared_ptr<Shape>> mShapes;
    // save current active command
    std::shared_ptr<Command> mCommand;

    std::stack<std::shared_ptr<Command>> undoStack;
    std::stack<std::shared_ptr<Command>> redoStack;
    
    wxPen mPen = *wxBLACK_PEN;
    wxBrush mBrush = *wxWHITE_BRUSH;
    
    std::shared_ptr<Shape> selectedShape;
    
    std::shared_ptr<Shape> deletedShape;
    
    //part 4 stuff
    
    wxBitmap bitmap; // bitmap somehow always stays on top....

};
