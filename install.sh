#! /bin/sh

# for testing 
#DEST_BIN=${HOME}/INSTALL/usr/local/bin
#DEST_SHARE=${HOME}/INSTALL/usr/local/lib/p7zip

# global install
DEST_BIN=/usr/local/bin
DEST_SHARE=/usr/local/lib/p7zip
[ "$1" ] && DEST_BIN=$1
[ "$2" ] && DEST_SHARE=$2

use_share="n"

if [ -x bin/7zCon.sfx ]
then
  use_share="o"
fi

if [ -x bin/7z ]
then
  use_share="o"
fi

# cleaning previous install
rm -f ${DEST_BIN}/7z
rm -f ${DEST_BIN}/7za
rm -f ${DEST_SHARE}/7z
rm -f ${DEST_SHARE}/7za
rm -f ${DEST_SHARE}/7zCon.sfx
rm -fr ${DEST_SHARE}/Codecs ${DEST_SHARE}/Formats
rmdir ${DEST_SHARE} 2> /dev/null

if [ "${use_share}" = "o" ]
then
  mkdir -p ${DEST_BIN}
  mkdir -p ${DEST_SHARE}
  if [ -x bin/7za ]
  then
    echo "- installing ${DEST_BIN}/7za"
    cp bin/7za ${DEST_SHARE}/7za
    chmod 777 ${DEST_SHARE}/7za
    strip     ${DEST_SHARE}/7za
    chmod 555 ${DEST_SHARE}/7za
    echo "#! /bin/sh" > ${DEST_BIN}/7za
    echo "${DEST_SHARE}/7za \$*" >> ${DEST_BIN}/7za
    chmod 555 ${DEST_BIN}/7za
  fi

  if [ -x bin/7zCon.sfx ]
  then
    echo "- installing ${DEST_SHARE}/7zCon.sfx"
    cp bin/7zCon.sfx ${DEST_SHARE}/7zCon.sfx
    chmod 777 ${DEST_SHARE}/7zCon.sfx
    strip     ${DEST_SHARE}/7zCon.sfx
    chmod 555 ${DEST_SHARE}/7zCon.sfx
  fi

  if [ -x bin/7z ]
  then
    echo "- installing ${DEST_BIN}/7z"
    cp bin/7z ${DEST_SHARE}/7z
    chmod 777 ${DEST_SHARE}/7z
    strip     ${DEST_SHARE}/7z
    chmod 555 ${DEST_SHARE}/7z
    cp -r bin/Codecs bin/Formats ${DEST_SHARE}/
    chmod 555 ${DEST_SHARE}/*/*
    echo "#! /bin/sh" > ${DEST_BIN}/7z
    echo "${DEST_SHARE}/7z \$*" >> ${DEST_BIN}/7z
    chmod 555 ${DEST_BIN}/7z
  fi

else
  if [ -x bin/7za ]
  then
    echo "- installing ${DEST_BIN}/7za"
    mkdir -p ${DEST_BIN}
    cp bin/7za ${DEST_BIN}/7za
    chmod 555 ${DEST_BIN}/7za
  fi
fi

