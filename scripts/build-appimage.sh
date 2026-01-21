#!/bin/bash
set -e

# Download linuxdeploy and Qt plugin
wget -q https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
chmod +x linuxdeploy*.AppImage

# Extract linuxdeploy if running in a container without FUSE
if [ ! -e /dev/fuse ]; then
  ./linuxdeploy-x86_64.AppImage --appimage-extract >/dev/null
  LINUXDEPLOY_BIN=./squashfs-root/AppRun
else
  LINUXDEPLOY_BIN=./linuxdeploy-x86_64.AppImage
fi

# Copy icon with the name expected by the desktop file
cp packaging/unix/midieditor/logo48.png packaging/unix/midieditor/midieditor.png
mv MidiEditor midieditor

# Set up environment for linuxdeploy
#export LINUXDEPLOY_OUTPUT_VERSION=$(git describe --tags --always)
export QMAKE=/usr/bin/qmake6
export QML_SOURCES_PATHS=.
# export QT_QPA_PLATFORM=xcb
export EXTRA_QT_PLUGINS="multimedia;xcb"

# Create AppImage
$LINUXDEPLOY_BIN \
  --appdir AppDir \
  --executable midieditor \
  --desktop-file packaging/unix/midieditor/MidiEditor.desktop \
  --icon-file packaging/unix/midieditor/midieditor.png \
  --output appimage

# Rename AppImage to a more user-friendly name
mv MidiEditor*.AppImage MidiEditor-Linux-x86_64.AppImage
