#!/bin/sh

rm -rf "$HOME/.helm/patches/User Patches"
ln -sf "$HOME/audio/my/presets/helm" "$HOME/.helm/patches/User Patches"

rm -rf $HOME/.amsynth/banks
ln -sf $HOME/audio/my/presets/amsynth $HOME/.amsynth/banks

rm -rf $HOME/.hydrogen
ln -sf $HOME/audio/hydrogen/ $HOME/.hydrogen

sudo ln -sf $HOME/audio/my/presets/zynaddsubfx/* /usr/share/zynaddsubfx/banks/
