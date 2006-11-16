#!/bin/sh
# Nico Schottelius
# Date: 2005-08-08
# cinit-conf

LIBEXEC=$(dirname $0)/../libexec/cinit-conf/

. ${LIBEXEC}/dialog-alias.sh

dialog --calendar "Test" 0 0 18 12 1982
dialog --checklist "Checktest" 0 0 0 item1 on item2 off item3 on
dialog --infobox "Infotext" 0 0 
dialog --inputbox "inputbox" 0 0 "vorgegebener text"
dialog --menu "menu" 0 0 0  tag1 item1 tag2 item2 bla blub
dialog --infobox "Infotext" 0 0 
dialog --msgbox "Infotext" 0 0 
dialog --radiolist "Infotext" 0 0 0 tag1 item1 on tag2 item2 off
dialog --textbox ~/.bashrc 0 0
dialog --yesno "Ja oder nein?" 0 0

dialog --gauge "Checktest" 0 0 10

#dialog --inputmenu "Infotext" 0 0 0 tag1 item1 tag2 item2 bla blub
