//
//  SetPenCommand.hpp
//  paint-mac
//
//  Created by Krish on 2/23/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef SetPenCommand_hpp
#define SetPenCommand_hpp

#include <stdio.h>
#include "Command.h"
#include "PaintModel.h"

class SetPenCommand : public Command
{
    
public:
    SetPenCommand(const wxPoint& start, std::shared_ptr<Shape> shape);
    
    ~SetPenCommand();
    
    virtual void Finalize(std::shared_ptr<PaintModel> model) override;
    
    virtual void Undo(std::shared_ptr<PaintModel> model) override;
    
    virtual void Redo(std::shared_ptr<PaintModel> model) override;
    
    virtual void Update(const wxPoint& newPoint) override;
    
    
private:
    
    wxPen mNewPen;
    wxPen mOldPen;
    
    //
    wxColour mOldColor;
    wxColour mNewColor;
};


#endif /* SetPenCommand_hpp */
