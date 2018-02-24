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
#   File: coal.pro
#
# Author: $author$
#   Date: 2/23/2018
#
# QtCreator .pro file for coal executable coal
########################################################################
include(../../../../../build/QtCreator/coal.pri)
include(../../../../QtCreator/coal.pri)
include(../../coal.pri)
include(../../../../QtCreator/app/coal/coal.pri)

TARGET = $${coal_exe_TARGET}

########################################################################
INCLUDEPATH += \
$${coal_exe_INCLUDEPATH} \

DEFINES += \
$${coal_exe_DEFINES} \

########################################################################
HEADERS += \
$${coal_exe_HEADERS} \

SOURCES += \
$${coal_exe_SOURCES} \

########################################################################
LIBS += \
$${coal_exe_LIBS} \


