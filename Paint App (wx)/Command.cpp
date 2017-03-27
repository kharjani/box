#include "Command.h"
#include "Shape.h"
#include "PaintModel.h"
#include "RectShape.hpp"
#include "DrawCommand.hpp"
#include "EllipseShape.hpp"
#include "Line.hpp"
#include "PencilShape.hpp"
#include "SetBrushCommand.hpp"
#include "SetPenCommand.hpp"
#include "DeleteCommand.hpp"
#include "MoveCommand.hpp"


Command::Command(const wxPoint& start, std::shared_ptr<Shape> shape)
	:mStartPoint(start)
	,mEndPoint(start)
	,mShape(shape)
{

}

// Called when the command is still updating (such as in the process of drawing)
void Command::Update(const wxPoint& newPoint)
{
	mEndPoint = newPoint;
}

std::shared_ptr<Command> CommandFactory::Create(std::shared_ptr<PaintModel> model,
	CommandType type, const wxPoint& start)
{
	std::shared_ptr<Command> retVal;
	
	// TODO: Actually create a command based on the type passed in

    std::shared_ptr<Shape> shape;

    //std::shared_ptr<DrawCommand> drawCom;
    
    if(type == CM_DrawRect)
    {
        shape = std::make_shared<RectShape>(start);
        shape->setBrush(model->getBrush());
        shape->setPen(model->getPen());
        retVal = std::make_shared<DrawCommand>(start, shape);
        model->AddShape(shape);
        
        
    }
    else if (type == CM_DrawEllipse)
    {
        shape = std::make_shared<EllipseShape>(start);
        shape->setBrush(model->getBrush());
        shape->setPen(model->getPen());
        retVal = std::make_shared<DrawCommand>(start, shape);
        model->AddShape(shape);
    }
    else if(type == CM_DrawLine)
    {
        shape = std::make_shared<Line>(start);
        shape->setBrush(model->getBrush());
        shape->setPen(model->getPen());
        retVal = std::make_shared<DrawCommand>(start, shape);
        model->AddShape(shape);
    }
    else if(type == CM_DrawPencil)
    {
        shape = std::make_shared<PencilShape>(start);
        shape->setBrush(model->getBrush());
        shape->setPen(model->getPen());
        retVal = std::make_shared<DrawCommand>(start, shape);
        model->AddShape(shape);
    }
    else if (type == CM_SetBrush)
    {
        shape = model->getSelectedShape();
        retVal = std::make_shared<SetBrushCommand>(start, shape);
        retVal->Finalize(model);
    }
    else if (type == CM_SetPen)
    {
        shape = model->getSelectedShape();
        retVal = std::make_shared<SetPenCommand>(start, shape);
        // where does finalize get called on the command ??????
        retVal->Finalize(model);
    }
    else if(type == CM_Delete)
    {
        // need make sure something is actually selected
        
        shape = model->getSelectedShape();
        retVal = std::make_shared<DeleteCommand>(start, shape);
    }
    else if(type == CM_Move)
    {
        shape = model->getSelectedShape();
        retVal = std::make_shared<MoveCommand>(start, shape);
    }
    
    
    
    
    
    
	return retVal;
}
