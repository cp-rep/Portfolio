// ============================================================================
// File: serverCurses.h
// ============================================================================
#ifndef SERVERCURSE_H
#define SERVERCURSE_H

typedef struct
{
    int		m_servOption;
    int		m_servMaxRows;
    int		m_servMaxCols;
    int		m_servYCoord;
    int		m_servXCoord;
}ServerCurseData;

// function prototypes
int 	    SetupServerCurses(void);
void 	    SetupServerScreen(ServerCurseData *servCData);
void 	    EndServerCurses(void);

#endif // SERVERCURSE_H