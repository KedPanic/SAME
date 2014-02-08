#-------------------------------------------------
#
# Project created by QtCreator 2014-01-23T21:00:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SamBox2
TEMPLATE = app


SOURCES += main.cpp\
        CSamBox.cpp \
    CInitializingThread.cpp \
    widgets/CProjectWizardDialog.cpp \
    resources/CResourceManager.cpp \
    exporter/CExporterManager.cpp \
    exporter/CMeshExporter.cpp \
    exporter/CTextureExporterDXT.cpp \
    exporter/ITextureExporter.cpp \
    resources/CFolder.cpp \
    resources/CMeshResource.cpp \
    resources/CTextureResource.cpp \
    resources/IResource.cpp \
    widgets/CMainWindow.cpp \
    CProject.cpp \
    CPlatform.cpp \
    widgets/frames/CProjectFrame.cpp \
    CFileWatcher.cpp \
    CProjectLoadingThread.cpp \
    resources/CFileResource.cpp \
    widgets/frames/project/CFolderTreeItem.cpp \
    widgets/frames/CPropertiesFrame.cpp \
    widgets/frames/properties/CTextureFrame.cpp \
    widgets/frames/properties/CTextureTargetSettingsFrame.cpp \
    widgets/CRendererWidget.cpp \
    CEngineThread.cpp

HEADERS  += CSamBox.h \
    CInitializingThread.h \
    widgets/CProjectWizardDialog.h \
    resources/CFileResource.h \
    resources/CFolder.h \
    resources/CMeshResource.h \
    resources/CResourceManager.h \
    resources/CTextureResource.h \
    resources/IResource.h \
    resources/IResourceFactory.h \
    resources/SMeshMetadata.h \
    resources/STextureMetadata.h \
    exporter/CExporterManager.h \
    exporter/CMeshExporter.h \
    exporter/CTextureExporterDXT.h \
    exporter/IExporter.h \
    exporter/ITextureExporter.h \
    SamBox.h \
    CProject.h \
    CPlatform.h \
    widgets/CMainWindow.h \
    widgets/frames/CProjectFrame.h \
    CFileWatcher.h \
    CProjectLoadingThread.h \
    widgets/frames/project/CFolderTreeItem.h \
    widgets/frames/CPropertiesFrame.h \
    widgets/frames/properties/CTextureFrame.h \
    widgets/frames/properties/CTextureTargetSettingsFrame.h \
    widgets/frames/properties/IPropertiesFrame.h \
    widgets/CRendererWidget.h \
    CEngineThread.h

FORMS    += \
    widgets/cprojectwizarddialog.ui \
    widgets/cmainwindow.ui \
    widgets/frames/cprojectframe.ui \
    widgets/frames/cpropertiesframe.ui \
    widgets/frames/properties/ctextureframe.ui \
    widgets/frames/properties/ctexturetargetsettingsframe.ui


################################
# links
################################
LIBS += -L$$PWD/../../../external/assimp/lib/

win32:CONFIG(release, debug|profile|release): {
    LIBS += -L$$PWD/../../../lib/release/
}
else:win32: {
    CONFIG(profile, debug|profile): LIBS += -L$$PWD/../../../lib/profile/
    CONFIG(debug, debug|profile): LIBS += -L$$PWD/../../../lib/debug/

    LIBS += -lSamProfiling
}
else:unix: {

}

LIBS += -lSamCommon -lSamRenderer -lSamEntitySystem -lFreeImage -lassimp -lShell32 -lnvcore -lnvtt -lnvimage -lnvmath -lnvthread -lsquish

################################
# add include path !
################################
INCLUDEPATH += $$PWD/
INCLUDEPATH += $$PWD/../../../include/sam/
INCLUDEPATH += $$PWD/../../../external/freeimage/Source/
INCLUDEPATH += $$PWD/../../../external/assimp/include/
INCLUDEPATH += $$PWD/../../../external/nvtt/src/
# set platform specific path.
win32: {
    INCLUDEPATH += $$PWD/../../../include/sam/platform/win

    #external libraries
    INCLUDEPATH += $$(DXSDK_DIR)/Include
}

################################
# libraries path !
################################
DEPENDPATH += $$PWD/../../../lib

# set platform specific libraries.
win32: {
    DEPENDPATH += $$(DXSDK_DIR)/Lib/x86/
}

RESOURCES += \
    resource.qrc
