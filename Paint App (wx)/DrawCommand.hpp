//
//  DrawCommand.hpp
//  paint-mac
//
//  Created by Krish on 2/20/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef DrawCommand_hpp
#define DrawCommand_hpp

#include "Command.h"
#include <stdio.h>
#include "Shape.h"
#include "PaintModel.h"

class DrawCommand : public Command
{
public:
    DrawCommand(const wxPoint& start, std::shared_ptr<Shape> shape);
    
    ~DrawCommand();
    
    virtual void Finalize(std::shared_ptr<PaintModel> model) override;
    
    virtual void Undo(std::shared_ptr<PaintModel> model) override;
    
    virtual void Redo(std::shared_ptr<PaintModel> model) override;
    
    virtual void Update(const wxPoint& newPoint) override;
    
private:
    
    
};

#endif /* DrawCommand_hpp */
