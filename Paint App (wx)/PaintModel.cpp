#include "PaintModel.h"
#include <algorithm>
#include <wx/dcmemory.h>

PaintModel::PaintModel()
{
}

// Draws any shapes in the model to the provided DC (draw context)
void PaintModel::DrawShapes(wxDC& dc, bool showSelection)
{
	// TODO
    
    for (int i = 0; i < mShapes.size(); ++i)
    {
        mShapes[i]->Draw(dc);
    }
    
    if(selectedShape != NULL) selectedShape->DrawSelection(dc);

    if (bitmap.IsOk())
    {
        dc.DrawBitmap(bitmap, 10, 10);
    }
    else{
        // no bitmap no problem
    }
    
    
}

// Clear the current paint model and start fresh
void PaintModel::New()
{
    selectedShape = NULL;
    mShapes.clear();
    mCommand.reset();
    
    while (!undoStack.empty()){ undoStack.pop();}
    while (!redoStack.empty()){ redoStack.pop();}
    
    mPen = *wxBLACK_PEN;
    mBrush = *wxWHITE_BRUSH;
    
    
    
    
    
    
    
}

// Add a shape to the paint model
void PaintModel::AddShape(std::shared_ptr<Shape> shape)
{
	mShapes.emplace_back(shape);
}

// Remove a shape from the paint model
void PaintModel::RemoveShape(std::shared_ptr<Shape> shape)
{
    
    if(selectedShape!= NULL) deletedShape = shape;
	auto iter = std::find(mShapes.begin(), mShapes.end(), shape);
	if (iter != mShapes.end())
	{
		mShapes.erase(iter);
	}
}

bool PaintModel::HasActiveCommand()
{
    if(mCommand.use_count() != 0) return true;
    return false;
}

void PaintModel::CreateCommand(CommandType comType, const wxPoint start)
{
    
    mCommand = CommandFactory::Create(this->shared_from_this(), comType, start);
    
    while(!redoStack.empty()) redoStack.pop();

    
}

void PaintModel::UpdateCommand(const wxPoint point)
{
    mCommand->Update(point);
}

void PaintModel::FinalizeCommand()
{
    //mCommand->Finalize(this->shared_from_this());
    undoStack.push(mCommand);
    mCommand.reset();
}

bool PaintModel::CanUndo() const
{
    return (!undoStack.empty());
}

bool PaintModel::CanRedo() const
{
    return (!redoStack.empty());
}

void PaintModel::Undo()
{
    if(CanUndo())
    {
        redoStack.push(undoStack.top());
        undoStack.top()->Undo(this->shared_from_this());
        undoStack.pop();
    }
    
    
}

void PaintModel::Redo()
{
    if(CanRedo())
    {
        undoStack.push(redoStack.top());
        
        redoStack.top()->Redo(this->shared_from_this());
        redoStack.pop();
    }
    
}

wxPen PaintModel::getPen()
{
    return mPen;
    
}

wxBrush PaintModel::getBrush()
{
    return mBrush;
}


void PaintModel::setPen(wxPen pen)
{
    mPen = pen;
}
void PaintModel::setBrush(wxBrush brush)
{
    //
    mBrush = brush;
}


void PaintModel::setPenColor(wxColour color)
{
   
    mPen.SetColour(color);
}

void PaintModel::setBrushColor(wxColour color)
{
    mBrush.SetColour(color);
}


void PaintModel::setPenWidth(int width)
{
    mPen.SetWidth(width);
}

void PaintModel::selectShape(wxPoint point)
{
    // reverse for loop, checks newest elements first (top layer)
    for(int i = (int)(mShapes.size() - 1); i >= 0; --i)
    {
     if(mShapes[i]->checkIntersect(point)) // if it intersects
     {
         selectedShape = mShapes[i];
         return;
     }
    }
    
    selectedShape = NULL;
}
std::shared_ptr<Shape> PaintModel::getSelectedShape()
{
    return selectedShape;
}


void PaintModel::Unselect()
{
    selectedShape = NULL;
}

void PaintModel::DeleteSelectedShape(std::shared_ptr<Command> command)
{
    undoStack.push(command);
    deletedShape = selectedShape;
    selectedShape = NULL;
    
    
}

void PaintModel::Export(std::string name, wxSize size)
{
    bitmap.Create(size);
    
    wxMemoryDC dc(bitmap);
    
    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();
    
    DrawShapes(dc);
    
    wxBitmapType type = wxBITMAP_TYPE_PNG;
    
    std::string png = ".png";
    std::string bmp = ".bmp";
    std::string jpeg = ".jpeg";
    std::size_t found = name.find(png);
    if(found != std::string::npos) type = wxBITMAP_TYPE_PNG;
    if(name.find(bmp) != std::string::npos) type = wxBITMAP_TYPE_BMP;
    if(name.find(jpeg) != std::string::npos) type = wxBITMAP_TYPE_JPEG;
    
    
    
    bitmap.SaveFile(name, type);
    
}

void PaintModel::Import(std::string filepath)
{
    New(); // clear old bitmap
    
    wxBitmapType type = wxBITMAP_TYPE_PNG;
    
    std::string png = ".png";
    std::string bmp = ".bmp";
    std::string jpeg = ".jpeg";
    std::string jpg = ".jpeg";
    std::size_t found = filepath.find(png);
    if(found != std::string::npos) type = wxBITMAP_TYPE_PNG;
    if(filepath.find(bmp) != std::string::npos) type = wxBITMAP_TYPE_BMP;
    if(filepath.find(jpeg) != std::string::npos) type = wxBITMAP_TYPE_JPEG;
    if(filepath.find(jpg) != std::string::npos) type = wxBITMAP_TYPE_JPEG;
    
    bitmap.LoadFile(filepath, type);
    
    
    
}







