//
//  DeleteCommand.hpp
//  paint-mac
//
//  Created by Krish on 2/23/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef DeleteCommand_hpp
#define DeleteCommand_hpp

#include <stdio.h>
#include "Command.h"
#include "PaintModel.h"
#include "Shape.h"

class DeleteCommand : public Command
{
public:
    DeleteCommand(const wxPoint& start, std::shared_ptr<Shape> shape);
    
    ~DeleteCommand();
    
    virtual void Finalize(std::shared_ptr<PaintModel> model) override;
    
    virtual void Undo(std::shared_ptr<PaintModel> model) override;
    
    virtual void Redo(std::shared_ptr<PaintModel> model) override;
    
    virtual void Update(const wxPoint& newPoint) override;
};
#endif /* DeleteCommand_hpp */
