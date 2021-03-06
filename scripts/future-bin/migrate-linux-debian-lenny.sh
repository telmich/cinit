#!/bin/sh
# 
# 2008      Nico Schottelius (nico-cinit-conf at schottelius.org)
# 
# This file is part of cinit-conf.
#
# cinit-conf is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# cinit-conf is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with cinit-conf. If not, see <http://www.gnu.org/licenses/>.
#

bd="${0%/*}"
export bd

echo "Trying to configure cinit for your Debian Linux"

# migrate /etc/fstab to mounts

"$bd/linux/sys-v-init/migrate-fstab.sh"

# migrate / create 6 getties

# migrate network

# migrate services
