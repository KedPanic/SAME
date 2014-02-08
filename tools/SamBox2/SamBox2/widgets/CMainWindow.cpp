#include "widgets/CMainWindow.h"
#include "ui_cmainwindow.h"

#include "CInitializingThread.h"
#include "widgets/CProjectWizardDialog.h"
#include "widgets/CRendererWidget.h"

#include "widgets/frames/CProjectFrame.h"
#include "widgets/frames/CPropertiesFrame.h"

#include <QSplashScreen>

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow),
    m_pRendererWidget(NULL)
{
    ui->setupUi(this);

    tabifyDockWidget(ui->Project, ui->Console);
    ui->Project->show();
    ui->Project->raise();

    // set render frame.
    m_pRendererWidget = new CRendererWidget(ui->tabScene);
    ui->tabScene->layout()->addWidget(m_pRendererWidget);

    // set the frames per tab.
    CPropertiesFrame *pPropertiesFrame = new CPropertiesFrame(ui->dockWidgetProperties);
    ui->dockWidgetProperties->layout()->addWidget(pPropertiesFrame);

    CProjectFrame *pProjectFrame = new CProjectFrame(ui->dockWidgetProject);
    ui->dockWidgetProject->layout()->addWidget(pProjectFrame);    
    connect(pProjectFrame, SIGNAL(on_resourceSelected(IResource*)), pPropertiesFrame, SLOT(on_resourceSelected(IResource*)));
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

/////////////////////////////////////////////////////////////////
/// SLOTS
/////////////////////////////////////////////////////////////////
void CMainWindow::OnProjectCreated()
{
    show();
}

void CMainWindow::on_tabWidget_currentChanged(int)
{
    m_pRendererWidget->setParent(ui->tabWidget->currentWidget());
    ui->tabWidget->currentWidget()->layout()->addWidget(m_pRendererWidget);
}
