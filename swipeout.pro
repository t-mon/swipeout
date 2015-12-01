# This is the basic qmake template for the Ubuntu-SDK
# it handles creation and installation of the manifest
# file and takes care of subprojects
TEMPLATE = subdirs

#load Ubuntu specific features
load(ubuntu-click)

SUBDIRS += swipeout

# specify the manifest file, this file is required for click
# packaging and for the IDE to create runconfigurations
UBUNTU_MANIFEST_FILE=manifest.json.in

# specify translation domain, this must be equal with the
# app name in the manifest file
UBUNTU_TRANSLATION_DOMAIN="swipeout.t-mon"

# specify the source files that should be included into
# the translation file, from those files a translation
# template is created in po/template.pot, to create a
# translation copy the template to e.g. de.po and edit the sources
UBUNTU_TRANSLATION_SOURCES+= \
    $$files(*.qml,true) \
    $$files(*.js,true) \
    $$files(*.desktop,true)

# specifies all translations files and makes sure they are
# compiled and installed into the right place in the click package
UBUNTU_PO_FILES+=$$files(po/*.po)

CONF_FILES +=  swipeout.apparmor \
               swipeout.png \
               swipeout.desktop

# install level files
dataFolder.files = data/
dataFolder.path = /swipeout

#show all the files in QtCreator
OTHER_FILES += $${CONF_FILES} \
               dataFolder

#specify where the config files are installed to
config_files.path = /swipeout
config_files.files += $${CONF_FILES}

#install the desktop file, a translated version is
#automatically created in the build directory
desktop_file.path = /swipeout
desktop_file.files = swipeout.desktop
desktop_file.CONFIG += no_check_exist

INSTALLS += desktop_file config_files dataFolder
