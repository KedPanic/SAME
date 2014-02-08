#ifndef __SAMBOX_APP__
#define __SAMBOX_APP__

#include "SamBox.h"
#include <QObject>
#include <QSplashScreen>

class CSamBox : public QObject
{
    Q_OBJECT

public:
    explicit CSamBox(QWidget *parent = 0);
    ~CSamBox();

    bool Initialize();

    /// @brief Retrieves current project.
    ///
    /// @return Current project.
    CProject *GetCurrentProject() const {return m_pProject;}

    /// @brief Add a supported platform could be used by a project.
    ///
    /// @param p_sPlatformFilename Path of the platform configuration file.
    void AddPlatform(const sam::String &p_sPlatformFilename);

    /// @brief Add a supported platform could be used by a project.
    ///
    /// @param p_pPlatform Created platform.
    void AddPlatform(CPlatform *p_pPlatform);

    /// @brief Retrieves supported platforms.
    ///
    /// @return Supported platforms.
    const Platforms &GetSupportedPlatforms() const {return m_aPlatforms;}

    /// @brief Retrieves the specified platform by id.
    ///
    /// @name p_nId Platform id.
    ///
    /// @return Pointer to the platform or null if not found.
    CPlatform *GetPlatform(uint32 p_nId) const;          

public slots:
    /// @brief Called when the initialization has been finished
    void Initialized();

    /// @brief Called when the current project has been loaded.
    void ProjectLoaded();

    /// @brief Called when a project has been created.
    void OnProjectCreated(CProject *p_pProject);

    /// @brief Called when a project has been opened.
    void OnProjectOpened(CProject *p_pProject);

    void ShowSplashScreen();
    void ShowMessage(const QString &p_sMessage);

private:
    CProject *m_pProject;   ///< Current project.
    Platforms m_aPlatforms; ///< Array of supported platforms.

    QSplashScreen *m_pSplashScreen;
};

#endif // __SAMBOX_APP__
