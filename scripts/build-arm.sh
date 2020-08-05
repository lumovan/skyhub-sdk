#!/bin/bash

#############################################################################
##
## Copyright (C) 2020, Smart Projects Holdings Ltd
## Contact: https://industrial.ugcs.com/contact
##
## This file is part of SkyHub SDK.
##
## BSD 3-Clause License Usage
##
## This file may be used under the terms of the BSD 3-Clause License
## as published by the Open Source Initiative and appearing in the file
## LICENSE included in the packaging of this file. Please review the
## following information to ensure the BSD 3-Clause License requirements
## will be met: https://opensource.org/licenses/BSD-3-Clause.
##
#############################################################################

cd "$(dirname "$(readlink -f "${0}")")"
set -e

if [ "$1" == "-c" ] || [ "$1" == "--clean" ] ; then
  sudo docker rm -f digi-dey-container || true
fi

export IS_RUNNING=$(sudo docker inspect -f "{{.State.Running}}" digi-dey-container)

if [ "$IS_RUNNING" != "true" ]; then
  sudo docker pull ugcs/digi-dey
  sudo docker run -it -d --name digi-dey-container ugcs/digi-dey /bin/bash
fi

if [ "$1" != "-i" ] && [ "$1" != "--incremental" ] ; then
  sudo docker cp ../lib/ digi-dey-container:/root/
  sudo docker cp ../scripts/ digi-dey-container:/root/
  sudo docker cp ../src/ digi-dey-container:/root/
  sudo docker cp ../skyhub-version.js digi-dey-container:/root/
  sudo docker cp ../skyhub-sdk.qbs digi-dey-container:/root/
fi

sudo docker exec -it digi-dey-container qbs build -d armhf profile:armv7ve qbs.defaultBuildVariant:release
mkdir -p ../build-arm
sudo docker cp digi-dey-container:/root/armhf/default/install-root/usr/local/lib/plugins/payloads/libpayload-example.so ../build-arm/
sudo chown $USER ../build-arm/libpayload-example.so
