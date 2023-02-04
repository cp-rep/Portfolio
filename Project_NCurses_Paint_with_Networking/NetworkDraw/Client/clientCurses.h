// ====================================================================================
// File: clientCurses.h
// ====================================================================================

#ifndef CLIENTCURSES_H
#define CLIENTCURSES_H

typedef struct 
{
    int		m_clientMaxRows;
    int		m_clientMaxCols;
    int		m_clientYCoord;
    int		m_clientXCoord;
    int		m_clientOption;
}ClientCurseData;

// function prototypes
int	     SetupClientCurses(void);
void	     SetupClientScreen(ClientCurseData *clientCData);	    
void 	     EndClientCurses(void);

#endif // CLIENTCURSES_H
