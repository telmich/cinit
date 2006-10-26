#!/bin/sh
# Nico Schottelius
# 2006-10-23
# cLinux/cinit

. $(dirname $0)/cinit.build-env

set -e

mkdir -p "${BASEDIR}"

mkdir -p "${SERVICES}"
mkdir -p "${SERVICES}/${C_INIT}"

mkdir -p "${CONFIG}"
