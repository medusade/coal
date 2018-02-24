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
# QtCreator .pri file for coal executable coal
########################################################################

########################################################################
# coal
coal_exe_TARGET = coal

coal_exe_INCLUDEPATH += \
$${coal_INCLUDEPATH} \

coal_exe_DEFINES += \
$${coal_DEFINES} \

########################################################################
coal_exe_HEADERS += \
$${COAL_SRC}/coal/base/ibase.h \
$${COAL_SRC}/coal/base/iface.h \
$${COAL_SRC}/coal/platform/iplatform.h \

coal_exe_SOURCES += \
$${COAL_SRC}/coal/base/ibase.c \
$${COAL_SRC}/coal/base/iface.c \
$${COAL_SRC}/coal/platform/iplatform.c \

########################################################################
coal_exe_LIBS += \

#$${coal_LIBS} \
