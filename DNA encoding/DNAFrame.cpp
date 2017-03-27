//
//  DNAFrame.cpp
//  DNAwx
//
//  Created by Sanjay Madhav on 12/27/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#include "DNAFrame.h"
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/filedlg.h>
#include <wx/busyinfo.h>
#include "DNADrawPanel.h"
#include "Exceptions.h"
#include "DNAAlignDlg.h"
#include "NW.hpp"
#include "Timer.h"

enum
{
	ID_AMINO_HIST=1000,
    ID_PAIRWISE=1001,
};

wxBEGIN_EVENT_TABLE(DNAFrame, wxFrame)
	EVT_MENU(wxID_EXIT, DNAFrame::OnExit)
	EVT_MENU(wxID_NEW, DNAFrame::OnNew)
	EVT_MENU(ID_AMINO_HIST, DNAFrame::OnAminoHist)
    EVT_MENU(ID_PAIRWISE, DNAFrame::OnPairwise)
wxEND_EVENT_TABLE()

DNAFrame::DNAFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	// File menu
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(wxID_NEW);
	menuFile->Append(ID_AMINO_HIST, "Amino Acid Histogram...",
					 "Create a histogram from a FASTA file.");
	menuFile->Append(wxID_EXIT);
	
    menuFile->Append(ID_PAIRWISE, "Pairwise Alignment...",
                     "Minimum edit distance of 2 DNA sequences");
    
	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	SetMenuBar(menuBar);
	CreateStatusBar();
	
	// Prepare the draw panel and show this frame
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	mPanel = new DNADrawPanel(this);
	sizer->Add(mPanel, 1, wxEXPAND);
	
	SetSizer(sizer);
	SetAutoLayout(true);
	Show(true);
	
	SetMinSize(GetSize());
	SetMaxSize(GetSize());
}

void DNAFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void DNAFrame::OnNew(wxCommandEvent& event)
{
	// Doesn't do anything...
}

void DNAFrame::OnAminoHist(wxCommandEvent& event)
{
	// TODO: Implement (File>Amino Acid Histogram...)
    try{
        wxFileDialog openFileDialog(this, _("Open FASTA File"), "./data", "", "*.FASTA", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
        
        if(openFileDialog.ShowModal() == wxID_OK)
        {
            FastaHandler handler = FastaHandler(openFileDialog.GetPath().ToStdString());
            
            std::string sequence = handler.GetSequence();
            std::string header = handler.GetHeader();
            
            Translator t = Translator(sequence);
            
            std::unordered_map<char, int> map = t.GetAminoMap();
            int total = t.GetTotalCount();
            mPanel->mAminoMap = map;
            mPanel->mHeader = header;
            mPanel->mTotalCount = total;
            mPanel->hasFile = true;
            mPanel->PaintNow();
            
            
        }
        
        

    }catch(FileLoadExcept e)
    {
        //wx message box stuff - bad file
        wxMessageBox("FASTA file is invalid (load error)", "Error", wxOK | wxICON_ERROR);
    }catch(FileReadExcept e)
    {
        // wxmessagebox cant invalid file contents
        wxMessageBox("FASTA file is invalid (read error)", "Error", wxOK | wxICON_ERROR);
    }
}

void DNAFrame::OnPairwise(wxCommandEvent &event)
{
    DNAAlignDlg dialog;
    if(dialog.ShowModal() == wxID_OK)
    {
       // wxBusyInfo info("Calculating pairwise match...", this);
        std::string pathA = dialog.GetInputAPath();
        std::string pathB = dialog.GetInputBPath();
        std::string output = dialog.GetOutputPath();
        
        Timer t;
        t.Start();
        
        NW needleman = NW(pathA, pathB, output);
        
        double time = t.GetElapsed();
    
        std::cout << "time elapsed: " << time << std::endl;
        std::string elapsed = "time elapsed: " + std::to_string(time);
        wxMessageBox(elapsed, "", wxOK );
        
        
        
        
    }
    
}
