// libraryfeature.cpp
// Created 8/17/2009 by RJ Ryan (rryan@mit.edu)

#include "library/libraryfeature.h"

// KEEP THIS cpp file to tell scons that moc should be called on the class!!!
// The reason for this is that LibraryFeature uses slots/signals and for this
// to work the code has to be precompiles by moc

namespace {

// The time between selecting and activating a feature item in the left
// pane. This is required to allow smooth and responsive scrolling through
// a list of items with an encoder!
const int kDefaultClickedChildActivationTimeoutMillis = 250;

} // anonymous namespace

LibraryFeature::LibraryFeature(
        QObject *parent)
        : QObject(parent),
          m_clickedChildActivationTimeoutMillis(kDefaultClickedChildActivationTimeoutMillis) {
}

LibraryFeature::LibraryFeature(
        int clickedChildActivationTimeoutMillis,
        QObject *parent)
        : QObject(parent),
          m_clickedChildActivationTimeoutMillis(clickedChildActivationTimeoutMillis) {
    DEBUG_ASSERT(m_clickedChildActivationTimeoutMillis >= 0);
}

LibraryFeature::LibraryFeature(
        UserSettingsPointer pConfig,
        QObject* parent)
        : QObject(parent),
          m_pConfig(pConfig),
          m_clickedChildActivationTimeoutMillis(kDefaultClickedChildActivationTimeoutMillis) {
}

LibraryFeature::LibraryFeature(
        UserSettingsPointer pConfig,
        int clickedChildActivationTimeoutMillis,
        QObject* parent)
        : QObject(parent),
          m_pConfig(pConfig),
          m_clickedChildActivationTimeoutMillis(clickedChildActivationTimeoutMillis) {
    DEBUG_ASSERT(m_clickedChildActivationTimeoutMillis >= 0);
}

QStringList LibraryFeature::getPlaylistFiles(QFileDialog::FileMode mode) const {
    QString lastPlaylistDirectory = m_pConfig->getValue(
            ConfigKey("[Library]", "LastImportExportPlaylistDirectory"),
            QDesktopServices::storageLocation(QDesktopServices::MusicLocation));

    QFileDialog dialog(NULL,
                     tr("Import Playlist"),
                     lastPlaylistDirectory,
                     tr("Playlist Files (*.m3u *.m3u8 *.pls *.csv)"));
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(mode);
    dialog.setModal(true);

    // If the user refuses return
    if (! dialog.exec()) return QStringList();
    return dialog.selectedFiles();
}
