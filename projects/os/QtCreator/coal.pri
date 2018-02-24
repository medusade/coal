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
# Os QtCreator .pri file for coal
########################################################################
UNAME = $$system(uname)

contains(UNAME,Darwin) {
COAL_OS = macosx
} else {
COAL_OS = linux
}

########################################################################
# coal
coal_INCLUDEPATH += \

coal_DEFINES += \

coal_LIBS += \
$${build_coal_LIBS} \
-lpthread \
-ldl \

contains(COAL_OS,Linux) {
coal_LIBS += \
-lrt 
} else {
}
