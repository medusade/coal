########################################################################
# Copyright (c) 1988-2018 $organization$
#
# This software is provided by the author and contributors ``as is''
# and any express or implied warranties, including, but not limited to,
# the implied warranties of merchantability and fitness for a particular
# purpose are disclaimed. In no event shall the author or contributors
# be liable for any direct, indirect, incidental, special, exemplary,
# or consequential damages (including, but not limited to, procurement
# of substitute goods or services; loss of use, data, or profits; or
# business interruption) however caused and on any theory of liability,
# whether in contract, strict liability, or tort (including negligence
# or otherwise) arising in any way out of the use of this software,
# even if advised of the possibility of such damage.
#
#   File: coal.pri
#
# Author: $author$
#   Date: 2/23/2018
#
# QtCreator .pri file for coal
########################################################################

OTHER_PKG = ../../../../../../..
OTHER_PRJ = ../../../../../..
OTHER_BLD = ..

THIRDPARTY_NAME = thirdparty
THIRDPARTY_PKG = $${OTHER_PKG}/$${THIRDPARTY_NAME}
THIRDPARTY_PRJ = $${OTHER_PRJ}/$${THIRDPARTY_NAME}
THIRDPARTY_SRC = $${OTHER_PRJ}/src/$${THIRDPARTY_NAME}

########################################################################
# coal
FRAMEWORK_NAME = coal

COAL_PKG = ../../../../..
COAL_BLD = ../..

COAL_PRJ = $${COAL_PKG}
COAL_BIN = $${COAL_BLD}/bin
COAL_LIB = $${COAL_BLD}/lib
COAL_SRC = $${COAL_PKG}/src

CONFIG(debug, debug|release) {
BUILD_CONFIG = Debug
coal_DEFINES += DEBUG_BUILD
} else {
BUILD_CONFIG = Release
coal_DEFINES += RELEASE_BUILD
}

# INCLUDEPATH
#
coal_INCLUDEPATH += \
$${COAL_SRC}/platform \
$${COAL_SRC}/base \
$${COAL_SRC} \
$${build_coal_INCLUDEPATH} \

# DEFINES
#
coal_DEFINES += \
$${build_coal_DEFINES} \

# LIBS
#
coal_LIBS += \
-L$${COAL_LIB}/lib$${FRAMEWORK_NAME} \
-l$${FRAMEWORK_NAME} \
