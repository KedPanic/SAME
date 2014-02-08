#include "CSamBox.h"

#include "CInitializingThread.h"
#include "CProjectLoadingThread.h"
#include "widgets/CProjectWizardDialog.h"
#include "widgets/CMainWindow.h"

#include "CPlatform.h"

#include <QSplashScreen>

CSamBox *g_pSamBox = NULL;

// Constructor.
CSamBox::CSamBox(QWidget *parent) :
    QObject(parent), m_pProject(NULL), m_pSplashScreen(NULL)
{
    g_pSamBox = this;
}

CSamBox::~CSamBox()
{
}

bool CSamBox::Initialize()
{ 
    // create thread to initialize the engine.
    {
        CInitializingThread *pInitThread = new CInitializingThread();
        pInitThread->start();

        // connect
        connect(pInitThread, SIGNAL(finished()), this, SLOT(Initialized()));
        connect(pInitThread, SIGNAL(ShowSplashScreen()), this, SLOT(ShowSplashScreen()));
        connect(pInitThread, SIGNAL(ShowMessage(QString)), this, SLOT(ShowMessage(QString)));
    }

    return true;
}

// Add a supported platform could be used by a project.
void CSamBox::AddPlatform(CPlatform *p_pPlatform)
{
    SAM_ASSERT(p_pPlatform != NULL, "Platform is null");

    m_aPlatforms.push_back(p_pPlatform);
}

// Retrieves if the specified platform is supported.
CPlatform *CSamBox::GetPlatform(uint32 p_nId) const
{
    for(uint32 nIndex = 0; nIndex < m_aPlatforms.size(); ++nIndex)
    {
        if(m_aPlatforms[nIndex]->GetId() == p_nId)
        {
            return m_aPlatforms[nIndex];
        }
    }

    return NULL;
}

/////////////////////////////////////////////////////////////////
/// SLOTS
/////////////////////////////////////////////////////////////////
void CSamBox::Initialized()
{
    CProjectWizardDialog *pWizard = new CProjectWizardDialog;
    pWizard->show();

    // connect
    connect(pWizard, SIGNAL(OnProjectCreated(CProject*)), this, SLOT(OnProjectCreated(CProject*)));
    connect(pWizard, SIGNAL(OnProjectOpened(CProject*)), this, SLOT(OnProjectOpened(CProject*)));

    delete m_pSplashScreen;
    m_pSplashScreen = NULL;
}

void CSamBox::ProjectLoaded()
{
    delete m_pSplashScreen;
    m_pSplashScreen = NULL;

    // create main window.
    CMainWindow *pMainWindow = new CMainWindow;
    pMainWindow->show();
}

void CSamBox::OnProjectCreated(CProject *p_pProject)
{
    m_pProject = p_pProject;

    // create main window.
    CMainWindow *pMainWindow = new CMainWindow;
    pMainWindow->show();
}

void CSamBox::OnProjectOpened(CProject *p_pProject)
{
    m_pProject = p_pProject;

    // create loading thread.
    CProjectLoadingThread *pLoadingThread = new CProjectLoadingThread(m_pProject);
    pLoadingThread->start();

    // connect
    connect(pLoadingThread, SIGNAL(finished()), this, SLOT(ProjectLoaded()));
    connect(pLoadingThread, SIGNAL(ShowSplashScreen()), this, SLOT(ShowSplashScreen()));
    connect(pLoadingThread, SIGNAL(ShowMessage(QString)), this, SLOT(ShowMessage(QString)));
}

void CSamBox::ShowSplashScreen()
{
    QPixmap oPixmap(":/images/splash");
    m_pSplashScreen = new QSplashScreen(oPixmap);
    m_pSplashScreen->show();
}

void CSamBox::ShowMessage(const QString &p_sMessage)
{
    m_pSplashScreen->showMessage(p_sMessage);
}
